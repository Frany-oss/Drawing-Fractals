#pragma once
#include <string>
#include <math.h>
#include <cstdint>
#include <memory>
#include "ZoomList.h"
#include "Bitmap.h"
#include "Mandelbrot.h"

class FractalCreator {
	int m_width;
	int m_height;
	unique_ptr<int[]> m_histogram;
	unique_ptr<int[]> m_fractal;
	Bitmap m_bitmap;
	ZoomList m_zoomList;
	int m_total = 0;

public:
	FractalCreator(int width, int height) : m_width(width), m_height(height), m_histogram(new int[Mandelbrot::MAX_ITERATIONS + 1]{}),
	m_fractal(new int[m_width * m_height]{}), m_bitmap(m_width, m_height), m_zoomList(m_width, m_height) {

		m_zoomList.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width));
	}

	void run(std::string name) {
		addZoom(Zoom(295, m_height - 202, 0.1));
		addZoom(Zoom(312, m_height - 304, 0.1));
		calculateIteration();
		calculateTotalIterations();
		drawFractal();
		writeBitmap(name);
	}

	void calculateIteration() {

		for (int y = 0; y < m_height; ++y) {
			for (int x = 0; x < m_width; ++x) {
				pair<double, double> coords = m_zoomList.doZoom(x, y);

				int iterations = Mandelbrot::getIterations(coords.first, coords.second);
				m_fractal[y * m_width + x] = iterations;

				if (iterations != Mandelbrot::MAX_ITERATIONS)
					m_histogram[iterations]++;
			}
		}
	}

	void calculateTotalIterations() {
		for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i) {
			m_total += m_histogram[i];
		}
	}

	void drawFractal() {

		for (int y = 0; y < m_height; y++) {
			for (int x = 0; x < m_width; x++) {

				uint8_t red = 0;
				uint8_t green = 0;
				uint8_t blue = 0;

				int iterations = m_fractal[y * m_width + x];

				if (iterations != Mandelbrot::MAX_ITERATIONS) {
					double hue = 0.0;
					for (int i = 0; i <= iterations; ++i) {
						hue += ((double)m_histogram[i]) / m_total;
					}
					green = pow(255, hue);
				}

				m_bitmap.setPixel(x, y, red, green, blue);
			}
		}
	}

	void addZoom(const Zoom& zoom) {
		m_zoomList.add(zoom);
	}

	void writeBitmap(std::string name) {
		m_bitmap.writeBitmap(name);
	}

};