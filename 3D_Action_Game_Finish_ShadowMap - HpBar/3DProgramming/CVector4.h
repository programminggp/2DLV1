#pragma once

#include "CVector3.h"

class CMatrix44;

/* 4次元（3次元）ベクトルクラスの定義
3次元座標（3次元ベクトル）と、
4×4行列との演算を行う
1行4列の行列
*/
class CVector4 : public CVector3 {
public:
	float w;	//w：1.0

	CVector4();

	CVector4(float x, float y, float z);
	CVector4(float x, float y, float z, float w);

	//CMatrix44との掛け算
	const CVector4 operator * (const CMatrix44 &m) const;

	/* CVector4同士の加算
	ただし、x,y,zのみ
	*/
	const CVector4 operator + (const CVector4 &v) const;
	/* CVector4とfloatの掛け算
	ただし、x,y,zのみ
	*/
	const CVector4 operator * (float f) const;
	/*内積を求める
	ただし、x,y,zのみ
	*/
	float dot(const CVector4 &v);
	/* ベクトルの大きさを返す
	ただし、x,y,zのみ
	*/
	float length();
	/* 正規化したベクトルを返す
	ベクトルの正規化：大きさを1にする
	*/
	CVector4 normalize();
	/* 指定されたベクトルの方向へ向ける為の回転角度を得る
	return:｜X軸の回転角度　Y軸の回転角度　０度｜
	*/
	CVector4 getRotationTowards(const CVector4 &dir);
	/* 指定された半径の球上の位置をランダムに設定する
	ベクトル｜0.0 0.0 1.0｜をX軸でランダムに回転させ、次に
	Y軸でランダムに回転させ、半径を掛けた値を設定する
	*/
	void setRandomPositionSphere(float radius);
};
