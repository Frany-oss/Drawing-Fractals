#pragma once
#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

namespace caveoFprogramming {
	class Bitmap {
	private:
		int m_width = 0;
		int m_height = 0;
		unique_ptr<uint8_t[]> m_pPixel = nullptr;
	public:
		Bitmap(int width, int height) : m_width(width), m_height(height), m_pPixel(new uint8_t[width*height*3]) {}

		virtual ~Bitmap();

		bool write(std::string fileName) {
			return false;
		}
		void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) { // uint8_t is unsigned bytes (0 to 256)

		}
	};
}
