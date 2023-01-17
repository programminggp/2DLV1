#ifndef CAREAMAGIC_H
#define CAREAMAGIC_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//三角形クラスのインクルード
#include "CTriangle.h"
//
#include "CCollider.h"
/*
弾クラス
三角形を飛ばす
*/
class CAreaMagic : public CCharacter {
public:
	//CAreaMagic();
	CAreaMagic(const CVector& position, const CVector& rotation, const CVector& scale);
	//幅と奥行きの設定
	//Set(幅, 奥行)
	void Set(float w, float d);
	//更新
	void Update();
	//描画
	void Render();
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
private:
	CCollider mCollider;
	int AMagicLife;   //範囲魔法生存時間
	//三角形
	CTriangle mT;
};

#endif
