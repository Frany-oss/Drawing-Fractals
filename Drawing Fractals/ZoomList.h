#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include "Zoom.h"


namespace franyNamespace {
	class ZoomList {
		std::vector<Zoom> zooms;

		double m_xCenter = 0;
		double m_yCenter = 0;
		double m_scale   = 1.0;

		int m_width = 0;
		int m_height = 0;
		
	public:
		ZoomList(int width, int height): m_width(width), m_height(height) { }

		void add(const Zoom& zoom) {
			zooms.push_back(zoom);

			m_xCenter += (zoom.x - m_width / 2.0)  * m_scale;
			m_yCenter += (zoom.y - m_height / 2.0) * m_scale;

			m_scale *= zoom.scale;

			std::cout << m_xCenter << ", " << m_yCenter << ", " << m_scale << std::endl;
		}
		std::pair<double, double> doZoom(int x, int y) {

			double xFractal = (x - m_width / 2.0)  * m_scale + m_xCenter;
			double yFractal = (y - m_height / 2.0) * m_scale + m_yCenter;

			return std::pair<double, double>(xFractal, yFractal);
		}
	};
}