#include "CRect.h"
#include "glut.h"

CRect::CRect()
: mX(0.0f), mY(0.0f), mW(0.0f), mH(0.0f), mR(0.0f)
{

}

CRect::CRect(float x, float y, float w, float h, float r)
: mX(x), mY(y), mW(w), mH(h), mR(r)
{

}

void CRect::Set(float x, float y, float w, float h, float r) {
	mX = x;
	mY = y;
	mW = w;
	mH = h;
	mR = r;
}

void CRect::Render() {
	glPushMatrix();
	glTranslatef(mX, mY, 0.0f);
	glRotatef(mR, 0.0f, 0.0f, 1.0f);
	glScalef(mW, mH, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-1.0f, -1.0f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(1.0f,  1.0f);
	glVertex2f(-1.0f, 1.0f);
	glEnd();
	glPopMatrix();
}
