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
	~CRectangle();
	void Render();
	void Render(float x, float y, float w, float h);
	void Set(float x, float y, float w, float h);

};