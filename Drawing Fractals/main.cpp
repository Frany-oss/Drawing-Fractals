#include <iostream>
#include "FractalCreator.h"

using namespace franyNamespace;


int main() {

	int const m_height = 600;
	
	std::cout << "Creating the Fractal..." << std::endl;

	FractalCreator fractalCreator(800, 600);

	fractalCreator.addZoom(Zoom(295, m_height - 202, 0.1));
	fractalCreator.addZoom(Zoom(312, m_height - 304, 0.1));

	fractalCreator.calculateIteration();
	fractalCreator.calculateTotalIterations();
	fractalCreator.drawFractal();

	fractalCreator.writeBitmap("test.bmp");

	std::cout << "Finished." << std::endl;
	return 0;
}