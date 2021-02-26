#ifndef CIMAGE_H
#define CIMAGE_H
#include "CBillBoard.h"
/*
CImage
板ポリゴンにテクスチャを貼って描画
*/
class CImage : public CBillBoard {
public:
	//CImage(テクスチャ,位置,回転,拡縮)
	CImage(std::shared_ptr<CTexture> texture, const CVector &pos, const CVector &rot, const CVector &sca);
	//SetUv(左座標,右座標,上座標,下座標)
	//使用するテクスチャの座標を指定する
	//原点左上
	void SetUv(float left, float right, float bottom, float top);
	//Update
	//行列の更新
	void Update();
};

#endif
