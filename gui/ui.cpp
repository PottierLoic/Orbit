#include "ui.hpp"
#include <imgui.h>
#include <imgui_stdlib.h>

#include "helper.hpp"

void UI::display_panels(UIContext &context) {
    // TODO give parameters to corresponding panels
    if (_enable_export_panel) display_export_panel(context);
    if (_enable_palette_panel) display_palette_panel(context);
    if (_enable_fractal_settings_panel) display_fractal_settings_panel(context);
    if (_enable_rendering_panel) display_rendering_panel(context);
}

void UI::display_export_panel(UIContext& context) {
    if (!ImGui::Begin("Export")) {
        ImGui::End();
        return;
    }

    if (ImGui::BeginTabBar("Export tabs")) {
        if (ImGui::BeginTabItem("Image")) {
            ImGui::InputText("Output path", &context.image_export_params.output_path);

            int current_image_file_type = static_cast<int>(context.image_export_params.file_type);
            if (ImGui::Combo("File type", &current_image_file_type, image_file_type_names, IM_ARRAYSIZE(image_file_type_names))) {
                context.image_export_params.file_type = static_cast<ImageFileType>(current_image_file_type);
            }

            int width = static_cast<int>(context.image_export_params.width);
            if (ImGui::InputInt("Width", &width)) {
                context.image_export_params.width = static_cast<uint32_t>(std::max(0, width));
            }

            int height = static_cast<int>(context.image_export_params.height);
            if (ImGui::InputInt("Height", &height)) {
                context.image_export_params.height = static_cast<uint32_t>(std::max(0, height));
            }

            ImGui::Separator();

            ImGui::InputText("Real", &context.image_export_params.center_real);
            ImGui::InputText("Imaginary", &context.image_export_params.center_imag);
            if (ImGui::Button("Use current position")) {
                context.image_export_params.center_real = context.render_params.center_real;
                context.image_export_params.center_imag = context.render_params.center_imag;
            }

            ImGui::Separator();

            if (ImGui::Button("Generate image")) {
                context.need_image_export = true;
            }

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Video")) {
            ImGui::InputText("Output path", &context.video_export_params.output_path);

            int current_video_file_type = static_cast<int>(context.video_export_params.file_type);
            if (ImGui::Combo("File type", &current_video_file_type, video_file_type_names, IM_ARRAYSIZE(video_file_type_names))) {
                context.video_export_params.file_type = static_cast<VideoFileType>(current_video_file_type);
            }

            ImGui::Separator();

            int width = static_cast<int>(context.video_export_params.width);
            if (ImGui::InputInt("Width", &width)) {
                context.video_export_params.width = static_cast<uint32_t>(std::max(0, width));
            }

            int height = static_cast<int>(context.video_export_params.height);
            if (ImGui::InputInt("Height", &height)) {
                context.video_export_params.height = static_cast<uint32_t>(std::max(0, height));
            }

            int fps = static_cast<int>(context.video_export_params.fps);
            if (ImGui::InputInt("FPS", &fps)) {
                context.video_export_params.fps = static_cast<uint32_t>(std::max(0, fps));
            }

            ImGui::Separator();

            ImGui::InputText("Real", &context.video_export_params.center_real);
            ImGui::InputText("Imaginary", &context.video_export_params.center_imag);
            if (ImGui::Button("Use current position")) {
                context.video_export_params.center_real = context.render_params.center_real;
                context.video_export_params.center_imag = context.render_params.center_imag;
            }

            ImGui::Separator();

            ImGui::InputText("Start zoom", &context.animation_params.start_zoom);
            ImGui::InputText("Final zoom", &context.animation_params.final_zoom);
            ImGui::InputDouble("Zoom factor", &context.animation_params.zoom_factor);

            ImGui::Separator();

            if (ImGui::Button("Generate video")) {
                context.need_video_export = true;
            }

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}

void UI::display_palette_panel(UIContext& context) {
    if (!ImGui::Begin("Palette")) {
        ImGui::End();
        return;
    }

    const std::string& current_palette_name = context.palettes[context.current_palette].name;
    if (ImGui::BeginCombo("Current palette", current_palette_name.c_str())) {
        for (int i = 0; i < static_cast<int>(context.palettes.size()); i++) {
            const Palette& p = context.palettes[i];
            if (ImGui::Selectable(p.name.c_str(), i == context.current_palette)) {
                context.current_palette = i;
                context.need_render = true;
            }

            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            ImVec2 pos = ImGui::GetItemRectMin();
            ImVec2 size = ImGui::GetItemRectSize();
            float gradient_x = pos.x + size.x / 2.0f;

            int n = p.colors.size();
            for (int j = 0; j < n - 1; j++) {
                float x0 = gradient_x + (120.0f * j) / (n - 1);
                float x1 = gradient_x + (120.0f * (j + 1)) / (n - 1);
                draw_list->AddRectFilledMultiColor(
                    ImVec2(x0, pos.y + 2), ImVec2(x1, pos.y + size.y - 2),
                    ImGui::ColorConvertFloat4ToU32(to_imvec4(p.colors[j])),
                    ImGui::ColorConvertFloat4ToU32(to_imvec4(p.colors[j + 1])),
                    ImGui::ColorConvertFloat4ToU32(to_imvec4(p.colors[j+1])),
                    ImGui::ColorConvertFloat4ToU32(to_imvec4(p.colors[j]))
                );
            }
        }
        ImGui::EndCombo();
    }

    for (size_t i = 0; i < context.palettes[context.current_palette].colors.size(); i++) {
        std::string id = "##color" + std::to_string(i);
        if (ImGui::ColorButton(id.c_str(), to_imvec4(context.palettes[context.current_palette].colors[i]), 0, ImVec2(30, 30))) {
            _editing_color_index = i;
            ImGui::OpenPopup("color_picker_popup");
        }
        ImGui::SameLine();
    }

    if (ImGui::Button("+", ImVec2(30, 30))) {
        context.palettes[context.current_palette].colors.push_back(RGBA{255, 255, 255, 255});
        _editing_color_index = context.palettes[context.current_palette].colors.size() - 1;
        ImGui::OpenPopup("color_picker_popup");
    }

    ImGui::NewLine();
    ImGui::InputText("Name", &context.palettes[context.current_palette].name);
    if (ImGui::InputDouble("Cycle length", &context.palettes[context.current_palette].cycle_length)) {
        context.need_render = true;
    }

    if (ImGui::BeginPopup("color_picker_popup")) {
        RGBA& color = context.palettes[context.current_palette].colors[_editing_color_index];
        float col[4] = {color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f};
        if (ImGui::ColorPicker4("##picker", col)) {
            color.r = static_cast<uint8_t>(col[0] * 255.0f);
            color.g = static_cast<uint8_t>(col[1] * 255.0f);
            color.b = static_cast<uint8_t>(col[2] * 255.0f);
            color.a = static_cast<uint8_t>(col[3] * 255.0f);
            context.need_render = true;
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}

void UI::display_fractal_settings_panel(UIContext& context) {
    if (!ImGui::Begin("Fractal settings")) {
        ImGui::End();
        return;
    }

    if (ImGui::InputText("Real", &context.render_params.center_real)) {
        context.need_render = true;
    }
    if (ImGui::InputText("Imaginary", &context.render_params.center_imag)) {
        context.need_render = true;
    }

    int max_iterations = static_cast<int>(context.iteration_params.max_iterations);
    if (ImGui::InputInt("Max iterations", &max_iterations)) {
        context.iteration_params.max_iterations = static_cast<uint32_t>(std::max(0, max_iterations));
        context.need_render = true;
    }
    ImGui::End();
}

void UI::display_rendering_panel(UIContext& context) {
    if (!ImGui::Begin("Rendering options")) {
        ImGui::End();
        return;
    }

    int current_backend = static_cast<int>(context.backend);
    if (ImGui::Combo("Backend", &current_backend, backend_names, IM_ARRAYSIZE(backend_names))) {
        context.backend = static_cast<Backend>(current_backend);
    }

    ImGui::Checkbox("Cardioid check", &context.iteration_params.cardioid_check);
    ImGui::SameLine();
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::Text("Skip iteration for points known to be inside");
        ImGui::Text("the main cardioid or period-2 bulb.");
        ImGui::Text("Enable only if the rendered area contains");
        ImGui::Text("pixels inside of these regions.");
        ImGui::EndTooltip();
    }

    ImGui::Separator();
    if (ImGui::Checkbox("Smooth coloring", &context.smooth_coloring)) {
        context.need_render = true;
    }

    ImGui::End();
}
