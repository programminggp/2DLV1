#pragma once
#include "CCharacter.h"
/*
* CBlock
* ブロッククラス
* マップのブロックに使用する
*/
class CBlock : public CCharacter
{
public:
	//CBlock(X座標,Y座標,幅,高さ,テクスチャのポインタ)
	CBlock(float x, float y, float w, float h, CTexture* pt);
	//Updateでは何もしない
	void Update() {}
};