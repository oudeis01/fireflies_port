#include "firefly.h"

ofEvent<FireflyEvent> Firefly::onFireflyBlink = ofEvent<FireflyEvent>();

void Firefly::setup(glm::vec2 pos, glm::vec2 vel, float brightness, float value) {
    this->pos = pos;
    this->vel = vel;
    this->brightness = brightness;
    this->value = value;
    this->start_offset_frame = ofRandom(60*5, 60*10);
}


void Firefly::update() {
    pos += vel;
    if (pos.x < 0 || pos.x > ofGetWidth()) {
        vel.x *= -1;
    }
    if (pos.y < 0 || pos.y > ofGetHeight()) {
        vel.y *= -1;
    }
    // if(start_offset_frame > ofGetFrameNum()) return;
    value += increment;
    if(value > 1) {
        value = 1;
        isDischarging = true;
        isBlinking = true;
    }
    if(isDischarging) {
        value -= decrement;
        if(value <= 0) {
            value = 0;
            isDischarging = false;
        }
    }
    if(isDischarging) {
        brightness = ofClamp(ofMap(value, 0, 1, 0, 255), default_brightness, 255);
            
    }
    else {
        brightness = default_brightness;
    }
}

void Firefly::draw() {
    ofSetColor(255, 255, 255, brightness);
    ofDrawCircle(pos, 5);
}

void Firefly::unBlink() {
    isBlinking = false;
}

void Firefly::deltaCharge() {
    if(isDischarging) value-=delta*0.1;
    else value += delta;
    if(value > 1) {
        value = 1;
        isDischarging = true;
        isBlinking = true;
    }
    if(value<=0) {
        value = 0;
        isDischarging = false;
    }
}