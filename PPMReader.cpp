#include "PPMReader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std;

PPMReader::PPMReader(string imagePath)
{
    imageFile.open(imagePath);

    if (imageFile.good())
    {
        string fileType;
        string comment;
        int pixelValue;
        try 
        {
            getline(imageFile, fileType);
            if (fileType == "P3")
            {
                while (getline(imageFile, comment))
                {
                    if (comment.empty() || comment[0] != '#')
                    {
                        istringstream iss(comment);
                        iss >> width >> height;
                        break;
                    }
                }

                // Odczytanie maksymalnej wartoœci koloru DO PRZEJRZENIA
               // imageFile >> maxColor;

                imageData.resize(height, std::vector<int>(width * 3));
                for (int y = 0; y < height; ++y)
                {
                    for (int x = 0; x < width * 3; ++x)
                    {
                        imageFile >> pixelValue;
                        imageData[y][x] = pixelValue;
                    }
                }
            }
            else
            {
                cout << "Plik nie jest odpowiedniego typu: " << fileType << endl;
                exit(0);
            }
            cout << "Poprawnie wczytano plik " << imagePath << ", typu: " << fileType << endl;
        }
        catch (std::exception& e)
        {
            cout << e.what() << "\n";
        }
    }
    else
    {
        cout << "Plik PPM (" << imagePath << ") nie zosta³ poprawnie wczytany\n";
        exit(0);
    }
}

void PPMReader::printImageInfo() 
{
    cout << "Rozmiar obrazu: " << width << "x" << height << endl;
    cout << "Iloœæ unikalnych kolorów: " << calcualteNumberOfUniqueColors() << endl;
    //cout << "Maksymalna wartosc koloru: " << maxColor << "\n"; //DO PRZEJRZENIA
    //printMostFrequentColor();

    set<int> uniqueColors;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width * 3; ++x)
        {
            uniqueColors.insert(imageData[y][x]);
        }
    }
    cout << "Unikalne kolory:";
    for (int color : uniqueColors)
    {
        cout << " " << color;
    }
    cout << "\n";
}

void PPMReader::printMostFrequentColor()
{
    auto mostFrequentColor = getMostFrequentColors();
    cout << "Najczêstszym kolorem jest: #" << hex << mostFrequentColor.first << ", wystêpuje " << dec << mostFrequentColor.second << " razy\n";
}

int PPMReader::calcualteNumberOfUniqueColors()
{
    set<int> uniqueColors;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width * 3; ++x)
        {
            uniqueColors.insert(imageData[y][x]);
        }
    }
    return uniqueColors.size();
}

pair<int, int> PPMReader::getMostFrequentColors()
{
    map<int, int> colorFrequency;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width * 3; x += 3)
        {
            int color = (imageData[y][x] << 16) | (imageData[y][x + 1] << 8) | imageData[y][x + 2];
            colorFrequency[color]++;
        }
    }

    // Szukamy najczêœciej wystêpuj¹cego koloru
    int maxFrequency = 0;
    int mostFrequentColor = 0;
    for (const auto& pair : colorFrequency)
    {
        if (pair.second > maxFrequency)
        {
            maxFrequency = pair.second;
            mostFrequentColor = pair.first;
        }
    }

    return make_pair(mostFrequentColor, maxFrequency);
}

void PPMReader::printImageData()
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width * 3; ++x)
        {
            cout << imageData[y][x] << " ";
            if ((x + 1) % (width * 3) == 0) cout << "\n";
        }
    }
}

pair<int, int> PPMReader::getLeastFrequentColor()
{
    unordered_map<int, int> colorFrequency;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width * 3; x += 3)
        {
            int color = (imageData[y][x] << 16) | (imageData[y][x + 1] << 8) | imageData[y][x + 2];
            colorFrequency[color]++;
        }
    }

    auto leastFrequentColor = min_element(colorFrequency.begin(), colorFrequency.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
        });

    return *leastFrequentColor;
}

void PPMReader::printLeastFrequentColor()
{
    auto leastFrequentColor = getLeastFrequentColor();
    cout << "Najrzadziej wystêpuj¹cym kolorem jest: #" << hex << leastFrequentColor.first << ", wystêpuje " << dec << leastFrequentColor.second << " razy\n";
}
