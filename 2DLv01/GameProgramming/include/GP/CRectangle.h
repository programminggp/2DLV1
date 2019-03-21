#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "CTask.h"
#include "CTexture.h"

/*
CRectangleクラス
長方形プログラムの定義
*/
class CRectangle : public CTask {
public:
	float mX;//中心のX座標
	float mY;//中心のY座標
	float mW;//幅の半分
	float mH;//高さの半分

	CTexture mTexture;
//	int mRow, mCol; //テクスチャ内の行数と列数

	//描画処理の宣言
	void Render();
	void Render(int index);
	//コンストラクタの宣言
	CRectangle();
	CRectangle(float x, float y, float w, float h);
	//中心座標(0,0)で幅と高さを指定するコンストラクタ
	CRectangle(float w, float h);
	//Y軸での衝突処理
	float CollisionY(const CRectangle &r) const;
	//6
	//X軸での衝突処理
	float CollisionX(const CRectangle &r) const;
	//7
	//四角形の衝突処理
//	void Collision(CRectangle &r, float &mx, float &my);
//	bool Collision(CRectangle &r);
	//SetXYWH
	void SetXYWH(int posx, int posy, int width, int height);
	//LoadTexture
	void LoadTexture(char* filename);
	void LoadTexture(char* filename, int row, int col);
};

#endif
