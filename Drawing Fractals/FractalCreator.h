#pragma once
#include <string>
#include <math.h>
#include <cstdint>
#include <memory>
#include <vector>
#include <cassert>
#include "ZoomList.h"
#include "Bitmap.h"
#include "Mandelbrot.h"
#include "RGB.h"

class FractalCreator {
	int m_width;
	int m_height;

	unique_ptr<int[]> m_histogram;
	unique_ptr<int[]> m_fractal;
	
	Bitmap m_bitmap;
	ZoomList m_zoomList;
	int m_total = 0;

	std::vector<int> m_ranges;
	std::vector<RGB> m_colors;
	std::vector<int> m_rangeTotals;

	bool m_bGotFirstRange = false;

public:
	FractalCreator(int width, int height) : m_width(width), m_height(height), m_histogram(new int[Mandelbrot::MAX_ITERATIONS + 1]{}),
	m_fractal(new int[m_width * m_height]{}), m_bitmap(m_width, m_height), m_zoomList(m_width, m_height) {

		m_zoomList.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width));
	}

	void run(std::string name) {
		addZoom(Zoom(295, 202, 0.1));
		addZoom(Zoom(312, 304, 0.1));

		calculateIteration();
		calculateTotalIterations();
		calculateColorRangeTotal();
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

	void calculateColorRangeTotal() {

		int rangeIndex = 0;

		for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i) {
			int pixels = m_histogram[i];
			if (i >= m_ranges[rangeIndex + 1]) {
				rangeIndex++;
			}
			m_rangeTotals[rangeIndex] += pixels;
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

				int iterations = m_fractal[y * m_width + x];

				int range = getColorRange(iterations);
				int rangeTotal = m_rangeTotals[range];
				int rangeStart = m_ranges[range];

				RGB& startColor = m_colors[range];
				RGB& endColor = m_colors[range + 1];
				RGB colorDiff = endColor - startColor;

				uint8_t red = 0;
				uint8_t green = 0;
				uint8_t blue = 0;

				if (iterations != Mandelbrot::MAX_ITERATIONS) {
					int totalPixels = 0;
					for (int i = rangeStart; i <= iterations; ++i) {
						totalPixels += m_histogram[i];
					}
					red   = startColor.r + colorDiff.r * (double)totalPixels / rangeTotal;
					green = startColor.g + colorDiff.g * (double)totalPixels / rangeTotal;
					blue  = startColor.b + colorDiff.b * (double)totalPixels / rangeTotal;
				}

				m_bitmap.setPixel(x, y, red, green, blue);
			}
		}
	}

	void addColorRange(double rangeEnd, const RGB& rgb) {
		m_ranges.push_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
		m_colors.push_back(rgb);

		if (m_bGotFirstRange) {
			m_rangeTotals.push_back(0);
		}
		m_bGotFirstRange = true;

	}

	int getColorRange(int iterations) const {
		int range = 0;

		for (int i = 1; i < m_ranges.size(); ++i) {
			range = i;
			if (m_ranges[i] > iterations) {
				break;
			}
		}
		range--;

		assert(range > -1);
		assert(range < m_ranges.size());

		return range;
	}

	void addZoom(const Zoom& zoom) {
		m_zoomList.add(zoom);
	}

	void writeBitmap(std::string name) {
		m_bitmap.writeBitmap(name);
	}

};