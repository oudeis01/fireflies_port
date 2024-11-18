#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "firefly.h"


class ParamGui {
public:
    void setup();
    void draw(int& radius, float& delta, float& increment, float& decrement, float& default_brightness, bool& _reset);
    void computeAverageCharge(vector<Firefly>& fireflies);
    void computeAverageBrightness(vector<Firefly>& fireflies);
    void updatePlot();

    ofxImGui::Gui gui;
    float average_charge;
    float average_brightness;
    ofFbo fbo_charge_plot;
    ofFbo fbo_brightness_plot;
    vector<float> charge_plot_data;
    vector<float> brightness_plot_data;
    float plot_offset;
};


/*
TODO
1. plot global charge
2. plot avarage charge
3. plot global brightness
4. varying radius for each firefly?
*/