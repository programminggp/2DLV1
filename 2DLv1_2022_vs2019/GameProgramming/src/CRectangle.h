#pragma once
class CRectangle
{
private:
	float mX; //X���W
	float mY; //Y���W
	float mW; //��
	float mH; //����
public:
	CRectangle();
	void Render();
	~CRectangle();
	CRectangle(float x, float y, float w, float h);
};