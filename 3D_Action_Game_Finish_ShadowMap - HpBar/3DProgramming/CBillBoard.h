#ifndef CBILLBOARD_H
#define CBILLBOARD_H

#include "CVector3.h"
#include "CVector4.h"
#include "CTexture.h"
#include "CMatrix44.h"
#include "CTask.h"

//ビルボードクラス
class CBillBoard : public CTask {
protected:
	//行列
	CMatrix44 mMatrix;
	//位置座標
	CVector3 mPosition;
	//拡大縮小値
	CVector3 mScale;
	//表示色
	CVector4 mColor;
	//テクスチャ
	CTexture *mpTexture;
	//テクスチャマッピング
	CVector2 mUv[4];
public:
	//コンストラクタ
	CBillBoard(){}
	CBillBoard(const CVector3 &position, const CVector3 &scale);
	//テクスチャの設定
	void SetTexture(CTexture *t);
	//描画処理
	void Render();
};
/*
ヒットエフェクトクラス
*/
class CEffectHit : public CBillBoard {
public:
	//テクスチャの宣言
	static CTexture mTexEffectHit;
	//エフェクトの寿命
	int mLife;
	CEffectHit(){}
	CEffectHit(const CVector3 &position, const CVector3 &scale);

	void Update();
	void Render();
};

class CEffectHit2 : public CBillBoard {
public:
	//テクスチャの宣言
	static CTexture mTexEffectHit;
	//エフェクトの寿命
	int mLife;
	int mRows, mCols;
	CEffectHit2(){}
	CEffectHit2(const CVector3 &position, const CVector3 &scale);
	CEffectHit2(const CVector3 &position, const CVector3 &scale, int rows, int cols);

	void Update();
	void Render();
};

class CEffectHit3 : public CBillBoard {
public:
	//テクスチャの宣言
	static CTexture mTexEffectHit;
	//エフェクトの寿命
	int mLife;
	int mRows, mCols;
	CEffectHit3(){}
	CEffectHit3(const CVector3 &position, const CVector3 &scale);
	CEffectHit3(const CVector3 &position, const CVector3 &scale, int rows, int cols);

	void Update();
	void Render();
};


#endif
