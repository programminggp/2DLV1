#pragma once

class CColor
{
public:
	CColor();
	CColor(float r, float g, float b);
	CColor(float r, float g, float b, float a);
	~CColor();

	void Set(float r, float g, float b);
	void Set(float r, float g, float b, float a);

	float R() const;
	void R(float r);
	float G() const;
	void G(float g);
	float B() const;
	void B(float b);
	float A() const;
	void A(float a);

	// 黒色 [0, 0, 0, 1]
	const static CColor black;
	// 白色 [1, 1, 1, 1]
	const static CColor white;
	// 灰色 [0.5, 0.5, 0.5, 1]
	const static CColor gray;
	// 赤色 [1, 0, 0, 1]
	const static CColor red;
	// 緑色 [0, 1, 0, 1]
	const static CColor green;
	// 青色 [0, 0, 1, 1]
	const static CColor blue;
	// シアン [0, 1, 1, 1]
	const static CColor cyan;
	// マゼンタ [1, 0, 1, 1]
	const static CColor magenta;
	// 黄色 [1, 1, 0, 1]
	const static CColor yellow;
	// 透明 [0, 0, 0, 0]
	const static CColor clear;

private:
	// RGBA各色
	float mR, mG, mB, mA;
};