#ifndef CRECTANGLE_H
#define CRECTANGLE_H
#include "CTexture.h"
#include "glut.h"
#include <vector>

class CRectangle {
public:
	static void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2);
	static void DrawRectangle(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
	static void Render(int x, int y, int w, int h);
	static void RenderImage(CTexture &t, int x, int y, int w, int h, int texsize_x, int texsize_y);
};

#endif