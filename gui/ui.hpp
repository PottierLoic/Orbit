#pragma once

#include "core/iteration_params.hpp"
#include "backend/render_params.hpp"
#include "backend/backend.hpp"
#include "export/export_params.hpp"
#include "export/animation_params.hpp"
#include "color/palette.hpp"

struct UIContext {
    // Fractal
    RenderParams& render_params;
    IterationParams& iteration_params;
    Backend& backend;

    // Palette
    int& current_palette;
    std::vector<Palette>& palettes;

    // Export
    ImageExportParams& image_export_params;
    VideoExportParams& video_export_params;
    AnimationParams& animation_params;

    // Misc
    bool& smooth_coloring;

    // Flags
    bool need_render = true;
    bool need_image_export = false;
    bool need_video_export = false;
};

class UI {
private:
    bool _enable_export_panel = true; // with two tabs: video and image and a button to export
                                 // not linked to current position / zoom but also a button to use current position / zoom
                                 // with a little previsualisation too but in reduced quality
                                 // and possibility to see start and end position for video
    bool _enable_palette_panel = true; // display palette colors, cycle_length, palette list dropdown, possibility to add a new palette, modify existing ones
    bool _enable_fractal_settings_panel = true; // zoom level, coordinates, max iterations, etc.
    bool _enable_rendering_panel = true; // cardioid check, cycling value checks etc

    void display_export_panel(UIContext& context);
    void display_palette_panel(UIContext& context);
    void display_fractal_settings_panel(UIContext& context);
    void display_rendering_panel(UIContext& context);

    int _editing_color_index = 0;
public:
    void display_panels(UIContext& context);
};