#ifndef _MJPEG_READER
#define _MJPEG_READER

/*
 *  ofxMJPEGReader.h
 *  ofxMjpeg
 *
 *  Created by Tobias Ebsen on 3/21/11.
 *  Copyright 2011 Tobias Ebsen. All rights reserved.
 *
 */


#include "ofMain.h"
#include "ofxThread.h"

typedef class MJPEGClient;
typedef class MJPEGImage;

class MJPEGReader : public ofxThread {

	public:
		MJPEGReader(MJPEGClient* client, istream* stream);
		~MJPEGReader();
		void threadedFunction();
	
	private:
		MJPEGClient* client;
		istream* stream;
		char* buffer;
		int capacity;
};

#endif