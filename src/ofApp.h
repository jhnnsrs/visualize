#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"
#include "JCentralFragment.h"
#include "JFragment.h"
#include "JOSCThread.h"


class ofApp : public ofBaseApp{

	public:

		bool fullscreen;
		// Three times that are used to create the pyramids,fragments and update them
		long zeit,zeit2,zeit3;
		ofxPostProcessing post;
		ofLight spotlight;
		ofLight ambientlight;
		JOSCThread oscthread;
		
		ofEasyCam cam;
		JCentralFragment central[6];
		vector<JFragment> fragments;
		int nfragments;
		int isrestart,isrestart2;

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



