#pragma once

#include "CVector3.h"
#include "CVector4.h"

/* 4x4行列クラスの定義
| f[ 0] f[ 1] f[ 2] f[ 3] |
| f[ 4] f[ 5] f[ 6] f[ 7] |
| f[ 8] f[ 9] f[10] f[11] |
| f[12] f[13] f[14] f[15] |

| m[0][0] m[0][1] m[0][2] m[0][3] |
| m[1][0] m[1][1] m[1][2] m[1][3] |
| m[2][0] m[2][1] m[2][2] m[2][3] |
| m[3][0] m[3][1] m[3][2] m[3][3] |

| m00 m10 m20 m30 |
| m01 m11 m21 m31 |
| m02 m12 m22 m32 |
| m03 m13 m23 m33 |

*/
class CMatrix44 {
public:
	/* 共用体：領域は共通
	f[0]、m[0][0]、m00は同じエリアを参照する
	f[1]、m[0][1]、m10は同じエリアを参照する
	f[15]、m[3][3]、m33は同じエリアを参照する
	*/
	union //共用体　共通の領域を参照する
	{
		float	f[16];
		float	m[4][4];
		struct
		{
			float	m00, m10, m20, m30,
			m01, m11, m21, m31,
			m02, m12, m22, m32,
			m03, m13, m23, m33;
		};
	};

	CMatrix44();

	/* 単位行列の設定
	| 1 0 0 0 |
	| 0 1 0 0 |
	| 0 0 1 0 |
	| 0 0 0 1 |
	*/
	void identity();
	/* Y軸回転行列の設定
	| cos 0 -sin 0 |
	|  0  1   0  0 |
	| sin 0  cos 0 |
	|  0  0   0  1 |
	*/
	void rotationY(float deg);
	/* X軸回転行列の設定
	| 1   0    0   0 |
	| 0  cos  sin  0 |
	| 0 -sin  cos  0 |
	| 0   0    0   1 |
	*/
	void rotationX(float deg);
	/* Z軸回転行列の設定
	| cos sin   0   0 |
	|-sin cos   0   0 |
	| 0    0    1   0 |
	| 0    0    0   1 |
	*/
	void rotationZ(float deg);
	/* 移動行列の設定
	| 1 0 0 0 |
	| 0 1 0 0 |
	| 0 0 1 0 |
	| x y z 1 |
	*/
	void translate(float pos[3]);
	/* 頂点との掛け算
	| x y z 1 | * | a b c d |
	| e f g h |
	| i j k l |
	| m n o p |
	x = x*a + y*e + z*i + 1*m
	y = x*b + y*f + z*j + 1*n
	z = x*c + y*g + z*k + 1*o
	*/
	void multi(float *x, float *y, float *z);
	//行列同士の掛け算
	const CMatrix44 operator * (const CMatrix44 &r) const;
	// ベクトルから移動行列を作成するメソッドの宣言
	void translate(CVector4 v);
	void translate(CVector3 v);
	void SetQuaternion(float x, float y, float z, float w);
	const CMatrix44 operator * (float f) const;
	void operator += (const CMatrix44 &r);
	const CMatrix44 operator + (const CMatrix44 &r) const;
	//38
	//逆行列の取得
	CMatrix44 getInverse(void);
	CMatrix44 getTranspose();
	void scale(const CVector3&);
	const CVector3 operator * (const CVector3& v) const;
	const CVector4 operator * (const CVector4& v) const;
};
