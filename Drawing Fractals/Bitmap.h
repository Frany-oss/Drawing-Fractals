#pragma once
#include <iostream>
#include <cstdint>
#include <fstream> // to write the Bitmap file
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

using namespace std;

class Bitmap {
	signed int m_width = 0;
	signed int m_height = 0;
	unique_ptr<uint8_t[]> m_pPixels{nullptr};
public:
	Bitmap(signed int width, signed int height) : m_width(width), m_height(height), m_pPixels(new uint8_t[width * height * 3]{}) { }

	bool writeBitmap(std::string fileName) {

		BitmapFileHeader fileHeader; // Information of the file
		BitmapInfoHeader infoHeader; // Information of the bitmap

		// The size of the file
		fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + (m_width * m_height * 3);
		fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader); // The distances from the beginning of the file to the actuall data

		infoHeader.width = m_width;
		infoHeader.height = m_height;

		ofstream file;
		file.open(fileName, ios::out | ios::binary);
		if (!file) {
			return false;
		}

		file.write((char*)&fileHeader, sizeof(fileHeader));
		file.write((char*)&infoHeader, sizeof(infoHeader));
		file.write((char*)m_pPixels.get(), (m_height * m_width * 3.0));

		file.close();


		return true;
	}
	void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) { // uint8_t is unsigned bytes (0 to 256)
		uint8_t* pPixel = m_pPixels.get();

		pPixel += (y * 3) * m_width + (x * 3);
		pPixel[0] = blue;
		pPixel[1] = green;
		pPixel[2] = red;
	}
};
