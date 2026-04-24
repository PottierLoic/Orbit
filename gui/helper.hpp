#pragma once

#include "external/imgui/imgui.h"
#include "color/rgba.hpp"

ImVec4 to_imvec4(const RGBA& color) {
    return ImVec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
}