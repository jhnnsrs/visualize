#pragma once
#include "ofMain.h"
#include "ofxOsc.h"

class JOSCThread : public ofThread
{
private:
	ofxOscMessage m;
	ofxOscReceiver Serve;
public:
	// Is set on Beat
	int sh_beat;
	int m_nbeatcount;
	JOSCThread(void);
	~JOSCThread(void);

	// Is called when thread start
	void threadedFunction();
};

