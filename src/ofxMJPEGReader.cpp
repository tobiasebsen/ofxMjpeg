/*
 *  ofxMJPEGReader.cpp
 *  ofxMjpeg
 *
 *  Created by Tobias Ebsen on 3/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#include "ofxMJPEGReader.h"
#include "ofxMJPEGClient.h"
#include "ofxMJPEGImage.h"

//-------------------------------------------------------------------
MJPEGReader::MJPEGReader(MJPEGClient* client, istream* stream) {
	this->client = client;
	this->stream = stream;
	capacity = 40 * 1024;
	buffer = new char[capacity];
}

//-------------------------------------------------------------------
MJPEGReader::~MJPEGReader() {
	free(buffer);
}


//-------------------------------------------------------------------
void MJPEGReader::threadedFunction() {
	
	char line[100];
	
	while(true) {
		int size = 0;
		do {
			stream->getline(line, sizeof(line), '\r');
			stream->ignore(1);
			if(strncmp(line, "Content-Length:", 15) == 0) {
				size = atoi(line+16);
			}
		} while (strlen(line) > 0);
		
		if(size > 0) {
			
			MJPEGImage* image = client->getImage(MJPEG_READYTO_READ);
			while (image == NULL) {
				ofSleepMillis(10);
				image = client->getImage(MJPEG_READYTO_READ);
			}
			image->read(stream, size);
		}
	}
}
