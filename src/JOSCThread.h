#pragma once
#include "ofMain.h"
#include "ofxOsc.h"

class JOSCThread : public ofThread
{
private:
	ofxOscMessage m;
	ofxOscReceiver Serve;
public:
	int sh_beat;
	JOSCThread(void);
	~JOSCThread(void);
	void threadedFunction();
};

