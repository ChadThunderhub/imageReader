#include <iostream>
#include <utility>

#include "PGMReader.hpp"
#include "PPMReader.hpp"

using namespace std; 

int main()
{
	system("chcp 1250");
	system("cls");

	string pgmFileName = "pgmFile.pgm";
	string ppmFileName = "ppmFile.ppm";

	PGMReader PGM(pgmFileName);
	
	PGM.printImageInfo();
	PGM.printMostFrequentColor();
	PGM.printLeastFrequentColor();
	cout << endl;

	cout << "Wczytany obraz: " << endl;
	PGM.printImageData();
	cout << endl;

	cout << "Obraz " << pgmFileName << " po transponowaniu: " << endl;
	PGM.transponeImage();
	PGM.printImageData();
	PGM.transponeImage();
	cout << endl;

	cout << "Obraz " << pgmFileName << " obrócony o 90 stopni w lewo: " << endl;
	PGM.rotateImage();
	PGM.printImageData();
	cout << endl;

	PPMReader PPM(ppmFileName);

	PPM.printImageInfo();
	PPM.printMostFrequentColor();
	PPM.printLeastFrequentColor();
	cout << endl;
	 
	cout << "Wczytany obraz: " << endl;
	PPM.printImageData();
	cout << endl;

	return 0;
}