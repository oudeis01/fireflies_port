#pragma once

#include "ofMain.h"
#include "firefly.h"
#define NUM_FIREFLIES 400



class ofApp : public ofBaseApp{

public:
	void setup() override;
	void update() override;
	void draw() override;
	void exit() override;
	void keyPressed(int key) override;
	void blinkEvent(FireflyEvent& e);

	float width, height;
	vector<Firefly> fireflies;
	

		
};
