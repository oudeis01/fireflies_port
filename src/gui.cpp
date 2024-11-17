#include "gui.h"

void ParamGui::setup() {
    gui.setup(nullptr, true, ImGuiConfigFlags_ViewportsEnable,false);

}

void ParamGui::draw() {
    gui.begin();
    static float delta = 0.2;
    static float increment = 0.004;
    static float decrement = 0.03;
    static float default_brightness = 30;
    ImGui::Begin("Parameters");
    ImGui::SliderFloat("delta", &delta, 0.0, 1.0);
    ImGui::SliderFloat("increment", &increment, 0.0, 1.0);
    ImGui::SliderFloat("decrement", &decrement, 0.0, 1.0);
    ImGui::SliderFloat("default_brightness", &default_brightness, 0.0, 255.0);
    ImGui::End();
    gui.end();
}