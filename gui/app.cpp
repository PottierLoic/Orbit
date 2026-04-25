#include "app.hpp"
#include "backend/backend_factory.hpp"
#include "color/apply.hpp"

#include <stdexcept>
#include <iostream> // TODO REMOVE

App::App(uint32_t width, uint32_t height, const std::string& title)
    : _palettes(get_all_palettes()),
      _current_palette(0),
      _ui_context{_render_params, _iteration_params, _current_backend, _current_palette, _palettes, _image_export_params, _video_export_params, _animation_params, _smooth_coloring}{
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

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

    _render_params.width = width;
    _render_params.height = height;

    glfwMakeContextCurrent(_window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    _renderer.emplace(std::string(SHADER_PATH) + "fractal.vert", std::string(SHADER_PATH) + "fractal.frag");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
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
            std::cout << "need image export" << std::endl; // TODO CALL IMAGE EXPORT FUNCTION INSTEAD
            _ui_context.need_image_export = false;
        }

        if (_ui_context.need_video_export) {
            std::cout << "need video export" << std::endl; // TODO CALL VIDEO EXPORT FUNCTION INSTEAD
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