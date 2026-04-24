#include "backend/backend.hpp"
#include "backend/backend_factory.hpp"
#include "export/animation_params.hpp"
#include "color/apply.hpp"

#include "export/video_export.hpp"

int main () {
    RenderParams render_params;
    render_params.set = Set::Mandelbrot;
    render_params.center_real = "-1.371995560824871";
    render_params.center_imag = "-0.0874889176338911";

    IterationParams iteration_params;
    iteration_params.max_iterations = 100;
    iteration_params.cardioid_check = true;

    Palette palette;
    palette.interpolation_mode = InterpolationMode::Cosine;
    palette.cycle_length = 100.0;
    palette.colors = {
            RGBA{0,   10,   42, 255},
            RGBA{143,  12, 245, 255},
            RGBA{237, 255, 255, 255},
            RGBA{125, 87, 230,   255},
            RGBA{0,   98,   112,   255},
    };
    palette.interior_color = RGBA{0, 0, 0, 0};

    auto backend = make_backend(Backend::CpuMultiThreaded);

    VideoExportParams export_params;
    export_params.width = 1920;
    export_params.height = 1080;
    export_params.output_path = "test2.mp4";
    export_params.file_type = VideoFileType::MP4;
    export_params.fps = 60;

    AnimationParams animation_params;
    animation_params.start_zoom = "0.5";
    animation_params.final_zoom = "70.0";
    animation_params.zoom_factor = 2.0;

    export_video(*backend, palette, render_params, iteration_params, export_params, animation_params);

    return 0;
}