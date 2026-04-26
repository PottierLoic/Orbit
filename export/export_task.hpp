#pragma once

#include <string>
#include <atomic>
#include <cstdint>

enum class FileType { Image, Video };
enum class TaskStatus { Running, Coloring, Writing, Done, Cancelled };

struct ExportTask {
    std::string filename;
    FileType type;
    std::atomic<uint32_t> progress = 0;
    uint32_t total = 0;
    std::atomic<TaskStatus> status = TaskStatus::Running;
};