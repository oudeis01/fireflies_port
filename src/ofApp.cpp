#include "ofApp.h"

// 70 not reached
// 80 reached
#define RADIUS 75

void ofApp::blinkEvent(FireflyEvent & e) {
    

    int count = 0;
    for(size_t i=0; i<fireflies.size(); i++) {
        if(fireflies[i].start_offset_frame > ofGetFrameNum()) continue;
        if(e.idx == i) continue;
        if(glm::distance(fireflies[i].pos, e.pos) < RADIUS) {
            fireflies[i].deltaCharge();
            count++;
        }
    }
    if(count > 0) {
        ofLog() << "blinkEvent: " << e.idx << " " << count;
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

    // find the main firefly closest to the center of the screen
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
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(auto& f : fireflies) {
        f.draw();
    }


    ofSetColor(255);
    stringstream ss;
    ss << "fps" << '\t' << ofGetFrameRate() << endl;
    for(int i=0; i<10; ++i){
        ss << (fireflies[i].isDischarging?"dis":"chg") << '\t';
        ss << fireflies[i].value << '\n';
    }

    ofPushStyle();
    ofSetColor(255,0,0);
    ofNoFill();
    ofDrawCircle(main_firefly->pos, RADIUS);
    ofPopStyle();


    ofDrawBitmapString(ss.str(), 20, 20);

    gui.draw();


}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
