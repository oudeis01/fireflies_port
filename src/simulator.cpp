#include "simulator.h"

// 70 not reached
// 80 reached
// 75 reached

int Simulator::RADIUS = 95;
//--------------------------------------------------------------
void Simulator::blinkEvent(FireflyEvent & e) {
    for(size_t i=0; i<fireflies.size(); i++) {
        if(fireflies[i].start_offset_frame > ofGetFrameNum()) continue;
        if(e.idx == i) continue;
        if(glm::distance(fireflies[i].pos, e.pos) < Simulator::RADIUS) {
            fireflies[i].deltaCharge();
        }
    }
}

//--------------------------------------------------------------
void Simulator::setup(){
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
    ofAddListener(Firefly::onFireflyBlink, this, &Simulator::blinkEvent);
    gui.setup();



    // // setup screen capture 
    // fbo.allocate(width, height, GL_RGB);
    // ofxTextureRecorder::Settings settings(fbo.getTexture());
    // settings.imageFormat = OF_IMAGE_FORMAT_PNG;
    // settings.numThreads = 64;
    // settings.maxMemoryUsage = 9000000000;
    // settings.folderPath = "frames";
    // recorder.setup(settings);

}

//--------------------------------------------------------------
void Simulator::update(){
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
        etime_offset = ofGetElapsedTimef();
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
void Simulator::draw(){
    // fbo.begin();
    // ofClear(0,0,0,255);
    for(auto& f : fireflies) {
        f.draw();
    }
    if(bdebug){
        ofPushStyle();
        ofSetColor(255,0,0);
        ofNoFill();
        ofDrawCircle(main_firefly->pos, Simulator::RADIUS);
        ofPopStyle();
    }
    

    
    stringstream ss;
    ss << std::fixed << std::setprecision(2);
    
    ss << ofGetElapsedTimef() << '\t'
    << ofGetFrameRate() << '\t'
    << gui.average_charge << '\t'
    << gui.average_brightness;
    ofSetColor(255);
    ofDrawBitmapString(ss.str(), 10, height-10);

    gui.draw(
        Simulator::RADIUS,
        Firefly::delta,
        Firefly::increment,
        Firefly::decrement,
        Firefly::default_brightness,
        breset,
        etime_offset
    );

    // fbo.end();
    // fbo.draw(0,0);

    // if(ofGetElapsedTimef()<60*5){
    //     recorder.save(fbo.getTexture());
    // }else{
    //     ofExit(0);
    // }

}

//--------------------------------------------------------------
void Simulator::exit(){

}

//--------------------------------------------------------------
void Simulator::keyPressed(int key){
    if(key == 'd'){
        bdebug = !bdebug;
    }
}

//--------------------------------------------------------------
