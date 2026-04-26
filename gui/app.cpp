#include "app.hpp"
#include "backend/backend_factory.hpp"
#include "color/apply.hpp"
#include "export/image_export.hpp"
#include "export/video_export.hpp"
#include "export/export_params.hpp"

#include <stdexcept>

App::App(uint32_t width, uint32_t height, const std::string& title)
    : _palettes(get_all_palettes()),
      _current_palette(0),
      _ui_context{_render_params, _iteration_params, _current_backend, _current_palette, _palettes,
                  _image_export_params, _video_export_params, _smooth_coloring, _export_tasks} {
    _width = width;
    _height = height;

    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    _window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!_window) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetWindowUserPointer(_window, this);
    glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        glViewport(0, 0, width, height);
        app->on_resize(width, height);
    });

    glfwSetScrollCallback(_window, [](GLFWwindow* window, double, double y_offset) {
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        app->on_scroll(y_offset);
    });

    _render_params.width = width;
    _render_params.height = height;

    glfwMakeContextCurrent(_window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    _renderer.emplace(std::string(SHADER_PATH) + "fractal.vert", std::string(SHADER_PATH) + "fractal.frag");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void App::run() {
    Backend last_backend = _current_backend;
    _backend = make_backend(_current_backend);

    while (!glfwWindowShouldClose(_window)) {
        if (last_backend != _current_backend) {
            _backend = make_backend(_current_backend);
            last_backend = _current_backend;
        }

        if (_ui_context.need_render) {
            auto pixels = _backend->render_frame(_render_params, _iteration_params);
            auto colors = apply_palette(_palettes[_current_palette], pixels, _smooth_coloring, _iteration_params.max_iterations);
            _renderer->upload(colors, _render_params.width, _render_params.height);
            _ui_context.need_render = false;
        }

        if (_ui_context.need_image_export) {
            auto export_backend = std::shared_ptr<IFractalBackend>(make_backend(_current_backend).release());
            auto task = std::make_shared<ExportTask>();
            _export_tasks.push_back(task);
            export_image(export_backend, _palettes[_current_palette], _render_params, _iteration_params, _image_export_params, _smooth_coloring, task);
            _ui_context.need_image_export = false;
        }

        if (_ui_context.need_video_export) {
            auto export_backend = std::shared_ptr<IFractalBackend>(make_backend(_current_backend).release());
            auto task = std::make_shared<ExportTask>();
            _export_tasks.push_back(task);
            export_video(export_backend, _palettes[_current_palette], _render_params, _iteration_params, _video_export_params, _smooth_coloring, task);
            _ui_context.need_video_export = false;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        _renderer->draw();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        _ui.display_panels(_ui_context);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
}

App::~App() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(_window);
    glfwTerminate();
}

void App::on_resize(int width, int height) {
    _width = static_cast<uint32_t>(width);
    _height = static_cast<uint32_t>(height);
    _render_params.width = _width;
    _render_params.height = _height;
    _ui_context.need_render = true;
}

void App::on_scroll(double y_offset) {
    if (ImGui::GetIO().WantCaptureMouse) return;
    double mouse_x, mouse_y;
    glfwGetCursorPos(_window, &mouse_x, &mouse_y);

    double zoom = safe_stod(_render_params.zoom);
    double center_real = safe_stod(_render_params.center_real);
    double center_imag = safe_stod(_render_params.center_imag);

    double aspect = static_cast<double>(_width) / static_cast<double>(_height);
    double vw = 3.5 / zoom;
    double vh = vw / aspect;

    double mouse_real = safe_stod(_render_params.center_real) + (mouse_x / _render_params.width - 0.5) * vw;
    double mouse_imag = safe_stod(_render_params.center_imag) - (mouse_y / _render_params.height - 0.5) * vh;

    double factor = std::pow(1.1, std::clamp(y_offset, -3.0, 3.0));
    zoom *= factor;

    double new_vw = 3.5 / zoom;
    double new_vh = new_vw / aspect;

    center_real = mouse_real - (mouse_x / _render_params.width - 0.5) * new_vw;
    center_imag = mouse_imag + (mouse_y / _render_params.height - 0.5) * new_vh;

    _render_params.zoom = std::to_string(zoom);
    _render_params.center_real = std::to_string(center_real);
    _render_params.center_imag = std::to_string(center_imag);

    _ui_context.need_render = true;
}