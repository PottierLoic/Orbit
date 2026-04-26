#include "video_export.hpp"

#include <cmath>
#include <vector>
#include <string>
#include <thread>
#include <filesystem>

#include "color/apply.hpp"

void export_video(std::shared_ptr<IFractalBackend> backend, Palette palette, RenderParams render_params, IterationParams iteration_params, VideoExportParams export_params, bool smooth_coloring, std::shared_ptr<ExportTask> task) {
    std::thread([backend, palette, render_params, iteration_params, export_params, smooth_coloring, task]() mutable {
        double start = std::stod(export_params.start_zoom);
        double end = std::stod(export_params.final_zoom);
        uint32_t frame_count = static_cast<uint32_t>(
                std::ceil(std::abs(std::log(end / start)) / std::log(export_params.zoom_factor) * export_params.fps)
        );
        double zoom_factor_per_frame = std::pow(export_params.zoom_factor, 1.0 / (export_params.fps));

        if (task) {
            task->filename = export_params.output_path;
            task->type = FileType::Video;
            task->total = frame_count;
        }

        RenderParams current_render_params = render_params;
        current_render_params.zoom = std::to_string(start);
        current_render_params.width = export_params.width;
        current_render_params.height = export_params.height;
        current_render_params.center_real = export_params.center_real;
        current_render_params.center_imag = export_params.center_imag;

        std::string cmd = "ffmpeg -y -f rawvideo -pixel_format rgba -video_size " +
                          std::to_string(export_params.width) + "x" + std::to_string(export_params.height) +
                          " -framerate " + std::to_string(export_params.fps) +
                          " -i pipe:0 -c:v libx264 -pix_fmt yuv420p " +
                          export_params.output_path;

#ifdef _WIN32
    FILE* pipe = _popen(cmd.c_str(), "wb");
#else
    FILE *pipe = popen(cmd.c_str(), "wb");
#endif

        if (!pipe) {
            throw std::runtime_error("Failed to open FFmpeg pipe");
        }

        for (size_t i = 0; i < frame_count; i++) {
            if (task && task->status == TaskStatus::Cancelled) {
                break;
            }
            std::vector <PixelValue> pixels = backend->render_frame(current_render_params, iteration_params);
            std::vector <RGBA> colors = apply_palette(palette, pixels, smooth_coloring,
                                                      iteration_params.max_iterations);
            fwrite(colors.data(), sizeof(RGBA), colors.size(), pipe);
            if (task) {
                task->progress = static_cast<uint32_t>(i + 1);
            }
            double next_zoom = std::stod(current_render_params.zoom);
            next_zoom *= zoom_factor_per_frame;
            current_render_params.zoom = std::to_string(next_zoom);
        }

#ifdef _WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif

        if (task && task->status != TaskStatus::Cancelled) {
            task->status = TaskStatus::Done;
        }
    }).detach();
}
