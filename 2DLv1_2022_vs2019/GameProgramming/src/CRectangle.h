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
	virtual void Set(float x, float y, float w, float h);
	float X();
	float Y();
	float W();
	float H();
	void Y(float y);
	void X(float x);
};