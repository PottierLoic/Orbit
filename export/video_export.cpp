#include "video_export.hpp"

#include <cmath>
#include <vector>
#include <string>

#include "color/apply.hpp"

void export_video(IFractalBackend& backend, const Palette& palette, const RenderParams& render_params, const IterationParams& iteration_params, const VideoExportParams& export_params, const AnimationParams& animation_params) {
    double start = std::stod(animation_params.start_zoom);
    double end = std::stod(animation_params.final_zoom);
    uint32_t frame_count = static_cast<uint32_t>(
        std::ceil(std::abs(std::log(end / start)) / std::log(animation_params.zoom_factor) * export_params.fps)
    );
    double zoom_factor_per_frame = std::pow(animation_params.zoom_factor, 1.0 / (export_params.fps));

    RenderParams current_render_params = render_params;
    current_render_params.zoom = std::to_string(start);
    current_render_params.width = export_params.width;
    current_render_params.height = export_params.height;

    std::string cmd = "ffmpeg -y -f rawvideo -pixel_format rgba -video_size " +
        std::to_string(export_params.width) + "x" + std::to_string(export_params.height) +
        " -framerate " + std::to_string(export_params.fps) +
        " -i pipe:0 -c:v libx264 -pix_fmt yuv420p " +
        export_params.output_path;

#ifdef _WIN32
    FILE* pipe = _popen(cmd.c_str(), "wb");
#else
    FILE* pipe = popen(cmd.c_str(), "wb");
#endif

    if (!pipe) {
        throw std::runtime_error("Failed to open FFmpeg pipe");
    }

    for (size_t i = 0; i < frame_count; i++) {
        std::vector<PixelValue> pixels = backend.render_frame(current_render_params, iteration_params);
        std::vector<RGBA> colors = apply_palette(palette, pixels, false, iteration_params.max_iterations); // TODO: don't keep hardcoded smooth boolean
        fwrite(colors.data(), sizeof(RGBA), colors.size(), pipe);
        double next_zoom = std::stod(current_render_params.zoom);
        next_zoom *= zoom_factor_per_frame;
        current_render_params.zoom = std::to_string(next_zoom);
    }

#ifdef _WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif

}
