#ifndef _MJPEG_CLIENT
#define _MJPEG_CLIENT

/*
 *  ofxMJPEGClient.h
 *  ofxMjpeg
 *
 *  Created by Tobias Ebsen on 3/21/11.
 *  Copyright 2011 Tobias Ebsen. All rights reserved.
 *
 */

#include "ofMain.h"
#include "Poco/Net/HTTPClientSession.h"
#include "ofxMJPEGReader.h"
#include "ofxMJPEGConverter.h"
#include "ofxMJPEGImage.h"


class MJPEGClient {

	public:
		MJPEGClient();
		~MJPEGClient();
		
		void connect(string url);
		void grabFrame();
		bool isFrameNew();
		void draw(float x, float y);
		unsigned char* getPixels();
		int getWidth();
		int getHeight();
	
		MJPEGImage* getImage(int status);
	
	private:
		Poco::Net::HTTPClientSession* session;
		MJPEGReader* reader;
		MJPEGConverter* converter;
		vector<MJPEGImage*> images;
		bool frameNew;
		unsigned char* pixels;
		int width;
		int height;
		int size;
		ofTexture texture;
};

#endif