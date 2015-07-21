#pragma once

#include "Courbe.h"

class Bezier :
	public Courbe
{
	public:
		Bezier(std::string vertexShader, std::string fragmentShader);
		~Bezier();


		void setControlPts(ListPts l){ list = l; }
		Point2 getPtsInCourbeAt(int i){ return m_pointInCourbe[i]; }
		void computePointInCourbe();
		void load();
		void drawCourbe(Mat4x4 projection, Mat4x4 modelView);
		void drawCourbeSurface(Mat4x4 projection, Mat4x4 modelView, bool points = true, bool poly = true);

		Point2 CastelJau(double step);			//CastelJau algorithm to compute barycenters
};

