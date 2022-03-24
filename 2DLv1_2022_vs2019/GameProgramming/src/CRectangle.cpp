#include "CRectangle.h"
#include "glut.h"

CRectangle::CRectangle()
{
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(400.0f, 0.0f);
	glVertex2f(400.0f, 300.0f);
	glVertex2f(0.0f, 300.0f);
	glEnd();
}

void CRectangle::Render()
{
	glBegin(GL_QUADS);
	glVertex2f(400.0f, 300.0f);
	glVertex2f(600.0f, 300.0f);
	glVertex2f(600.0f, 450.0f);
	glVertex2f(400.0f, 450.0f);
	glEnd();
}

CRectangle::~CRectangle()
{
	//glBegin(GL_QUADS);
	//glVertex2f(400.0f, 300.0f);
	//glVertex2f(800.0f, 300.0f);
	//glVertex2f(800.0f, 600.0f);
	//glVertex2f(400.0f, 600.0f);
	//glEnd();
}

CRectangle::CRectangle(float left, float right, float bottom, float top)
{
	glBegin(GL_QUADS);
	glVertex2f(left, bottom);
	glVertex2f(right, bottom);
	glVertex2f(right, top);
	glVertex2f(left, top);
	glEnd();
}
