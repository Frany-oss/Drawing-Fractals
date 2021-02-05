#include <iostream>
#include "FractalCreator.h"

int main() {

	std::cout << "Creating the Fractal..." << std::endl << std::endl;

	FractalCreator fractalCreator(800, 600);

	fractalCreator.addColorRange(0.0, RGB(0, 0, 255));
	fractalCreator.addColorRange(0.05, RGB(255, 99, 71));
	fractalCreator.addColorRange(0.08, RGB(255, 215, 0));
	fractalCreator.addColorRange(1.0, RGB(255, 255, 255));

	fractalCreator.run("Fractal.bmp");

	std::cout << "Finished!!" << std::endl;
	return 0;
}