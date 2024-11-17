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


    glm::vec2 pos;
    glm::vec2 vel;
    float brightness;
    float value;
    float default_brightness= 30;
    float increment=0.004;
    float decrement=0.03;
    float delta=0.2;
    int start_offset_frame;
    bool isDischarging=false;
    bool isBlinking=false;


    static ofEvent<FireflyEvent> onFireflyBlink;
};