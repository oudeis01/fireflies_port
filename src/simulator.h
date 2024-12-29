#pragma once

#include "ofMain.h"
#include "gui.h"
#include "firefly.h"
#include "ofxTextureRecorder.h"
#define NUM_FIREFLIES 1500

class Simulator : public ofBaseApp{

public:
	void setup() override;
	void update() override;
	void draw() override;
	void exit() override;
	void keyPressed(int key) override;
	void blinkEvent(FireflyEvent& e);

	float width, height;
	vector<Firefly> fireflies;
	Firefly* main_firefly;
	ParamGui gui;
	static int RADIUS;
	bool breset;
	bool bdebug=true;
	float etime_offset;
	

	ofxTextureRecorder recorder;
	ofFbo fbo;

		
};
