#include "ofApp.h"

// 70 not reached
// 80 reached
// 75 reached

int ofApp::RADIUS = 95;
//--------------------------------------------------------------
void ofApp::blinkEvent(FireflyEvent & e) {
    for(size_t i=0; i<fireflies.size(); i++) {
        if(fireflies[i].start_offset_frame > ofGetFrameNum()) continue;
        if(e.idx == i) continue;
        if(glm::distance(fireflies[i].pos, e.pos) < ofApp::RADIUS) {
            fireflies[i].deltaCharge();
        }
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(false);
    ofSetFrameRate(60);
    ofSetCircleResolution(100);
    width = ofGetWidth();
    height = ofGetHeight();
    bool engender=false;
    for(size_t i=0; i<NUM_FIREFLIES; i++) {
        glm::vec2 pos = glm::vec2(ofRandomuf()*width, ofRandomuf()*height);
        glm::vec2 vel = glm::vec2(ofRandomf(), ofRandomf());
        vel *= 0.1;
        if(engender) vel *= 0.0;
        engender = !engender;
        float brightness = ofRandom(100, 255);
        float v = ofRandomuf();
        Firefly f;
        f.setup(pos, vel, brightness, v);
        fireflies.push_back(f);
    }

    // find the firefly closest to the center of the screen
    float min_dist = 100000;
    for(auto& f : fireflies) {
        float dist = glm::distance(f.pos, glm::vec2(width/2, height/2));
        if(dist < min_dist) {
            min_dist = dist;
            main_firefly = &f;
        }
    }
    ofAddListener(Firefly::onFireflyBlink, this, &ofApp::blinkEvent);
    gui.setup();

}

//--------------------------------------------------------------
void ofApp::update(){
    for(size_t i=0; i<fireflies.size(); i++) {
        fireflies[i].update();
        if(fireflies[i].isBlinking) {
            FireflyEvent e;
            e.idx = i;
            e.pos = fireflies[i].pos;
            ofNotifyEvent(Firefly::onFireflyBlink, e, this);
            fireflies[i].unBlink();
        }
    }
    gui.computeAverageCharge(fireflies);
    gui.computeAverageBrightness(fireflies);
    gui.updatePlot();

    if(breset){
        for(auto& f : fireflies) {
            f.reset();
        }
        breset = false;
        // find the firefly closest to the center of the screen
        float min_dist = 100000;
        for(auto& f : fireflies) {
            float dist = glm::distance(f.pos, glm::vec2(width/2, height/2));
            if(dist < min_dist) {
                min_dist = dist;
                main_firefly = &f;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(auto& f : fireflies) {
        f.draw();
    }
    if(bdebug){
        ofPushStyle();
        ofSetColor(255,0,0);
        ofNoFill();
        ofDrawCircle(main_firefly->pos, ofApp::RADIUS);
        ofPopStyle();
    }
    

    
    stringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << ofGetFrameRate() << '\t'
    << gui.average_charge << '\t'
    << gui.average_brightness;
    ofSetColor(255);
    ofDrawBitmapString(ss.str(), 10, height-10);

    gui.draw(ofApp::RADIUS, Firefly::delta, Firefly::increment, Firefly::decrement, Firefly::default_brightness, breset);


}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'd'){
        bdebug = !bdebug;
    }
}

//--------------------------------------------------------------
