#pragma once

#include <string>
#include <cstdint>

enum class ImageFileType {
    PNG,
    BMP,
    TGA,
    JPG,
};
inline const char* image_file_type_names[] = { "PNG", "BMP", "TGA", "JPG"};
constexpr size_t image_file_type_count = 4;

struct ImageExportParams {
    uint32_t width = 640;
    uint32_t height = 480;
    std::string center_real = "0.0";
    std::string center_imag = "0.0";
    std::string output_path = "output.png";
    ImageFileType file_type = ImageFileType::PNG;
};

enum class VideoFileType {
    MP4,
    AVI,
    //TODO depending on compatiblity with FFmpeg
};
inline const char* video_file_type_names[] = { "MP4", "AVI"};
constexpr size_t video_file_type_count = 2;

struct VideoExportParams {
    uint32_t width = 640;
    uint32_t height = 480;
    std::string center_real = "0.0";
    std::string center_imag = "0.0";
    std::string output_path = "output.mp4";
    VideoFileType file_type = VideoFileType::MP4;
    uint32_t fps = 30;
};