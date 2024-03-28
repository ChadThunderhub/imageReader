#include "PGMReader.hpp"
#include <string>
#include <unordered_set>
#include <map>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

PGMReader::PGMReader(string imagePath)
{
	imageFile.open(imagePath, ios::in);

	if (imageFile.good())
	{
		string fileType;
		string comment;
		int pixelValue;
		try
		{
			getline(imageFile, fileType);
			if (fileType == "P2" || "P1")
			{
				getline(imageFile, comment);
				imageFile >> width >> height;

				for (int i = 0; i < width * height; ++i)
				{
					imageFile >> pixelValue;
					imageData.push_back(pixelValue);
				}
			}
			else
			{
				cout << "Plik nie jest odpowiedniego typu: " << fileType << endl;
				exit(0);
			}
		}
		catch (exception& e)
		{
			cout << e.what() << "\n";
		}
		cout << "Poprawnie wczytano plik " << imagePath << ", typu: " << fileType << endl;
	}
	else
	{
		cout << "Plik PGM (" << imagePath << ") nie zosta³ poprawnie wczytany\n";
		exit(0);
	}
}

void PGMReader::printImageInfo()
{
	cout << "Rozmiar obrazu " << width << "x" << height << endl;
	cout << "Iloœæ unikalnych kolorów: " << calcualteNumberOfUniqueColors() << endl;

	set<int> uniqueColors;
	for (int y = 0; y < height; ++y)
	{
			uniqueColors.insert(imageData[y]);
	}
	cout << "Unikalne kolory:";
	for (int color : uniqueColors)
	{
		cout << " " << color;
	}
	cout << endl;
}

void PGMReader::printMostFrequentColor()
{
	auto mostFrequentColor = getMostFrequentColor();
	cout << "Najczêstszym kolorem jest: #" << hex << mostFrequentColor.first << ", wystêpuje " << dec << mostFrequentColor.second << " razy\n";
}

int PGMReader::calcualteNumberOfUniqueColors()
{
	// *Bardzo* skomplikowane kalkulacje
	unordered_set<int> uniqueColors;
	for (int i = 0; i < height; ++i) 
	{
		for (int j = 0; j < width; ++j) 
		{
			int pixelValue = imageData[i * width + j];
			uniqueColors.insert(pixelValue);
		}
	}
	return uniqueColors.size();
}

	pair<int, int> PGMReader::getMostFrequentColor()
	{
		map<int, int> colorFrequency;

		for (int color : imageData)
		{
			colorFrequency[color]++;
		}

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

	void PGMReader::printImageData()
	{
		for (int i = 0; i < imageData.size(); ++i)
		{
			cout << imageData[i] << " ";
			if ((i + 1) % width == 0) cout << "\n";
		}
	}

	void PGMReader::transponeImage() 
	{
		vector<int> rotatedImageData(width * height);

		for (int i = 0; i < height; ++i) 
		{
			for (int j = 0; j < width; ++j) 
			{
				int originalIndex = i * width + j;
				int rotatedIndex = j * height + i;
				rotatedImageData[rotatedIndex] = imageData[originalIndex];
			}
		}

		swap(width, height);

		imageData = rotatedImageData;
	}

	void PGMReader::rotateImage() 
	{
		vector<int> rotatedImageData(width * height);

		for (int i = 0; i < height; ++i) 
		{
			for (int j = 0; j < width; ++j) 
			{
				int originalIndex = i * width + j;
				int rotatedIndex = (width - j - 1) * height + i;
				rotatedImageData[rotatedIndex] = imageData[originalIndex];
			}
		}

		swap(width, height);

		imageData = rotatedImageData;
	}

	void PGMReader::printLeastFrequentColor() 
	{
		map<int, int> colorFrequency;

		for (int color : imageData) 
		{
			colorFrequency[color]++;
		}

		int minFrequency = numeric_limits<int>::max();
		int leastFrequentColor = 0;
		for (const auto& pair : colorFrequency) 
		{
			if (pair.second < minFrequency) 
			{
				minFrequency = pair.second;
				leastFrequentColor = pair.first;
			}
		}
		cout << "Najrzadziej wystêpuj¹cym kolorem jest: " << leastFrequentColor << ", wystêpuje " << minFrequency;
		if (minFrequency > 1)
		{
			cout << " razy" << endl;
		}
		else
		{
			cout << " raz" << endl;
		}
	}