#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//トランスフォームクラスのインクルード
#include "CTransform.h"
/*
コライダクラス
衝突判定データ
*/
class CCollider : public CTransform, public CTask {
public:
	//コライダの種類
	enum ETag {
		ENONE,
		EBODY,//機体
		ESEARCH,//サーチ
	};
	ETag mTag;
	CCharacter *mpParent;//親
	float mRadius;	//半径
	//コンストラクタ
	//CCollider(親, 位置, 回転, 拡縮, 半径)
	CCollider(CCharacter *parent, CVector position, CVector rotation, CVector scale, float radius);
	~CCollider();
	//描画
	void Render();
	//衝突判定
	//Collision(コライダ1, コライダ2)
	//retrun:true（衝突している）false(衝突していない)
	static bool Collision(CCollider *m, CCollider *y);
};

#endif
