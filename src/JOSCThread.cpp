#include "JOSCThread.h"


JOSCThread::JOSCThread(void)
{
	sh_beat=0;
	Serve.setup(9001);
}


JOSCThread::~JOSCThread(void)
{
}

void JOSCThread::threadedFunction() {
 
        // start
 
        while(isThreadRunning()) {
 
            while(Serve.hasWaitingMessages()){
		// get the next message
				ofxOscMessage m;
				Serve.getNextMessage(&m);
				if(m.getAddress() == "/live/beat"){
					lock();
					// Set Arrived Message
					sh_beat = m.getArgAsInt32(0);
					// 
					unlock();
					m_nbeatcount += 1;
				}
				
            }   
        }
 
        // done
    }