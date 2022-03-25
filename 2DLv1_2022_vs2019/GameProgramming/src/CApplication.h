#pragma once
#include "CRectangle.h"
class CApplication
{
private:
	CRectangle mRectangle;
public:
	//最初に一度だけ実行するプログラム
	void Start();
	//繰り返し実行するプログラム
	void Update();
};