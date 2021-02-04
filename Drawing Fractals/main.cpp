#include <iostream>
#include <cstdint>
#include "Bitmap.h"
#include "Mandelbrot.h"

using namespace std;
using namespace franyNamespace;

signed int const WIDTH = 600;
signed int const HEIGHT = 800;


int main() {
	
	Bitmap bitmap(WIDTH, HEIGHT);
	double min = 999999;
	double max = -999999;

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			double xFractal = (x - WIDTH / 2.0 - 200) * 2.0 / HEIGHT;
			double yFractal = (y - HEIGHT / 2.0) * 2.0 / HEIGHT;

			int iterations = Mandelbrot::getIterations(xFractal, yFractal);

			uint8_t color = (uint8_t)(256 * (double)iterations / Mandelbrot::MAX_ITERATIONS);

			color = color * color * color;

			bitmap.setPixel(x, y, 0, color, color);
			if (color < min) min = color;
			if (color > max) max = color;
		}
	}

	cout << min << ", " << max << endl;

	bitmap.writeBitmap("test.bmp");

	cout << "Finished." << endl;
	return 0;
}