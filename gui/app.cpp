#include "app.hpp"
#include "backend/backend_factory.hpp"

#include <stdexcept>
#include <iostream> // TODO REMOVE

App::App(uint32_t width, uint32_t height, const std::string& title)
    : _palettes(get_all_palettes()),
      _current_palette(0),
      _ui_context{_render_params, _iteration_params, _current_backend, _current_palette, _palettes, _image_export_params, _video_export_params, _animation_params}{
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    _window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!_window) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(_window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

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
            std::cout << "need render" << std::endl; // TODO RENDER INSTEAD
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

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Call to input handling here

        _ui.display_panels(_ui_context);

        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(_window);

        glfwPollEvents();
        // call to render handling here
    }
}

App::~App() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(_window);
    glfwTerminate();
}