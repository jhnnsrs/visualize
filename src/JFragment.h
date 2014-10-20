#pragma once
#include "ofMain.h"

class JFragment
{
public:
	JFragment(void);
	~JFragment(void);
	
	ofMesh mesh;
	ofVec3f	start;
	ofVec3f direction;
	float velocity;
	float starttime;

	void init();
	void update();
	ofVec3f getTranslation(float time);
};

