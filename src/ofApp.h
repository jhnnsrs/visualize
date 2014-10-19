#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"

class ofApp : public ofBaseApp{

	public:
		bool fullscreen;
		ofxPostProcessing post;
		ofMesh	mesh;
		ofEasyCam cam;
		ofVec3f a,b,c,d;
		ofVec3f* s;
		ofVec3f* t;
		ofVec3f* u;
		ofVec3f* v;

		vector<ofVec3f> allvectors;
		int nvertices,nadded;
		long zeit;
		int smod,tmod,umod,vmod;
		int suv,stv,tuv;
		void setup();
		void update();
		void draw();

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
