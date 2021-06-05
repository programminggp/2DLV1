#pragma once

#include "CVector3.h"

/* カメラクラス（視点のクラス）
目の位置と目的の位置を保持し、
カメラ行列（ビュー変換行列）を設定する
*/
class CCamera {
public:
	float pos[3];	//注視点 [0]:X座標 [1]:Y座標 [2]:Z座標
	float eye[3];	//視点 [0]:X座標 [1]:Y座標 [2]:Z座標
	CVector3 mUp;	//カメラの上方向

	//カメラの上方向の初期化
	CCamera();

	/* 視点と注視点の設定
	void setPos(float x, float y, float z)
	x:注視点のX座標 y:注視点のY座標 z:注視点のZ座標
	規定の視点は注視点よりYへ+2、Zへ+4移動
	*/
	void setPos(float x, float y, float z);

	/* 更新処理
	キーにより視点を変更する
	J：左前から　K：前面から　L：右前から
	U：左後ろから　I：後ろから　O：右後ろから
	*/
	void update();

	void update(CVector3 eye, CVector3 pos, CVector3 up);
	//38
	static CMatrix44 mCameraInverse;
	static CMatrix44  GetInverse();
};
