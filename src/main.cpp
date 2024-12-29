#include "ofMain.h"
#include "simulator.h"

//========================================================================
int main( ){
	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	settings.windowMode = OF_FULLSCREEN;

	auto window = ofCreateWindow(settings);

	ofRunApp(window, std::make_shared<Simulator>());
	ofRunMainLoop();

}
