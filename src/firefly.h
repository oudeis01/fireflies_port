#pragma once
#include "ofMain.h"

class FireflyEvent : public ofEventArgs {
public:
    glm::vec2 pos;
    int idx;
};

class Firefly {
public:
    void setup(glm::vec2 pos, glm::vec2 vel, float brightness, float value);
    void update();
    void draw();
    void unBlink();
    void deltaCharge();
    void reset();

    glm::vec2 pos;
    glm::vec2 vel;
    float brightness;
    float value;
    static float default_brightness;
    static float increment;
    static float decrement;
    static float delta;
    int start_offset_frame;
    bool isDischarging=false;
    bool isBlinking=false;


    static ofEvent<FireflyEvent> onFireflyBlink;
};