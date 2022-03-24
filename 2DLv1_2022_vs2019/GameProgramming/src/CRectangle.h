#pragma once
class CRectangle
{
private:
	float mX; //XÀ•W
	float mY; //YÀ•W
	float mW; //•
	float mH; //‚‚³
public:
	CRectangle();
	void Render();
	~CRectangle();
	CRectangle(float x, float y, float w, float h);
};