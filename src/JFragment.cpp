#include "JFragment.h"


JFragment::JFragment(void)
{
	mesh.enableIndices();
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	starttime = ofGetElapsedTimef();
	direction = ofVec3f(1,0,0);
	velocity = 1000;
}


JFragment::~JFragment(void)
{
}

void JFragment::update() {
	float t = ofGetElapsedTimef() - starttime;
	velocity -= t*0.0002;
	if (velocity <= 10) velocity = 10;


}

ofVec3f JFragment::getTranslation(float time){

	float dtime = time - starttime;

	ofVec3f position = direction*velocity*dtime;

	return position;
}