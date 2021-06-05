#pragma once

class CMatrix44;

class CVector2 {
public:
	float x, y;
	CVector2() : x(0), y(0) {}
	CVector2(float a, float b)
		: x(a), y(b) {}
};

class CVector3 {
public:
	float x, y, z;
	CVector3();
	CVector3(float x, float y, float z);
	//CMatrix44との掛け算
	const CVector3 operator * (const CMatrix44 &m) const;
	/* CVector3同士の演算
	*/
	const CVector3 operator + (const CVector3 &v) const;
	void operator += (const CVector3 &v);
	const CVector3 operator - (const CVector3 &v) const;
	void operator -= (const CVector3 &v);
	const CVector3 operator * (const CVector3 &v) const;
	void operator *= (const CVector3 &v);
	const CVector3 operator / (const CVector3 &v) const;
	void operator /= (const CVector3 &v);
	const CVector3 operator * (float f) const;
	void operator *= (float f);
	const CVector3 operator / (float f) const;
	void operator /= (float f);
	/*内積を求める
	ただし、x,y,zのみ
	*/
	//29
	float dot(const CVector3 &v) const;
	/* ベクトルの大きさを返す
	ただし、x,y,zのみ
	*/
	//30
	float length() const ;
	//float length();
	/* 正規化したベクトルを返す
	ベクトルの正規化：大きさを1にする
	*/
	//30
	CVector3 normalize() const ;
	/* 指定されたベクトルの方向へ向ける為の回転角度を得る
	return:｜X軸の回転角度　Y軸の回転角度　０度｜
	*/
	CVector3 getRotationTowards(const CVector3 &dir);
	/* 指定された半径の球上の位置をランダムに設定する
	ベクトル｜0.0 0.0 1.0｜をX軸でランダムに回転させ、次に
	Y軸でランダムに回転させ、半径を掛けた値を設定する
	*/
	void setRandomPositionSphere(float radius);
	//28
	/*
	外積を求める
	*/
	CVector3 Cross(const CVector3 &v) const {
		return CVector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x).normalize();
	}

};
