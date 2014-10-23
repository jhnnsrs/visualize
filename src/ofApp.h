#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"
#include "JCentralFragment.h"
#include "JFragment.h"
#include "JOSCThread.h"

// Visualize Software
// Features:
//		- Central Fragment Spawing Triangles
//		- LiveOSC integration via JOSCThread

class ofApp : public ofBaseApp{

	public:
		// Global Variables
		bool fullscreen;

		// Time variables
		long zeit,zeit2,zeit3;

		// OSC Control Interface
		JOSCThread oscthread;

		// Processing, Matrixes and Light
		ofxPostProcessing post;
		ofLight spotlight;
		ofLight ambientlight;
		ofEasyCam cam;
		
		// Figures
		JCentralFragment central[6];
		vector<JFragment> fragments;

		// Indexes of Figures
		int ncentral;
		int nfragments;
		int isrestart,isrestart2;

		// Functions of Openframework
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};



