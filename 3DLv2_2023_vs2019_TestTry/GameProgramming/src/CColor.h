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

	// ���F [0, 0, 0, 1]
	const static CColor black;
	// ���F [1, 1, 1, 1]
	const static CColor white;
	// �D�F [0.5, 0.5, 0.5, 1]
	const static CColor gray;
	// �ԐF [1, 0, 0, 1]
	const static CColor red;
	// �ΐF [0, 1, 0, 1]
	const static CColor green;
	// �F [0, 0, 1, 1]
	const static CColor blue;
	// �V�A�� [0, 1, 1, 1]
	const static CColor cyan;
	// �}�[���^ [1, 0, 1, 1]
	const static CColor magenta;
	// ���F [1, 1, 0, 1]
	const static CColor yellow;
	// ���� [0, 0, 0, 0]
	const static CColor clear;

private:
	// RGBA�e�F
	float mR, mG, mB, mA;
};