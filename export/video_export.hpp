#pragma once

#include "backend/backend.hpp"
#include "backend/render_params.hpp"
#include "animation_params.hpp"
#include "export_params.hpp"
#include "core/iteration_params.hpp"
#include "color/palette.hpp"

void export_video(IFractalBackend& backend, const Palette palette, const RenderParams render_params, const IterationParams iteration_params, const VideoExportParams export_params, const AnimationParams animation_params, bool smooth_coloring);
