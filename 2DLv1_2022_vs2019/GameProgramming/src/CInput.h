#pragma once
#include <Windows.h>

class CInput
{
public:
	CInput();
	//bool Key(文字)
	//戻り値
	//true:文字のキーが押されている
	//false:文字のキーが押されていない
	bool Key(char key);
};