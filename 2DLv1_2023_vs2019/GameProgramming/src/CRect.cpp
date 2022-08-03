#include "CRect.h"

void CRect::Draw(float x, float y, float w, float h)
{
	glBegin(GL_QUADS);
	glVertex2f(x - w, y - h);
	glVertex2f(x + w, y - h);
	glVertex2f(x + w, y + h);
	glVertex2f(x - w, y + h);
	glEnd();
}

void CRect::Draw(int x, int y, int w, int h)
{
	glBegin(GL_QUADS);
	glVertex2i(x - w, y - h);
	glVertex2i(x + w, y - h);
	glVertex2i(x + w, y + h);
	glVertex2i(x - w, y + h);
	glEnd();
}
