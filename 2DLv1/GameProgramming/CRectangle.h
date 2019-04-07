#ifndef CRECTANGLE_H
#define CRECTANGLE_H

/*
CRectangleクラス
四角形プログラムの定義
*/
class CRectangle {
public:
	float mPx;//位置X座標
	float mPy;//位置Y座標
	float mSx;//大きさX座標
	float mSy;//大きさY座標
	//描画処理の宣言
	void Render();
};

#endif
