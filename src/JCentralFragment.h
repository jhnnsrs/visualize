#pragma once

#include "ofMain.h"
#include "JFragment.h"


class JCentralFragment
{
public:
	ofMesh	mesh;
	ofVec3f a,b,c,d;
	ofVec3f* s;
	ofVec3f* t;
	ofVec3f* u;
	ofVec3f* v;
	int smod,tmod,umod,vmod;
	
	vector<ofVec3f> allvectors;
	int nvertices,nadded;
	long zeit;
	void update();
	void init();
	void restart();
	void branch(int there);
	void init(ofVec3f	a, ofVec3f b, ofVec3f c, ofVec3f d);
	void setInitialPyramid(ofVec3f	a, ofVec3f b, ofVec3f c, ofVec3f d);
	
	JCentralFragment();
	~JCentralFragment();
	
	JFragment* collapse(JFragment* frag,int size,ofColor color);
private:


};