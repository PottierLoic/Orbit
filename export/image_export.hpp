#pragma once

#include <vector>

#include "external/stb/stb_image_write.h"

#include "color/rgba.hpp"
#include "export_params.hpp"

void export_image(const std::vector<RGBA>& pixels, const ImageExportParams& params);