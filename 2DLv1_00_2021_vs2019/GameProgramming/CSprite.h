#ifndef CSPRITE_H
#define CSPRITE_H

#include "CRect.h"
#include "CTexture.h"

class CSprite : public CRect {
public:
	CTexture *mpTexture;

	CSprite();
	CSprite(float x, float y, float w, float h, float r, CTexture *ptexture);

	//x:X座標 y:Y座標 w:幅 h:高さ r:回転 ptexture:テクスチャへのポインタ
	void Set(float x, float y, float w, float h, float r, CTexture *ptexture);
	void Set(CTexture *ptexture);

	void Render();
	void Render(int uleft, int uright, int ubottom, int utop);

};


#endif
