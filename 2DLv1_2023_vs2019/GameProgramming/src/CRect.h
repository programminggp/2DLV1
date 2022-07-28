#pragma once
#include "glut.h"

/*
* 四角形クラス
*/
class CRect
{
public:
	//Draw(X座標,Y座標,幅,高さ)
	//四角形を描画する
	static void CRect::Draw(float x, float y, float w, float h);
};
