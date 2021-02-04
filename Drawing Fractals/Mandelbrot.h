#pragma once
#include <complex> // for using complex numbers

class Mandelbrot {
public:
	static const int MAX_ITERATIONS = 1000;

public:
	Mandelbrot() { }

	static int getIterations(double x, double y) {

		complex<double> z = 0;
		complex<double> c(x, y);

		int iterations = 0;

		while (iterations < MAX_ITERATIONS) {
			z = z * z + c;

			if (norm(z) > 4) {
				break;
			}

			iterations++;
		}

		return iterations;
	}
};
