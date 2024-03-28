#ifndef _IMAGE_READER_HPP_
#define _IMAGE_READER_HPP_

class ImageReader
{
public:
	virtual void printImageInfo() = 0;
	virtual void printMostFrequentColor() = 0;
	virtual int calcualteNumberOfUniqueColors() = 0;
};



#endif
#pragma once