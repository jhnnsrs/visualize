#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableDepthTest();

	smod = 3;
	tmod = 2;
	umod = 1;
	vmod = 0;
	suv = 1;
	tuv = 1;
	stv = 1;

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

	
	s = &allvectors[nvertices-smod];
	t = &allvectors[nvertices-tmod];
	u = &allvectors[nvertices-umod];
	v = &allvectors[nvertices-vmod];


}

//--------------------------------------------------------------
void ofApp::update(){


	if ( ofGetElapsedTimeMillis() > zeit + 1000 && nadded < 4)
	{
		
		// Select last pyramid as working pyramid
		// modifiers specify the chosen vertices

		// Rotate pyramide so that the spawn side
		// can be interpreted as A,B,C (Base) and D
		// peak. The base is not considered a spawning
		// side, as this may mess with the 3d structure.

		if (nadded == 0){
			a = *s;
			b = *t;
			c = *u;
			d = *v;
		}
		if (nadded == 1){
			a = *t;
			b = *u;
			c = *s;
			d = *v;
		}
		if (nadded == 2){
			a = *u;
			b = *s;
			c = *t;
			d = *v;
		}

		// Calculate barycenter of base (z, with help of m)
		// normal vector (n) of base and hence the new peak of the
		// pyramid (newv)
		ofVec3f n,m,z,newv;

		n = (b-a).crossed(d-a);
		m = b + (d-b)/2;
		z = a + 0.666f*(m-a);

		newv = z + n.normalized()*100.0f;

		// Add vector to mesh
		mesh.addVertex(newv);
		allvectors.push_back(newv);
		nvertices++;


		// Change to new triangle 
		
		if (nadded == 0){
			t = u;
			u = s;
		}

		if (nadded == 1){
			u = t;
			t = s;
				 
		}

		if (nadded == 2){
			t = t;
			u = u;
		}

		s= &allvectors[nvertices-1];
		v= &allvectors[nvertices];
		// Add sides (triangles) to the mesh
		
		mesh.addIndex(s - &allvectors[0]);
		mesh.addIndex(t - &allvectors[0]);
		mesh.addIndex(v - &allvectors[0]);

		mesh.addIndex(s - &allvectors[0]);
		mesh.addIndex(u - &allvectors[0]);
		mesh.addIndex(v - &allvectors[0]);

		mesh.addIndex(u - &allvectors[0]);
		mesh.addIndex(t - &allvectors[0]);
		mesh.addIndex(v - &allvectors[0]);

		// Decrement Modifiers, depending on spawn side
		// TODO: Breaks my brain. MACH MA HINNE LUKAS
		// Hardcoded numbers must dynamically change on count of
		// oparations from one side
		// PROBLEM: When


		zeit = ofGetElapsedTimeMillis();
		
		nadded++;
		if (nadded ==3){ nadded = 0;}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(122,122,122);
	cam.begin();
	mesh.draw();
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
