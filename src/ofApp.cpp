#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableDepthTest();

	smod = 3;
	tmod = 2;
	umod = 1;
	vmod = 0;

	nvertices = 0;
	nadded = 0;
	zeit = ofGetElapsedTimeMillis();
	mesh.enableIndices();
	ofColor color(255,255,0);
	

	a = ofVec3f(0,0,0);
	b =	ofVec3f(100,0,0);
	c = ofVec3f(0,100,0);
	d = ofVec3f(0,50,100);
	mesh.addVertex(a);
	allvectors.push_back(a);
	mesh.addColor(ofColor(255,0,0));

	mesh.addVertex(b);
	allvectors.push_back(b);
	mesh.addColor(ofColor(0,255,0));

	mesh.addVertex(c);
	allvectors.push_back(c);
	mesh.addColor(ofColor(0,0,255));

	mesh.addVertex(d);
	allvectors.push_back(d);
	mesh.addColor(ofColor(255,0,255));

	nvertices = nvertices+3;
	cout << mesh.getNumVertices()-1 << endl;
	cout << nvertices << endl;
	cout << allvectors.size()-1 << endl;
	mesh.addIndex(0);
	mesh.addIndex(1);
	mesh.addIndex(3);

	mesh.addIndex(0);
	mesh.addIndex(1);
	mesh.addIndex(2);

	mesh.addIndex(1);
	mesh.addIndex(2);
	mesh.addIndex(3);

	mesh.addIndex(0);
	mesh.addIndex(3);
	mesh.addIndex(2);


}

//--------------------------------------------------------------
void ofApp::update(){


	if ( ofGetElapsedTimeMillis() > zeit + 1000 && nadded < 4)
	{
		
		ofVec3f s = allvectors[nvertices-smod];
		ofVec3f t = allvectors[nvertices-tmod];
		ofVec3f u = allvectors[nvertices-umod];
		ofVec3f v = allvectors[nvertices-vmod];

		if (nadded == 0){
			a = s;
			b = t;
			c = u;
			d = v;
		}
		if (nadded == 1){
			a = t;
			b = u;
			c = s;
			d = v;
		}
		if (nadded == 2){
			a = u;
			b = s;
			c = t;
			d = v;
		}

		ofVec3f n,m,z,newv;

		n = (b-a).crossed(d-a);
		m = b + (d-b)/2;
		z = a + 0.666f*(m-a);

		newv = z + n.normalized()*30.0f;

		mesh.addVertex(newv);
		allvectors.push_back(newv);
		nvertices++;

		if (nadded == 0){
			smod++;
			tmod++;
		}

		if (nadded == 1){
			umod++;
			smod++;
		}

		if (nadded == 2){
			tmod++;
			umod++;
		}
		
		
		cout << nvertices-smod << " " << nvertices-tmod << " " << nvertices-vmod << endl;
		mesh.addIndex(nvertices - smod);
		mesh.addIndex(nvertices - tmod);
		mesh.addIndex(nvertices);

		mesh.addIndex(nvertices - tmod);
		mesh.addIndex(nvertices - umod);
		mesh.addIndex(nvertices);

		mesh.addIndex(nvertices - umod);
		mesh.addIndex(nvertices - smod);
		mesh.addIndex(nvertices);

		zeit = ofGetElapsedTimeMillis();
		
		cout << mesh.getNumVertices()-1 << endl;
		cout << nvertices << endl;
		cout << allvectors.size()-1 << endl;
		
		nadded++;
		if (nadded ==3){ nadded = 5;}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(122,122,122);
	cam.begin();
	mesh.drawWireframe();
	cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
