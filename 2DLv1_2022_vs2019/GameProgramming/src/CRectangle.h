#pragma once
class CRectangle
{
//private:
//	float mX; //X座標
//	float mY; //Y座標
//	float mW; //幅
//	float mH; //高さ
public:
	CRectangle();
	~CRectangle();
	void Render();
	void Render(float x, float y, float w, float h);


};