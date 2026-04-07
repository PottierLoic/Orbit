#include "image_export.hpp"

void export_image(const std::vector<RGBA>& pixels, const ImageExportParams& params) { 
    switch (params.file_type) {
        case ImageFileType::PNG : stbi_write_png(params.output_path.c_str(), params.width, params.height, 4, pixels.data(), params.width * 4); break;
        case ImageFileType::BMP : stbi_write_bmp(params.output_path.c_str(), params.width, params.height, 4, pixels.data()); break;
        case ImageFileType::TGA : stbi_write_tga(params.output_path.c_str(), params.width, params.height, 4, pixels.data()); break;
        case ImageFileType::JPG : stbi_write_jpg(params.output_path.c_str(), params.width, params.height, 4, pixels.data(), 100); break;
    }
}