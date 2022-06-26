#include <stdio.h>
#include "CUi.h"

CUi::CUi()
	: mLeft(0)
{
	mFont.Load("FontWhite.png", 1, 64);
}

void CUi::Left(int left)
{
	mLeft = left;
}

void CUi::Render()
{
	char str[7];
	sprintf(str, "LEFT:%d", mLeft);
	mFont.Draw(20, 20, 10, 20, str);
}
