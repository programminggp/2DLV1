#ifndef CCHARACTER_H
#define CCHARACTER_H
//ベクトルクラスのインクルード
#include "CVector.h"
//モデルクラスのインクルード
#include "CModel.h"
//マトリクスクラスのインクルード
#include "CMatrix.h"
/*
キャラクタークラス
ゲームキャラクタの基本的な機能を定義する
*/
class CCharacter {
public:
	CVector mPosition; //位置
	CVector mRotation; //回転
	CVector mScale; //拡大縮小
	CModel *mpModel; //モデルのポインタ
	CMatrix mMatrix; //合成行列
	CMatrix mMatrixTranslate; //平行移動行列
	CMatrix mMatrixRotate; //回転行列
	CMatrix mMatrixScale; //拡大縮小行列
	//更新処理
	void Update();
	//描画処理
	void Render();
};

#endif
