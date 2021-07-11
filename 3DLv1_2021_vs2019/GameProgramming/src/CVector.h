#ifndef CVECTOR_H
#define CVECTOR_H
#include "CMatrix.h"
/*
ベクトルクラス
ベクトルデータを扱います
*/
class CVector {
public:
	//3D各軸での値を設定
	float mX, mY, mZ;
	//各軸での値の設定
	//Set(X座標, Y座標, Z座標)
	void Set(float x, float y, float z);
	//デフォルトコンストラクタ
	CVector();
	//コンストラクタ
	//CVector(X座標, Y座標, Z座標)
	CVector(float x, float y, float z);
	//CVector * CMatrixの結果をCVectorで返す
	CVector operator*(const CMatrix &m);
	//-演算子のオーバーロード
	//CVector - CVector の演算結果を返す
	CVector operator-(const CVector &v);
	//ベクトルの長さを返す
	float Length();
	//内積
	//Dot(ベクトル)
	float Dot(const CVector &v);
	//外積
	//Cross(ベクトル)
	CVector Cross(const CVector &v);
	//*演算子のオーバーロード
	//CVector * float の演算結果を返す
	CVector operator*(const float &f);
	//正規化
	//大きさ1のベクトルを返す
	CVector Normalize();
	//+演算子のオーバーロード
	//CVector + CVector の演算結果を返す
	CVector operator+(const CVector &v);
	//Y軸での回転角度の取得
	//度度を返す（Z軸＋が0度）
	float GetRotationY();
	//X軸での回転角度の取得
	//度度を返す（Z軸＋が0度）
	//GetRotationX(Y軸方向)
	float GetRotationX(CVector& y);

};
#endif
