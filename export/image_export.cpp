#include "image_export.hpp"

void export_png(const std::vector<RGBA>& pixels, const ExportParams& params) { 
    switch (params.file_type) {
        case FileType::PNG : stbi_write_png(params.output_path.c_str(), params.width, params.height, 4, pixels.data(), params.width * 4); break;
        case FileType::BMP : stbi_write_bmp(params.output_path.c_str(), params.width, params.height, 4, pixels.data()); break;
        case FileType::TGA : stbi_write_tga(params.output_path.c_str(), params.width, params.height, 4, pixels.data()); break;
        case FileType::JPG : stbi_write_jpg(params.output_path.c_str(), params.width, params.height, 4, pixels.data(), 100); break;
    }
}