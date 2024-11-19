#include "gui.h"

#define PLOT_WIDTH 400
#define PLOT_HEIGHT 100
#define DENSITY 8


void ParamGui::setup() {
    gui.setup(nullptr, true, ImGuiConfigFlags_ViewportsEnable,false);
    ImGui::StyleColorsDark();
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.24f*0.7, 0.52f*0.7, 0.88f*0.7, 1.00f);
    ofFbo::Settings fboSettings;
    fboSettings.width = PLOT_WIDTH;
    fboSettings.height = PLOT_HEIGHT;
    fboSettings.internalformat = GL_RGBA ;
    fboSettings.textureTarget = GL_TEXTURE_2D ;
    fbo_charge_plot.allocate(fboSettings) ;
    fbo_brightness_plot.allocate(fboSettings) ;
}

void ParamGui::draw(int& radius, float& delta, float& increment, float& decrement, float& default_brightness, bool& _reset, float etime_offset) {
    gui.begin();
    ImGui::Begin("Parameters");
    ImGui::Text("Elapsed %.1f", ofGetElapsedTimef()-etime_offset);
    ImGui::SliderInt("radius", &radius, 0.0, 200.0, "%d", ImGuiSliderFlags_None);
    ImGui::SliderFloat("delta", &delta, 0.0, 0.5, "%.3f", ImGuiSliderFlags_None);
    ImGui::SliderFloat("inc", &increment, 0.0, 0.5, "%.3f", ImGuiSliderFlags_None);
    ImGui::SliderFloat("dec", &decrement, 0.0, 0.5, "%.3f", ImGuiSliderFlags_None);
    ImGui::SliderFloat("b(def)", &default_brightness, 0.0, 255.0, "%.3f", ImGuiSliderFlags_None);
    ImGui::Text("%.3f charge(avg)", average_charge); ImGui::SameLine();
    ImGui::ProgressBar(average_charge, ImVec2(-FLT_MIN,0.0f));
    ImGui::Image(
        (ImTextureID)(uintptr_t)fbo_charge_plot.getTexture().getTextureData().textureID,
        ImVec2(PLOT_WIDTH, PLOT_HEIGHT),
        ImVec2(0, 1), ImVec2(1, 0),
        ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
        ImGui::GetStyleColorVec4(ImGuiCol_Border)
        );
    ImGui::Text("%.3f bright(avg)", average_brightness);ImGui::SameLine();
    ImGui::ProgressBar(average_brightness, ImVec2(-FLT_MIN,0.0f));
    ImGui::Image(
        (ImTextureID)(uintptr_t)fbo_brightness_plot.getTexture().getTextureData().textureID,
        ImVec2(PLOT_WIDTH, PLOT_HEIGHT),
        ImVec2(0, 1), ImVec2(1, 0),
        ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
        ImGui::GetStyleColorVec4(ImGuiCol_Border)
        );
    _reset = ImGui::Button("reset");
    ImGui::End();

    gui.end();
}

void ParamGui::computeAverageCharge(vector<Firefly>& fireflies) {
    double sum = 0;
    for(auto& f : fireflies) {
        sum += f.value;
    }
    sum /= fireflies.size();
    average_charge = sum;
    charge_plot_data.push_back(1.f-average_charge);
    if(charge_plot_data.size() > PLOT_WIDTH*DENSITY){
        charge_plot_data.erase(charge_plot_data.begin());
        plot_offset+=1.f/(float)DENSITY;
    }
}

void ParamGui::computeAverageBrightness(vector<Firefly>& fireflies) {
    float sum = 0;
    for(auto& f : fireflies) {
        sum += f.brightness;
    }
    sum /= fireflies.size();
    average_brightness = sum/255.f;
    brightness_plot_data.push_back(1.f-average_brightness);
    if(brightness_plot_data.size() > PLOT_WIDTH*DENSITY){
        brightness_plot_data.erase(brightness_plot_data.begin());
    }
}

void ParamGui::updatePlot() {
    fbo_charge_plot.begin();
    ofNoFill();
    ofClear(0,0,0,0);
    ofSetColor(80);
    ofDrawLine(0, PLOT_HEIGHT/3, PLOT_WIDTH, PLOT_HEIGHT/3);
    ofDrawLine(0, 2*PLOT_HEIGHT/3, PLOT_WIDTH, 2*PLOT_HEIGHT/3);
    ofDrawLine(PLOT_WIDTH/4, 0, PLOT_WIDTH/4, PLOT_HEIGHT);
    ofDrawLine(PLOT_WIDTH/4*2, 0, PLOT_WIDTH/4*2, PLOT_HEIGHT);
    ofDrawLine(PLOT_WIDTH/4*3, 0, PLOT_WIDTH/4*3, PLOT_HEIGHT);
    ofSetColor(255);
    ofBeginShape();
    for(size_t i=0; i<charge_plot_data.size(); i++) {
        ofVertex(float(i)/DENSITY, PLOT_HEIGHT-charge_plot_data[i]*PLOT_HEIGHT);
    }
    ofEndShape();
    ofFill();
    fbo_charge_plot.end();

    fbo_brightness_plot.begin();
    ofNoFill();
    ofClear(0,0,0,0);
    ofSetColor(80);
    ofDrawLine(0, PLOT_HEIGHT/3, PLOT_WIDTH, PLOT_HEIGHT/3);
    ofDrawLine(0, 2*PLOT_HEIGHT/3, PLOT_WIDTH, 2*PLOT_HEIGHT/3);
    ofDrawLine(PLOT_WIDTH/4, 0, PLOT_WIDTH/4, PLOT_HEIGHT);
    ofDrawLine(2*PLOT_WIDTH/4, 0, 2*PLOT_WIDTH/4, PLOT_HEIGHT);
    ofDrawLine(3*PLOT_WIDTH/4, 0, 3*PLOT_WIDTH/4, PLOT_HEIGHT);
    ofSetColor(255);
    ofBeginShape();
    for(size_t i=0; i<brightness_plot_data.size(); i++) {
        ofVertex(float(i)/DENSITY, PLOT_HEIGHT-brightness_plot_data[i]*PLOT_HEIGHT);
    }
    ofEndShape();
    ofFill();
    fbo_brightness_plot.end();
}

