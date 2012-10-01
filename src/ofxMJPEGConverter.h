#ifndef _MJPEG_CONVERTER
#define _MJPEG_CONVERTER

/*
 *  ofxMJPEGConverter.h
 *  ofxMjpeg
 *
 *  Created by Tobias Ebsen on 3/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxThread.h";

typedef class MJPEGClient;

class MJPEGConverter : public ofxThread {
	
	public:
		MJPEGConverter(MJPEGClient* client);
		void threadedFunction();
	
	private:
		MJPEGClient* client;
};

#endif