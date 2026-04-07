#pragma once

#include <string>
#include <cstdint>

enum class ImageFileType {
    PNG,
    BMP,
    TGA,
    JPG,
};

struct ImageExportParams {
    uint32_t width;
    uint32_t height;
    std::string output_path;
    ImageFileType file_type;
};

enum class VideoFileType {
    MP4,
    WAV,
    //TODO depending on compatiblity with FFmpeg
};

struct VideoExportParams {
    uint32_t width;
    uint32_t height;
    std::string output_path;
    VideoFileType file_type;
    uint32_t fps;
};