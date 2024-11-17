#pragma once
#include "ofMain.h"
#include "ofxImGui.h"


class ParamGui {
public:
    void setup();
    void draw();


    ofxImGui::Gui gui;


};


/*
TODO
1. plot global charge
2. plot avarage charge
3. plot global brightness
4. varying radius for each firefly?
*/