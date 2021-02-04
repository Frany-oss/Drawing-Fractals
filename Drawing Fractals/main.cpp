#include <iostream>
#include "FractalCreator.h"

int main() {

	std::cout << "Creating the Fractal..." << std::endl << std::endl;

	FractalCreator fractalCreator(800, 600);
	fractalCreator.run("Fractal.bmp");

	std::cout << "Finished!!" << std::endl;
	return 0;
}