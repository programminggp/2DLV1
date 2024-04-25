#include "CColor.h"

const CColor CColor::black(0.0f, 0.0f, 0.0f, 1.0f);
const CColor CColor::white(1.0f, 1.0f, 1.0f, 1.0f);
const CColor CColor::gray(0.5f, 0.5f, 0.5f, 1.0f);
const CColor CColor::red(1.0f, 0.0f, 0.0f, 1.0f);
const CColor CColor::green(0.0f, 1.0f, 0.0f, 1.0f);
const CColor CColor::blue(0.0f, 0.0f, 1.0f, 1.0f);
const CColor CColor::cyan(0.0f, 1.0f, 1.0f, 1.0f);
const CColor CColor::magenta(1.0f, 0.0f, 1.0f, 1.0f);
const CColor CColor::yellow(1.0f, 1.0f, 0.0f, 1.0f);
const CColor CColor::clear(0.0f, 0.0f, 0.0f, 0.0f);

CColor::CColor()
	: mR(1.0f), mG(1.0f), mB(1.0f), mA(1.0f)
{
}

CColor::CColor(float r, float g, float b)
	: mR(r), mG(g), mB(b), mA(1.0f)
{
}

CColor::CColor(float r, float g, float b, float a)
	: mR(r), mG(g), mB(b), mA(a)
{
}

CColor::~CColor()
{
}

void CColor::Set(float r, float g, float b)
{
	mR = r, mG = g, mB = b;
}

void CColor::Set(float r, float g, float b, float a)
{
	mR = r, mG = g, mB = b, mA = a;
}

float CColor::R() const
{
	return mR;
}

void CColor::R(float r)
{
	mR = r;
}

float CColor::G() const
{
	return mG;
}

void CColor::G(float g)
{
	mG = g;
}

float CColor::B() const
{
	return mB;
}

void CColor::B(float b)
{
	mB = b;
}

float CColor::A() const
{
	return mA;
}

void CColor::A(float a)
{
	mA = a;
}
