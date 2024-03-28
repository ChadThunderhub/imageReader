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
    void printMostFrequentColor() override;
    int calcualteNumberOfUniqueColors();

    pair<int, int> getLeastFrequentColor();
    void printLeastFrequentColor();

    pair<int, int> getMostFrequentColors();
    void printImageData();

};

#endif // _PPMREADER_HPP_
