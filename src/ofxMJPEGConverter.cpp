/*
 *  ofxMJPEGConverter.cpp
 *  ofxMjpeg
 *
 *  Created by Tobias Ebsen on 3/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxMJPEGConverter.h"
#include "ofxMJPEGClient.h"

//----------------------------------------------------------
MJPEGConverter::MJPEGConverter(MJPEGClient* client) {
	this->client = client;
}

void MJPEGConverter::threadedFunction() {
	
	while (true) {

		MJPEGImage* image = client->getImage(MJPEG_READYTO_CONVERT);
		if(image != NULL)
			image->convert();
		else
			ofSleepMillis(10);
	}
}