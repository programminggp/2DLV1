#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "CTexture.h"

/*
CRectangleクラス
長方形プログラムの定義
*/
class CRectangle {
protected:
	CTexture mTexture;
	CTexture* mpTexture;
public:
	float mX;//中心のX座標
	float mY;//中心のY座標
	float mW;//幅の半分
	float mH;//高さの半分
	float mR;//回転値

	//	int mRow, mCol; //テクスチャ内の行数と列数

	//描画処理の宣言
	void Render();
	void Render(int index);
	void Render(CTexture& texture);
	void Render(CTexture& texture, int index);
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
	//LoadTexture
	void LoadTexture(char* filename);
	void LoadTexture(char* filename, int row, int col);
	//SetTexture
	void SetTexture(CTexture *texture);
	//SetPosition
	void SetPosition(float x, float y);
	void SetSize(float sx, float sy);
	void Translate(float x, float y);
	void Scale(float sx, float sy);

};

#endif
