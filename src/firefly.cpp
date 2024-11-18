#include "firefly.h"

ofEvent<FireflyEvent> Firefly::onFireflyBlink = ofEvent<FireflyEvent>();
float Firefly::default_brightness = 30;
float Firefly::increment = 0.004;
float Firefly::decrement = 0.03;
float Firefly::delta = 0.2;

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
    value += Firefly::increment;
    if(value > 1) {
        value = 1;
        isDischarging = true;
        isBlinking = true;
    }
    if(isDischarging) {
        value -= Firefly::decrement;
        if(value <= 0) {
            value = 0;
            isDischarging = false;
        }
    }
    if(isDischarging) {
        brightness = ofClamp(ofMap(value, 0, 1, 0, 255), Firefly::default_brightness, 255);
            
    }
    else {
        brightness = Firefly::default_brightness;
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
    if(isDischarging) value-=Firefly::delta*0.1;
    else value += Firefly::delta;
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

void Firefly::reset() {
    // this->pos = glm::vec2(ofRandomuf()*ofGetWidth(), ofRandomuf()*ofGetHeight());
    this->vel = glm::vec2(ofRandomf(), ofRandomf());
    this->vel *= 0.1;
    this->brightness = ofRandom(100, 255);
    this->value = ofRandomuf();
    this->start_offset_frame = ofRandom(60, 60*5) + ofGetFrameNum();
}