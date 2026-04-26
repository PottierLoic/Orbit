#include "image_export.hpp"

#include <thread>

void export_image(const std::vector<RGBA>& pixels, const ImageExportParams& export_params) {
    switch (export_params.file_type) {
        case ImageFileType::PNG : stbi_write_png(export_params.output_path.c_str(), export_params.width, export_params.height, 4, pixels.data(), export_params.width * 4); break;
        case ImageFileType::BMP : stbi_write_bmp(export_params.output_path.c_str(), export_params.width, export_params.height, 4, pixels.data()); break;
        case ImageFileType::TGA : stbi_write_tga(export_params.output_path.c_str(), export_params.width, export_params.height, 4, pixels.data()); break;
        case ImageFileType::JPG : stbi_write_jpg(export_params.output_path.c_str(), export_params.width, export_params.height, 4, pixels.data(), 100); break;
    }
}

void export_image(std::shared_ptr<IFractalBackend> backend, Palette palette, RenderParams render_params, IterationParams iteration_params, ImageExportParams export_params, bool smooth_coloring, std::shared_ptr<ExportTask> task) {
    std::thread([backend, palette, render_params, iteration_params, export_params, smooth_coloring, task]() mutable {
        render_params.width = export_params.width;
        render_params.height = export_params.height;
        render_params.zoom = export_params.zoom;
        render_params.center_real = export_params.center_real;
        render_params.center_imag = export_params.center_imag;

        if (task) {
            task->filename = export_params.output_path;
            task->type = FileType::Image;
            task->total = render_params.height;
        }

        auto pixels = backend->render_frame(render_params, iteration_params, [&task]() {
            if (task) { task->progress.fetch_add(1, std::memory_order_relaxed); }
            return !task || task->status != TaskStatus::Cancelled;
        });
        if (task) { task->status = TaskStatus::Coloring; }
        auto colors = apply_palette(palette, pixels, smooth_coloring, iteration_params.max_iterations);
        if (task) { task->status = TaskStatus::Writing; }
        export_image(colors, export_params);
        if (task && task->status != TaskStatus::Cancelled) {
            task->status = TaskStatus::Done;
        }
    }).detach();
}