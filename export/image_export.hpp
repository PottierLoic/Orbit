#pragma once

#include <vector>

#include "external/stb/stb_image_write.h"

#include "color/rgba.hpp"
#include "export_params.hpp"
#include "core/iteration_params.hpp"
#include "backend/backend.hpp"
#include "backend/render_params.hpp"
#include "color/palette.hpp"
#include "color/apply.hpp"

void export_image(const std::vector<RGBA>& pixels, const ImageExportParams& export_params);
void export_image(IFractalBackend& backend, const Palette palette, const RenderParams render_params, const IterationParams iteration_params, const ImageExportParams export_params, bool smooth_coloring);
