#ifndef CVERTEX_H
#define CVERTEX_H

#include "CVector3.h"

/*
頂点バッファデータクラス
頂点毎にデータをまとめます
*/
class CVertex {
public:
	//位置
	CVector3 mPosition;
	//法線
	CVector3 mNormal;
	//テクスチャマッピング
	CVector2 mTextureCoords;
	//スキンウェイト
	float mBoneWeight[4];
	//スキンインデックス
	float mBoneIndex[4];

	CVertex() {
		for (int i = 0; i < 4; i++) {
			mBoneIndex[i] = 0;
			mBoneWeight[i] = 0.0f;
		}
		mBoneWeight[0] = 1.0f;
	}
};

#endif
