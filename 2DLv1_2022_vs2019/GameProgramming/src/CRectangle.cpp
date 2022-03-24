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

CRectangle::CRectangle(float x, float y, float w, float h)
{
	glBegin(GL_QUADS);
	glVertex2f(x - w, y - h);
	glVertex2f(x + w, y - h);
	glVertex2f(x + w, y + h);
	glVertex2f(x - w, y + h);
	glEnd();
}
