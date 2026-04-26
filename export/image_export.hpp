#pragma once

#include <vector>
#include <memory>

#include "external/stb/stb_image_write.h"

#include "color/rgba.hpp"
#include "export_params.hpp"
#include "export_task.hpp"
#include "core/iteration_params.hpp"
#include "backend/backend.hpp"
#include "backend/render_params.hpp"
#include "color/palette.hpp"
#include "color/apply.hpp"

void export_image(const std::vector<RGBA>& pixels, const ImageExportParams& export_params);
void export_image(std::shared_ptr<IFractalBackend> backend, Palette palette, RenderParams render_params, IterationParams iteration_params, ImageExportParams export_params, bool smooth_coloring, std::shared_ptr<ExportTask> task = nullptr);
