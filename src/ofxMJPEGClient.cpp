/*
 *  ofxMJPEGClient.cpp
 *  ofxMjpeg
 *
 *  Created by Tobias Ebsen on 3/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxMJPEGClient.h"
#include "Poco/URI.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPMessage.h"
#include "Poco/Net/HTTPResponse.h"

using Poco::URI;
using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPMessage;
using Poco::Net::HTTPResponse;

//--------------------------------------------------------------
MJPEGClient::MJPEGClient() {
	session = NULL;
	images.push_back(new MJPEGImage());
	images.push_back(new MJPEGImage());
	images.push_back(new MJPEGImage());
	images.push_back(new MJPEGImage());
	pixels = NULL;
}

//--------------------------------------------------------------
MJPEGClient::~MJPEGClient() {
	if(session != NULL) {
		delete session;
		session = NULL;
	}
}

//--------------------------------------------------------------
void MJPEGClient::connect(string url) {
	
	URI uri(url);
	string path(uri.getPathAndQuery());
	if (path.empty()) path = "/";
	
	HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
	
	session = new HTTPClientSession(uri.getHost(), uri.getPort());
	session->sendRequest(req);
	
	HTTPResponse res;
	istream& stream = session->receiveResponse(res);
	
	reader = new MJPEGReader(this, &stream);
	reader->startThread();
	
	converter = new MJPEGConverter(this);
	converter->startThread();
}

//--------------------------------------------------------------
void MJPEGClient::grabFrame() {

	MJPEGImage* image = getImage(MJPEG_READYTO_DRAW);
	if (image == NULL) {
		frameNew = false;
	}
	else {
				
		width = image->getWidth();
		height = image->getHeight();
		int n = width * height * 3;
		if(size != n) {
			if(pixels != NULL) delete pixels;
			size = n;
			pixels = new unsigned char[size];
		}

		unsigned char* ipixels = image->getPixels();
		memcpy(pixels, ipixels, size);
		
		image->setStatus(MJPEG_READYTO_READ);

		frameNew = true;
	}
}

//--------------------------------------------------------------
void MJPEGClient::draw(float x, float y) {
	
	if(frameNew) {
		
		if(!texture.bAllocated()) {
			texture.allocate(width, height, GL_RGB);
		}
		else if(texture.getWidth() != width || texture.getHeight()) {
			texture.clear();
			texture.allocate(width, height, GL_RGB);
		}
		texture.loadData(pixels, width, height, GL_RGB);
	}
	texture.draw(x, y);
}

//--------------------------------------------------------------
bool MJPEGClient::isFrameNew() {
	return frameNew;
}

//--------------------------------------------------------------
unsigned char* MJPEGClient::getPixels() {	
	return pixels;
}

//--------------------------------------------------------------
int MJPEGClient::getWidth() {
	return width;
}

//--------------------------------------------------------------
int MJPEGClient::getHeight() {
	return height;
}

//--------------------------------------------------------------
MJPEGImage* MJPEGClient::getImage(int status) {
	
	for (int i=0; i<images.size(); i++) {
		if (images[i]->getStatus() == status) {
			return images[i];
		}
	}
	return NULL;
}
