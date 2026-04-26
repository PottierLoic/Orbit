#pragma once

#include "backend/backend.hpp"
#include "backend/render_params.hpp"
#include "export_params.hpp"
#include "export_task.hpp"
#include "core/iteration_params.hpp"
#include "color/palette.hpp"

void export_video(std::shared_ptr<IFractalBackend> backend, Palette palette, RenderParams render_params, IterationParams iteration_params, VideoExportParams export_params, bool smooth_coloring, std::shared_ptr<ExportTask> task = nullptr);
