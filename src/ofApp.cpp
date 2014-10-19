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
		
		// Select last pyramid as working pyramid
		// modifiers specify the chosen vertices
		ofVec3f s = allvectors[nvertices-smod];
		ofVec3f t = allvectors[nvertices-tmod];
		ofVec3f u = allvectors[nvertices-umod];
		ofVec3f v = allvectors[nvertices-vmod];

		// Rotate pyramide so that the spawn side
		// can be interpreted as A,B,C (Base) and D
		// peak. The base is not considered a spawning
		// side, as this may mess with the 3d structure.

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


		// Increment all modifiers
		umod++;
		smod++;
		tmod++;
		vmod++;

		// Add sides (triangles) to the mesh
		cout << nvertices-smod << " " << nvertices-tmod << " " << nvertices-vmod << endl;

		if (nadded == 0){
		mesh.addIndex(nvertices - smod);
		mesh.addIndex(nvertices - tmod);
		mesh.addIndex(nvertices);

		mesh.addIndex(nvertices - tmod);
		mesh.addIndex(nvertices - vmod);
		mesh.addIndex(nvertices);

		mesh.addIndex(nvertices - smod);
		mesh.addIndex(nvertices - vmod);
		mesh.addIndex(nvertices);
		}

		if (nadded == 1){
		mesh.addIndex(nvertices - tmod);
		mesh.addIndex(nvertices - umod);
		mesh.addIndex(nvertices);

		mesh.addIndex(nvertices - tmod);
		mesh.addIndex(nvertices - vmod);
		mesh.addIndex(nvertices);

		mesh.addIndex(nvertices - umod);
		mesh.addIndex(nvertices - vmod);
		mesh.addIndex(nvertices);
		}

		if (nadded == 2){
		mesh.addIndex(nvertices - tmod);
		mesh.addIndex(nvertices - vmod);
		mesh.addIndex(nvertices);

		mesh.addIndex(nvertices - tmod);
		mesh.addIndex(nvertices - umod);
		mesh.addIndex(nvertices);

		mesh.addIndex(nvertices - umod);
		mesh.addIndex(nvertices - vmod);
		mesh.addIndex(nvertices);
		}

		// Decrement Modifiers, depending on spawn side
		// TODO: Breaks my brain. MACH MA HINNE LUKAS
		// Hardcoded numbers must dynamically change on count of
		// oparations from one side
		if (nadded == 0){
			umod--;
			vmod--;
		}

		if (nadded == 1){
			smod = smod - 3;
			vmod--;
		}

		if (nadded == 2){
			smod--;
			vmod--;
		}

		zeit = ofGetElapsedTimeMillis();
		
		cout << mesh.getNumVertices()-1 << endl;
		cout << nvertices << endl;
		cout << allvectors.size()-1 << endl;
		
		nadded++;
		if (nadded ==3){ nadded = 6;}
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
