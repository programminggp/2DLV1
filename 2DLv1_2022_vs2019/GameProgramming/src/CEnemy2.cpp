#include "CEnemy2.h"

#define TEXCOORD 168, 188, 190, 160	//テクスチャマッピング

CEnemy2::CEnemy2(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EENEMY;
}

void CEnemy2::Update()
{
}
