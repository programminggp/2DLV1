#pragma once
#include "CMatrix.h"
class CVector2;
class CVector4;

/// <summary>
/// 3次元ベクトル
/// </summary>
class CVector
{
public:
	// コンストラクタ（引数なし）
	CVector();
	// コンストラクタ（xyz）
	CVector(float x, float y, float z);
	// コンストラクタ（CVector2）
	CVector(const CVector2& v);
	// コンストラクタ（CVector2 + z）
	CVector(const CVector2& v, float z);
	// コンストラクタ（CVector4）
	CVector(const CVector4& v);
	// デストラクタ
	~CVector();

	// CVector == CVector の結果を返す
	bool operator == (const CVector& v) const;
	// CVector != CVector の結果を返す
	bool operator != (const CVector& v) const;

	// -CVector の演算結果を返す
	CVector operator - () const;

	// CVector + CVector の演算結果を返す
	CVector operator + (const CVector& v) const;
	// CVector += CVector で演算結果を自身に代入
	void operator += (const CVector& v);

	// CVector - CVector の演算結果を返す
	CVector operator - (const CVector& v) const;
	// CVector -= CVector で演算結果を自身に代入
	void operator -= (const CVector& v);

	// CVector * float の演算結果を返す
	CVector operator * (const float& f) const;
	// CVector *= float で演算結果を自身に代入
	void operator *= (const float& f);
	// CVector * CMatrixの結果をCVectorで返す
	CVector operator * (const CMatrix& m) const;

	// 各軸の値を設定
	void Set(float x, float y, float z);

	// X軸の値を取得
	float X() const;
	// X軸の値を設定
	void X(float x);
	// Y軸の値を取得
	float Y() const;
	// Y軸の値を設定
	void Y(float y);
	// Z軸の値を取得
	float Z() const;
	// Z軸の値を設定
	void Z(float z);

	// ベクトルを正規化
	void Normalize();
	/// <summary>
	/// 正規化したベクトルを取得
	/// </summary>
	/// <returns>正規化したベクトル</returns>
	CVector Normalized() const;

	/// <summary>
	/// 指定したベクトルとの内積を求める
	/// </summary>
	/// <param name="v">相手のベクトル</param>
	/// <returns>内積の結果</returns>
	float Dot(const CVector& v) const;
	/// <summary>
	/// 2つのベクトルの内積を求める
	/// </summary>
	/// <param name="v0">1つ目のベクトル</param>
	/// <param name="v1">2つ目のベクトル</param>
	/// <returns>内積の結果</returns>
	static float Dot(const CVector& v0, const CVector& v1);

	/// <summary>
	/// 指定したベクトルとの外積を求める
	/// </summary>
	/// <param name="v">相手のベクトル</param>
	/// <returns>外積の結果（3次元はベクトル）</returns>
	CVector Cross(const CVector& v) const;
	/// <summary>
	/// 2つのベクトルの外積を求める
	/// </summary>
	/// <param name="v0">1つ目のベクトル</param>
	/// <param name="v1">2つ目のベクトル</param>
	/// <returns>外積の結果（3次元はベクトル）</returns>
	static CVector Cross(const CVector& v0, const CVector& v1);

	/// <summary>
	/// ベクトルの長さを取得
	/// </summary>
	/// <returns>ベクトルの長さ</returns>
	float Length() const;
	/// <summary>
	/// ベクトルの2乗の長さを取得
	/// </summary>
	/// <returns>ベクトルの2乗の長さ</returns>
	float LengthSqr() const;

	/// <summary>
	/// 2点間の距離を求める
	/// </summary>
	/// <param name="p0">1つ目の座標</param>
	/// <param name="p1">2つ目の座標</param>
	/// <returns>2点間の距離</returns>
	static float Distance(const CVector& p0, const CVector& p1);
	/// <summary>
	/// 2つのベクトルの角度を求める
	/// （最短角度を求めるので0～180の値を返す）
	/// </summary>
	/// <param name="v0">1つ目のベクトル</param>
	/// <param name="v1">2つ目のベクトル</param>
	/// <returns>2つのベクトルの角度（ディグリー）</returns>
	static float Angle(const CVector& v0, const CVector& v1);

	/// <summary>
	/// 2点間を線形補間する
	/// </summary>
	/// <param name="a">開始位置</param>
	/// <param name="b">終了位置</param>
	/// <param name="t">補間割合（0.0f～1.0f）</param>
	/// <returns>線形補間の結果</returns>
	static CVector Lerp(const CVector& a, const CVector& b, float t);
	/// <summary>
	/// 2つのベクトル間を球面線形補間する
	/// </summary>
	/// <param name="a">開始ベクトル</param>
	/// <param name="b">終了ベクトル</param>
	/// <param name="t">補間割合（0.0f～1.0f）</param>
	/// <returns></returns>
	static CVector Slerp(const CVector& a, const CVector& b, float t);

	// 0ベクトル [0, 0, 0]
	const static CVector zero;
	// 1ベクトル [1, 1, 1]
	const static CVector one;
	// 左ベクトル [-1, 0, 0]
	const static CVector left;
	// 右ベクトル [1, 0, 0]
	const static CVector right;
	// 上ベクトル [0, 1, 0]
	const static CVector up;
	// 下ベクトル [0, -1, 0]
	const static CVector down;
	// 前方ベクトル [0, 0, 1]
	const static CVector forward;
	// 後方ベクトル [0, 0, -1]
	const static CVector back;

private:
	// 3D各軸での値を設定
	float mX, mY, mZ;
};

/// <summary>
/// 2次元ベクトル
/// </summary>
class CVector2
{
public:
	// コンストラクタ（引数なし）
	CVector2();
	// コンストラクタ（xy）
	CVector2(float x, float y);
	// コンストラクタ（CVector）
	CVector2(const CVector& v);
	// デストラクタ
	~CVector2();

	// CVector2 == CVector2 の結果を返す
	bool operator == (const CVector2& v) const;
	// CVector2 != CVector2 の結果を返す
	bool operator != (const CVector2& v) const;

	// -CVector2 の演算結果を返す
	CVector2 operator - () const;

	// CVector2 + CVector2 の演算結果を返す
	CVector2 operator + (const CVector2& v) const;
	// CVector2 += CVector2 で演算結果を自身に代入
	void operator += (const CVector2& v);

	// CVector2 - CVector2 の演算結果を返す
	CVector2 operator - (const CVector2& v) const;
	// CVector2 -= CVector2 で演算結果を自身に代入
	void operator -= (const CVector2& v);

	// CVector2 * float の演算結果を返す
	CVector2 operator * (const float& f) const;
	// CVector2 *= float で演算結果を自身に代入
	void operator *= (const float& f);
	// CVector2 * CMatrixの結果をCVector2で返す
	CVector2 operator * (const CMatrix& m);

	// 各軸の値を設定
	void Set(float x, float y);

	// X軸の値を取得
	float X() const;
	// X軸の値を設定
	void X(float x);
	// Y軸の値を取得
	float Y() const;
	// Y軸の値を設定
	void Y(float y);

	// ベクトルを正規化
	void Normalize();
	/// <summary>
	/// 正規化したベクトルを取得
	/// </summary>
	/// <returns>正規化したベクトル</returns>
	CVector2 Normalized() const;

	/// <summary>
	/// 指定したベクトルとの内積を求める
	/// </summary>
	/// <param name="v">相手のベクトル</param>
	/// <returns>内積の結果</returns>
	float Dot(const CVector2& v) const;
	/// <summary>
	/// 2つのベクトルの内積を求める
	/// </summary>
	/// <param name="v0">1つ目のベクトル</param>
	/// <param name="v1">2つ目のベクトル</param>
	/// <returns>内積の結果</returns>
	static float Dot(const CVector2& v0, const CVector2& v1);

	/// <summary>
	/// 指定したベクトルとの外積を求める
	/// </summary>
	/// <param name="v">相手のベクトル</param>
	/// <returns>外積の結果</returns>
	float Cross(const CVector2& v) const;
	/// <summary>
	/// 2つのベクトルの外積を求める
	/// </summary>
	/// <param name="v0">1つ目のベクトル</param>
	/// <param name="v1">2つ目のベクトル</param>
	/// <returns>外積の結果</returns>
	static float Cross(const CVector2& v0, const CVector2& v1);

	/// <summary>
	/// ベクトルの長さを取得
	/// </summary>
	/// <returns>ベクトルの長さ</returns>
	float Length() const;
	/// <summary>
	/// ベクトルの2乗の長さを取得
	/// </summary>
	/// <returns>ベクトルの2乗の長さ</returns>
	float LengthSqr() const;

	/// <summary>
	/// 2点間の距離を求める
	/// </summary>
	/// <param name="p0">1つ目の座標</param>
	/// <param name="p1">2つ目の座標</param>
	/// <returns>2点間の距離</returns>
	static float Distance(const CVector2& p0, const CVector2& p1);
	/// <summary>
	/// 2つのベクトルの角度を求める
	/// （最短角度を求めるので0～180の値を返す）
	/// </summary>
	/// <param name="v0">1つ目のベクトル</param>
	/// <param name="v1">2つ目のベクトル</param>
	/// <returns>2つのベクトルの角度（ディグリー）</returns>
	static float Angle(const CVector2& v0, const CVector2& v1);

	// 0ベクトル [0, 0]
	const static CVector2 zero;
	// 1ベクトル [1, 1]
	const static CVector2 one;
	// 左ベクトル [-1, 0]
	const static CVector2 left;
	// 右ベクトル [1, 0]
	const static CVector2 right;
	// 上ベクトル [0, 1]
	const static CVector2 up;
	// 下ベクトル [0, -1]
	const static CVector2 down;

private:
	// 2D各軸での値を設定
	float mX, mY;
};

//ベクトルクラス（4次元）
class CVector4
{
public:
	// コンストラクタ（引数なし）
	CVector4();
	// コンストラクタ（xyzw）
	CVector4(float x, float y, float z, float w);
	// コンストラクタ（xyz）
	CVector4(float x, float y, float z);
	// コンストラクタ（CVector）
	CVector4(const CVector& v);
	// コンストラクタ（CVector + w）
	CVector4(const CVector& v, float w);

	//各軸での値の設定
	//Set(X座標, Y座標, Z座標, W)
	void Set(float x, float y, float z, float w);
	//Set(X座標, Y座標, Z座標)
	void Set(float x, float y, float z);
	//Xの値を得る
	float X() const;
	//Xの値を設定
	void X(float x);
	//Yの値を得る
	float Y() const;
	//Yの値を設定
	void Y(float y);
	//Zの値を得る
	float Z() const;
	//Zの値を設定
	void Z(float z);
	//Wの値を得る
	float W() const;
	//Wの値を設定
	void W(float w);
	//インデックス値を指定して値を取得
	float V(int n) const;
	//インデックス値を指定して値を設定
	void V(int n, float v);

	//代入演算子
	//CVector4 = CVector でCVectorの内容を自身に代入
	void operator=(const CVector& v);

	//比較演算子
	//CVector4 == CVector4 の結果を返す
	bool operator==(const CVector4& v) const;
	//CVector4 != CVector4 の結果を返す
	bool operator!=(const CVector4& v) const;

	//+演算子のオーバーロード
	//CVector4 + CVector4 の演算結果を返す
	CVector4 operator+(const CVector4& v) const;
	//CVector4 += CVector4 で演算結果を自身に代入
	void operator+=(const CVector4& v);


	//-演算子のオーバーロード
	//CVector4 - CVector4 の演算結果を返す
	CVector4 operator-(const CVector4& v) const;
	//CVector4 -= CVector4 で演算結果を自身に代入
	void operator-=(const CVector4& v);

	//*演算子のオーバーロード
	//CVector4 * float の演算結果を返す
	CVector4 operator*(const float& f) const;
	//CVector4 *= float で演算結果を自身に代入
	void operator*=(const float& f);

	//CVector4 * CMatrix の演算結果を返す
	CVector4 operator*(const CMatrix& m) const;

private:
	//4Dでの値を設定
	float mX, mY, mZ, mW;
};

//CMatrix * CVector の演算結果を返す
CVector operator * (const CMatrix& m, const CVector& v);
//CMatrix * CVector4 の演算結果を返す
CVector4 operator * (const CMatrix& m, const CVector4& v);
