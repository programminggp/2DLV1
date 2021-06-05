#include "CMatrix44.h"
#define _USE_MATH_DEFINES	//数学ライブラリのM_PIを有効にする
#include <math.h>	//数学ライブラリのインクルード


CMatrix44::CMatrix44() {
	identity();	//単位行列に設定
}

/* 単位行列の設定
| 1 0 0 0 |
| 0 1 0 0 |
| 0 0 1 0 |
| 0 0 0 1 |
*/
void CMatrix44::identity() {
	for (int i = 0; i < 16; i++) {
		f[i] = 0.0f;
	}
	m00 = m11 = m22 = m33 = 1.0f;
}
/* Y軸回転行列の設定
| cos 0 -sin 0 |
|  0  1   0  0 |
| sin 0  cos 0 |
|  0  0   0  1 |
*/
void CMatrix44::rotationY(float deg) {
	float r = deg * M_PI / 180.0f;
	m[0][0] = cos(r);
	m[2][2] = cos(r);
	m[2][0] = sin(r);
	m[0][2] = -sin(r);
}
/* X軸回転行列の設定
| 1   0    0   0 |
| 0  cos  sin  0 |
| 0 -sin  cos  0 |
| 0   0    0   1 |
*/
void CMatrix44::rotationX(float deg) {
	float r = deg * M_PI / 180.0f;
	m[1][1] = cos(r);
	m[2][2] = cos(r);
	m[2][1] = -sin(r);
	m[1][2] = sin(r);
}
void CMatrix44::rotationZ(float deg) {
	float r = deg * M_PI / 180.0f;
	m[0][0] = cos(r);
	m[1][1] = cos(r);
	m[1][0] = -sin(r);
	m[0][1] = sin(r);
}
/* 移動行列の設定
| 1 0 0 0 |
| 0 1 0 0 |
| 0 0 1 0 |
| x y z 1 |
*/
void CMatrix44::translate(float pos[3]) {
	m[3][0] = pos[0];
	m[3][1] = pos[1];
	m[3][2] = pos[2];
}
/* 頂点との掛け算
| x y z 1 | * | a b c d |
| e f g h |
| i j k l |
| m n o p |
x = x*a + y*e + z*i + 1*m
y = x*b + y*f + z*j + 1*n
z = x*c + y*g + z*k + 1*o
*/
void CMatrix44::multi(float *x, float *y, float *z) {
	float a = *x, b = *y, c = *z;
	*x = a * m[0][0] + b * m[1][0] + c * m[2][0] + 1.0f * m[3][0];
	*y = a * m[0][1] + b * m[1][1] + c * m[2][1] + 1.0f * m[3][1];
	*z = a * m[0][2] + b * m[1][2] + c * m[2][2] + 1.0f * m[3][2];
}
//行列同士の掛け算
const CMatrix44 CMatrix44::operator * (const CMatrix44 &r) const {
	CMatrix44 tmp;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tmp.m[i][j] = 0.0f;
			for (int k = 0; k < 4; k++) {
				tmp.m[i][j] += r.m[i][k] * m[k][j];
			}
		}
	}
	return tmp;
}

/* ベクトルから移動行列を作成する
v：ベクトル｜x,y,z｜
*/
void CMatrix44::translate(CVector4 v) {
	m[3][0] = v.x;
	m[3][1] = v.y;
	m[3][2] = v.z;
}

void CMatrix44::translate(CVector3 v) {
	m[3][0] = v.x;
	m[3][1] = v.y;
	m[3][2] = v.z;
}


void CMatrix44::SetQuaternion(float x, float y, float z, float w) {
	m00 = 1 - 2 * y*y - 2 * z*z;	m01 = 2 * x*y + 2 * w*z;		m02 = 2 * x*z - 2 * w*y;		m03 = 0;
	m10 = 2 * x*y - 2 * w*z;		m11 = 1 - 2 * x*x - 2 * z*z;	m12 = 2 * y*z + 2 * w*x;		m13 = 0;
	m20 = 2 * x*z + 2 * w*y;		m21 = 2 * y*z - 2 * w*x;		m22 = 1 - 2 * x*x - 2 * y*y;	m23 = 0;
	m30 = 0;						m31 = 0;						m32 = 0;						m33 = 1;
}

//行列同士の掛け算
const CMatrix44 CMatrix44::operator * (float f) const {
	CMatrix44 tmp;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tmp.m[i][j] = m[i][j] * f;
		}
	}
	return tmp;
}

void CMatrix44::operator += (const CMatrix44 &r) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] += r.m[i][j];
		}
	}
}

const CMatrix44 CMatrix44::operator + (const CMatrix44 &r) const {
	CMatrix44 tmp;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
				tmp.m[i][j] = r.m[i][j] + m[i][j];
		}
	}
	return tmp;
}
//38
/*
getInverse
逆行列の取得
*/
CMatrix44 CMatrix44::getInverse(void)
{
	float det = 0.0f;
	det += m00*m11*m22*m33 + m00*m12*m23*m31 + m00*m13*m21*m32;
	det += m01*m10*m23*m32 + m01*m12*m20*m33 + m01*m13*m22*m30;
	det += m02*m10*m21*m33 + m02*m11*m23*m30 + m02*m13*m20*m31;
	det += m03*m10*m22*m31 + m03*m11*m20*m32 + m03*m12*m21*m30;

	det -= m00*m11*m23*m32 + m00*m12*m21*m33 + m00*m13*m22*m31;
	det -= m01*m10*m22*m33 + m01*m12*m23*m30 + m01*m13*m20*m32;
	det -= m02*m10*m23*m31 + m02*m11*m20*m33 + m02*m13*m21*m30;
	det -= m03*m10*m21*m32 + m03*m11*m22*m30 + m03*m12*m20*m31;

	CMatrix44 b;

	b.m00 = m11*m22*m33 + m12*m23*m31 + m13*m21*m32 - m11*m23*m32 - m12*m21*m33 - m13*m22*m31;
	b.m01 = m01*m23*m32 + m02*m21*m33 + m03*m22*m31 - m01*m22*m33 - m02*m23*m31 - m03*m21*m32;
	b.m02 = m01*m12*m33 + m02*m13*m31 + m03*m11*m32 - m01*m13*m32 - m02*m11*m33 - m03*m12*m31;
	b.m03 = m01*m13*m22 + m02*m11*m23 + m03*m12*m21 - m01*m12*m23 - m02*m13*m21 - m03*m11*m22;

	b.m10 = m10*m23*m32 + m12*m20*m33 + m13*m22*m30 - m10*m22*m33 - m12*m23*m30 - m13*m20*m32;
	b.m11 = m00*m22*m33 + m02*m23*m30 + m03*m20*m32 - m00*m23*m32 - m02*m20*m33 - m03*m22*m30;
	b.m12 = m00*m13*m32 + m02*m10*m33 + m03*m12*m30 - m00*m12*m33 - m02*m13*m30 - m03*m10*m32;
	b.m13 = m00*m12*m23 + m02*m13*m20 + m03*m10*m22 - m00*m13*m22 - m02*m10*m23 - m03*m12*m20;

	b.m20 = m10*m21*m33 + m11*m23*m30 + m13*m20*m31 - m10*m23*m31 - m11*m20*m33 - m13*m21*m30;
	b.m21 = m00*m23*m31 + m01*m20*m33 + m03*m21*m30 - m00*m21*m33 - m01*m23*m30 - m03*m20*m31;
	b.m22 = m00*m11*m33 + m01*m13*m30 + m03*m10*m31 - m00*m13*m31 - m01*m10*m33 - m03*m11*m30;
	b.m23 = m00*m13*m21 + m01*m10*m23 + m03*m11*m20 - m00*m11*m23 - m01*m13*m20 - m03*m10*m21;

	b.m30 = m10*m22*m31 + m11*m20*m32 + m12*m21*m30 - m10*m21*m32 - m11*m22*m30 - m12*m20*m31;
	b.m31 = m00*m21*m32 + m01*m22*m30 + m02*m20*m31 - m00*m22*m31 - m01*m20*m32 - m02*m21*m30;
	b.m32 = m00*m12*m31 + m01*m10*m32 + m02*m11*m30 - m00*m11*m32 - m01*m12*m30 - m02*m10*m31;
	b.m33 = m00*m11*m22 + m01*m12*m20 + m02*m10*m21 - m00*m12*m21 - m01*m10*m22 - m02*m11*m20;

	CMatrix44 tmp = b * (1 / det);
	//CMatrix44 nml;
	//nml = (*this) * (*this);
	//CMatrix44 tnml;
	//tnml = tmp * (*this);

	return tmp;
};

CMatrix44 CMatrix44::getTranspose() {
	CMatrix44 tmp;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tmp.m[i][j] = m[j][i];
		}
	}
	return tmp;
}

void CMatrix44::scale(const CVector3 &v) {
	identity();
	m[0][0] = v.x;
	m[1][1] = v.y;
	m[2][2] = v.z;
}

const CVector3 CMatrix44::operator * (const CVector3& v) const {
	CVector3 t;
	t.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3];
	t.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3];
	t.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3];
	return t;
}



const CVector4 CMatrix44::operator * (const CVector4& v) const {
	CVector4 t;
	t.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
	t.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
	t.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
	t.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;
	return t;
}
