#pragma once

#include <string>
#include <cstdint>

enum class FileType {
    PNG,
    BMP,
    TGA,
    JPG,
};

struct ExportParams {
    uint32_t width;
    uint32_t height;
    std::string output_path;
    FileType file_type;
};