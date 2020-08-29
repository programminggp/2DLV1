#ifndef CVERTEX_H
#define CVERTEX_H
#include "CVector.h"

class CVertex
{
public:
	//座標
	CVector mPosition;
	//法線
	CVector mNormal;
	//テクスチャマップ
	float mTexCoord[2];
	//スキンウェイト
	float mBoneWeight[4];
	//スキンインデックス
	float mBoneIndex[4];

	//デフォルトコンストラクタ
	CVertex();

};

#endif
