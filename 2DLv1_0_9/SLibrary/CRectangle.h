#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "CTexture.h"

/*
CRectangleクラス
長方形プログラムの定義
*/
class CRectangle {
public:
	float mX;//中心のX座標
	float mY;//中心のY座標
	float mW;//幅の半分
	float mH;//高さの半分
	float mR;//回転値

	//	int mRow, mCol; //テクスチャ内の行数と列数

	//描画処理の宣言
	void Render();
	/*
	長方形をテクスチャを張って描画する
	texture：テクスチャのポインタ
	left：テクスチャ画像の左X座標
	right：テクスチャ画像の右X座標
	bottom：テクスチャ画像の下Y座標
	top：テクスチャ画像の上Y座標
	*/
	void Render(CTexture *texture, float left, float right, float bottom, float top);
	//コンストラクタの宣言
	CRectangle();
	CRectangle(float x, float y, float w, float h);
	//中心座標(0,0)で幅と高さを指定するコンストラクタ
	CRectangle(float w, float h);
	//Y軸での衝突処理
	float CollisionY(const CRectangle &r) const;
	//X軸での衝突処理
	float CollisionX(const CRectangle &r) const;
	//SetXYWH
	void SetXYWH(int posx, int posy, int width, int height);
	/*
	Set
	posx:X座標 posy:Y座標 width:幅 height:高さ
	*/
	void Set(int posx, int posy, int width, int height);
	//SetPosition
	void SetPosition(float x, float y);
	void SetSize(float sx, float sy);
	void Translate(float x, float y);
	void Scale(float sx, float sy);
	static void Render(float x, float y, float w, float h, CTexture*, float left, float right, float bottom, float top);
	/*
	長方形を描画する
	x:長方形の中心X座標
	y:長方形の中心Y座標
	w:長方形のX軸方向の長さ
	h:長方形のY軸方向の長さ
	*/
	static void Render(float x, float y, float w, float h);

};

#endif
