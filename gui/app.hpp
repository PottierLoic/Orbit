#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <string>
#include <optional>

#include "ui.hpp"
#include "backend/backend.hpp"
#include "color/palette.hpp"
#include "color/palette_presets.hpp"
#include "renderer.hpp"
#include "export/export_task.hpp"

class App {
public:
    App(uint32_t width, uint32_t height, const std::string& title);
    ~App();
    void on_resize(int width, int height);
    void on_scroll(double y_offset);
    void run();

private:
    GLFWwindow* _window = nullptr;
    uint32_t _width;
    uint32_t _height;

    std::optional<Renderer> _renderer;

    Backend _current_backend = Backend::CpuMultiThreaded;
    std::unique_ptr<IFractalBackend> _backend;

    std::vector<Palette>& _palettes;
    int _current_palette;

    RenderParams _render_params;
    IterationParams _iteration_params;
    ImageExportParams _image_export_params;
    VideoExportParams _video_export_params;

    bool _smooth_coloring = true;

    std::vector<std::shared_ptr<ExportTask>> _export_tasks;

    UI _ui;
    UIContext _ui_context;
};