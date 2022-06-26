#pragma once
#include "CFont.h"

class CUi
{
public:
	CUi();
	void Left(int left);
	void Render();
private:
	int mLeft;
	CFont mFont;
};
