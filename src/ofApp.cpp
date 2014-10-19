#include "ofApp.h"
#include <ctime>
//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableDepthTest();
	srand(time(0));
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
	
	 mesh.setMode(OF_PRIMITIVE_TRIANGLES);

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

	nvertices = nvertices + 3;

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

	
	// Set Pointers to Initial Triangle
	s = &allvectors[0];
	t = &allvectors[1];
	u = &allvectors[2];
	v = &allvectors[3];
}

//--------------------------------------------------------------
void ofApp::update(){


	if ( ofGetElapsedTimeMillis() > zeit + 100)
	{
		// Select random side
		
		nadded = 0 + (rand() % (int)(2 + 1));

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

		float randomness = ofMap(ofSignedNoise(ofGetElapsedTimef(),z.x,z.y,z.z),-1,1,0,1)*200;
		newv = z + n.normalized()*randomness;

		// Dirty, because vectors in C++ do not allow pointers to elements,
		// within the vector when it allocates new memory. Reference and pointers
		// return garbage. Python <3 
		smod =  s - &allvectors[0];
		tmod =  t - &allvectors[0];
		umod =  u - &allvectors[0];
		vmod =  v - &allvectors[0];

		// Add vector to mesh
		mesh.addVertex(newv);
		mesh.addColor(ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)));
		allvectors.push_back(newv);
		nvertices++;

		// Rereference pointers
		s = &allvectors[smod];
		t = &allvectors[tmod];
		u = &allvectors[umod];
		v = &allvectors[vmod];

		
		
		// Change to new pyramid, wuhu beautiful
		
		if (nadded == 0){
			u = t;
			t = s;
			
		}

		if (nadded == 1){
			u = u;
			t = t;
				 
		}

		if (nadded == 2){
			t = u;
			u = s;
		}

		s = v;
		v = &allvectors[nvertices];

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

		mesh.addIndex(s - &allvectors[0]);
		mesh.addIndex(t - &allvectors[0]);
		mesh.addIndex(u - &allvectors[0]);


		zeit = ofGetElapsedTimeMillis();
		
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(122,122,122);
	cam.begin();
		ofPushMatrix();
			ofRotateZ(ofGetElapsedTimef()*0.01);
			mesh.draw();
		ofPopMatrix();
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
