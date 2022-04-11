#ifndef CCHARACTER_H
#define CCHARACTER_H

//変換行列クラスのインクルード
#include"CTransform.h"
//モデルクラスのインクルード
#include"CModel.h"
//タスククラスのインクルード
#include"CTask.h"
//コライダクラスの宣言
class CCollider;
/*
キャラクタークラス
ゲームキャラクタの基本的な機能を定義する
*/

class CCharacter : public CTransform,public CTask{
protected:
	CModel* mpModel; //モデルのポインタ
public:
	//モデルの設定
	//Model(モデルクラスのポインタ)
	void Model(CModel* m);
	//描画処理
	void Render();
	//コンストラクタ
	CCharacter();
	//デストラクタ
	~CCharacter();
	//衝突処理
	virtual void Collision(CCollider *m,CCollider *o){}
};
#endif 


