#include "CTriangle.h"
#include "glut.h"

CTriangle::CTriangle()
{
	glBegin(GL_TRIANGLES);
	glVertex2f(400.0f, 0.0f);
	glVertex2f(800.0f, 0.0f);
	glVertex2f(800.0f, 300.0f);
	glEnd();
}