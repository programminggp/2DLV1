#ifndef CRECT_H
#define CRECT_H

class CRect {
public:
	float mX;
	float mY;
	float mW;
	float mH;
	float mR;

	CRect();
	CRect(float x, float y, float w, float h, float r);

	void Set(float x, float y, float w, float h, float r);

	void Render();

};


#endif
