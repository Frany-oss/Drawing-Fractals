#include <iostream>
#include "Bitmap.h"

using namespace std;
using namespace caveofprogramming;

int const WIDTH = 800;
int const HEIGHT = 600;

int main() {
	
	Bitmap bitmap(WIDTH, HEIGHT);

	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			bitmap.setPixel(x, y, 255, 0, 0);
		}
	}

	bitmap.writeBitmap("test.bmp");

	cout << "finished..." << endl;

	return 0;
}