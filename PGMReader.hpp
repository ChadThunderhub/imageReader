#pragma once
#ifndef _PGMReader_HPP_
#define _PGMReader_HPP_

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "ImageReader.hpp"

using namespace std;

class PGMReader : public ImageReader
{
private:
	int width;
	int height;

	fstream imageFile;
	vector<int> imageData;

public:
	PGMReader(string imagePath);

	void printImageInfo() override;
	void printMostFrequentColor() override;
	int calcualteNumberOfUniqueColors() override;

	void transponeImage();
	void rotateImage();
	void printLeastFrequentColor();

	pair<int, int> getMostFrequentColor();
	void printImageData();

};

#endif //_PGMReader_HPP_
