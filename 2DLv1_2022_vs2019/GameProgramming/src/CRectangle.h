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
	~CRectangle();
	void Render();
	void Render(float x, float y, float w, float h);
	void Set(float x, float y, float w, float h);

};