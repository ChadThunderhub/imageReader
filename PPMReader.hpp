#pragma once
#ifndef _PPMREADER_HPP_
#define _PPMREADER_HPP_

#include "ImageReader.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class PPMReader : public ImageReader {
private:

    ifstream imageFile;
    int width;
    int height;
    int maxColor;
    vector<std::vector<int>> imageData;

public:
    PPMReader(std::string imagePath);

    void printImageInfo() override;

    pair<int, int> getMostFrequentColors();
    void printMostFrequentColor() override;

    int calcualteNumberOfUniqueColors() override;

    pair<int, int> getLeastFrequentColor();
    void printLeastFrequentColor();

    void printImageData();
};

#endif // _PPMREADER_HPP_
