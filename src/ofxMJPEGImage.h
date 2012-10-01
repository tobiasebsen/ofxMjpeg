#ifndef _MJPEG_IMAGE
#define _MJPEG_IMAGE

/*
 *  ofxMJPEGImage.h
 *  ofxMjpeg
 *
 *  Created by Tobias Ebsen on 3/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include <FreeImage.h>

#define MJPEG_READYTO_READ		0
#define MJPEG_READYTO_CONVERT	1
#define MJPEG_READYTO_DRAW		2

class MJPEGImage {
	
	public:
		MJPEGImage();
		~MJPEGImage();
		void read(istream* stream, int size);
		void read(char* data, int size);
		void convert();
	
		int getWidth();
		int getHeight();
		unsigned char* getPixels();
	
		int getStatus();
		void setStatus(int status);
	
	private:
		FIMEMORY *memory;
		unsigned char* pixels;
		int size;
		int width;
		int height;
		int status;
};

#endif