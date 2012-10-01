/*
 *  ofxMJPEGImage.cpp
 *  ofxMjpeg
 *
 *  Created by Tobias Ebsen on 3/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxMJPEGImage.h"

//----------------------------------------------------------------
MJPEGImage::MJPEGImage() {
	memory = FreeImage_OpenMemory();
	pixels = NULL;
	status = MJPEG_READYTO_READ;
}

//----------------------------------------------------------------
MJPEGImage::~MJPEGImage() {
	FreeImage_CloseMemory(memory);
	if(pixels != NULL) {
		delete pixels;
		pixels = NULL;
	}
}

//----------------------------------------------------------------
void MJPEGImage::read(istream* stream, int size) {
		
	unsigned char buffer[256];
	int s = size;
	
	FreeImage_SeekMemory(memory, 0, SEEK_SET);
	
	while (s > 0) {
		int n = s > sizeof(buffer) ? sizeof(buffer) : s;
		stream->read((char*)buffer, n);
		FreeImage_WriteMemory(buffer, n, 1, memory);
		s -= n;
	}
		
	int t = FreeImage_TellMemory(memory);
	
	status = MJPEG_READYTO_CONVERT;
}

//----------------------------------------------------------------
void MJPEGImage::read(char* data, int size) {
	
	FreeImage_SeekMemory(memory, 0, SEEK_SET);
	FreeImage_WriteMemory(data, size, 1, memory);
}

//----------------------------------------------------------------
void MJPEGImage::convert() {
		
	FreeImage_SeekMemory(memory, 0, SEEK_SET);
	FIBITMAP* dib = FreeImage_LoadFromMemory(FIF_JPEG, memory, 0);
	
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
		
	unsigned n = width * height * 3;
	if (n != size) {
		if (pixels != NULL) delete pixels;
		size = n;
		pixels = new unsigned char[size];
	}
	
	unsigned char* bits = (unsigned char*)FreeImage_GetBits(dib);
	FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(dib);
	unsigned pitch = FreeImage_GetPitch(dib);
	unsigned bpp = FreeImage_GetBPP(dib);
	
	int p = 0;
	
	if(image_type == FIT_RGBF) {
		
		/*for(int y=0; y<height; y++) {
			FIRGBF* row = (FIRGBF*)bits;
			for(int x=0; x<width; x++) {
				pixels[p++] = row[x].red;
				pixels[p++] = row[x].green;
				pixels[p++] = row[x].blue;
			}
			bits += pitch;
		}*/
	}
	if(image_type == FIT_BITMAP && bpp == 24) {

		bits += pitch * (height - 1);
		for(int y=0; y<height; y++) {
			unsigned char* row = (unsigned char*)bits;
			for(int x=0; x<width; x++) {
				pixels[p++] = row[FI_RGBA_RED];
				pixels[p++] = row[FI_RGBA_GREEN];
				pixels[p++] = row[FI_RGBA_BLUE];
				row += 3;
			}
			bits -= pitch;
		}
	}

	FreeImage_Unload(dib);
	
	status = MJPEG_READYTO_DRAW;
}

//----------------------------------------------------------------
int MJPEGImage::getWidth() {
	return width;
}

//----------------------------------------------------------------
int MJPEGImage::getHeight() {
	return height;
}

//----------------------------------------------------------------
unsigned char* MJPEGImage::getPixels() {
	return pixels;
}

//----------------------------------------------------------------
int MJPEGImage::getStatus() {
	return status;
}

//----------------------------------------------------------------
void MJPEGImage::setStatus(int status) {
	this->status = status;
}