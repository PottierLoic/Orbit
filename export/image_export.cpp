#include "image_export.hpp"

void export_image(const std::vector<RGBA>& pixels, const ImageExportParams& export_params) {
    switch (export_params.file_type) {
        case ImageFileType::PNG : stbi_write_png(export_params.output_path.c_str(), export_params.width, export_params.height, 4, pixels.data(), export_params.width * 4); break;
        case ImageFileType::BMP : stbi_write_bmp(export_params.output_path.c_str(), export_params.width, export_params.height, 4, pixels.data()); break;
        case ImageFileType::TGA : stbi_write_tga(export_params.output_path.c_str(), export_params.width, export_params.height, 4, pixels.data()); break;
        case ImageFileType::JPG : stbi_write_jpg(export_params.output_path.c_str(), export_params.width, export_params.height, 4, pixels.data(), 100); break;
    }
}

void export_image(IFractalBackend& backend, const Palette& palette, const RenderParams& render_params, const IterationParams& iteration_params, const ImageExportParams& export_params, bool smooth_coloring) {
    auto pixels = backend.render_frame(render_params, iteration_params);
    auto colors = apply_palette(palette, pixels, smooth_coloring, iteration_params.max_iterations);
    export_image(colors, export_params);
}