#include "ofApp.h"
#include <ctime>
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofEnableDepthTest();
	srand(time(0));
	fullscreen = false;
	nfragments = 0;
	isrestart = 0;

	central[0].init();
	/*
	central[1].init(ofVec3f(34,5,67),ofVec3f(0,5,67),ofVec3f(2,5,67),ofVec3f(34,5,0));
	central[2].init(ofVec3f(34,0,67),ofVec3f(0,5,35),ofVec3f(2,0,100),ofVec3f(94,5,0));
	central[3].init(ofVec3f(0,5,35),ofVec3f(2,0,100),ofVec3f(94,5,0),ofVec3f(34,0,67));
	central[4].init(ofVec3f(34,0,67),ofVec3f(2,0,100),ofVec3f(0,5,35),ofVec3f(94,5,0));
	central[5].init(ofVec3f(2,0,100),ofVec3f(34,0,67),ofVec3f(0,5,35),ofVec3f(94,5,0));*/

	cout << "HUHU";
	post.init(1920, 1080);
	post.createPass<FxaaPass>();
	post.createPass<LimbDarkeningPass>();

	
	zeit = ofGetElapsedTimeMillis();
	zeit2 = ofGetElapsedTimeMillis();
	zeit3 = ofGetElapsedTimeMillis();
	ofColor color(255,255,0);
	
	
}

//--------------------------------------------------------------
void ofApp::update(){

	/// Do you want to branch?
	if (isrestart == 1 & isrestart2 != 1) {
		for (JCentralFragment &i: central)
			{
			i.branch(9);
			}
		isrestart2 = 1;
	}
	
	// SPAWN NEW TRIANGLE
	if ( ofGetElapsedTimeMillis() > zeit + 100){
		for (JCentralFragment &i: central)
			{
			i.update();
			}
		
		zeit = ofGetElapsedTimeMillis();
	}

	// CREATE NEW FRAGMENT
	if ( ofGetElapsedTimeMillis() > zeit2 + 1000){
		for (JCentralFragment &i: central)
			{
			JFragment* x = new JFragment;
			x = i.collapse(x,9);
			/*cout << x->mesh.getNumVertices() << " OUTER VERTEX" <<endl;*/
			fragments.push_back(*x);
			nfragments++;
			
			/*cout << fragments[nfragments-1].mesh.getVertex(0);*/
			}		
		zeit2 = ofGetElapsedTimeMillis();
		
	}

	// UPDATE POSITION OF FRAGMENT
	if ( ofGetElapsedTimeMillis() > zeit3 + 1){
		for (JFragment &i: fragments)
			{
			i.update();
			}
		
		zeit3 = ofGetElapsedTimeMillis();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    //ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);

	cam.begin();
	post.begin(cam);
	ofBackground(ofColor(0,0,0));
	ofPushMatrix();
		ofRotateZ(ofGetElapsedTimef()*10);
		ofRotateY(ofGetElapsedTimef()*10);
		ofRotateX(ofGetElapsedTimef()*10);
		// Draw central figures
		for(JCentralFragment &z: central)
		{
			z.mesh.draw();
		}
		// Draw orbiting figures
		for (JFragment &i: fragments)
			{
			ofPushMatrix();
				ofTranslate(i.getTranslation(ofGetElapsedTimef()));
				i.mesh.draw();
			ofPopMatrix();
			}
	ofPopMatrix();post.end();
	cam.end();
	ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()),10,10,0);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	if (key == 102) {
		fullscreen = !fullscreen;
		ofSetFullscreen(fullscreen);
	}
	if (key == 103) {
		isrestart = 1;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
	if (key == 103) {
		isrestart = 0;
		isrestart2 = 0;
	}

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
