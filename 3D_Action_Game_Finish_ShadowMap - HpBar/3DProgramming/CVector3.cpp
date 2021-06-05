#include "CVector3.h"
#include "CMatrix44.h"

#define _USE_MATH_DEFINES	//数学ライブラリのM_PIを有効にする
#include <math.h>	//数学ライブラリのインクルード
#include "stdlib.h"

CVector3::CVector3() : x(0.0f), y(0.0f), z(0.0f) {}

CVector3::CVector3(float x, float y, float z) : x(x), y(y), z(z) {}
//CMatrix44との掛け算
const CVector3 CVector3::operator * (const CMatrix44 &m) const {
	CVector3 tmp;
	tmp.x = x * m.m[0][0] + y * m.m[1][0] + z * m.m[2][0] + 1.0f * m.m[3][0];
	tmp.y = x * m.m[0][1] + y * m.m[1][1] + z * m.m[2][1] + 1.0f * m.m[3][1];
	tmp.z = x * m.m[0][2] + y * m.m[1][2] + z * m.m[2][2] + 1.0f * m.m[3][2];
	return tmp;
}
/* CVector3同士の演算
*/
const CVector3 CVector3::operator + (const CVector3 &v) const {
	return CVector3(x + v.x, y + v.y, z + v.z);
}
void CVector3::operator += (const CVector3 &v) {
	x += v.x;
	y += v.y;
	z += v.z;
}
const CVector3 CVector3::operator - (const CVector3 &v) const {
	return CVector3(x - v.x, y - v.y, z - v.z);
}
void CVector3::operator -= (const CVector3 &v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}
const CVector3 CVector3::operator * (const CVector3 &v) const {
	return CVector3(x * v.x, y * v.y, z * v.z);
}
void CVector3::operator *= (const CVector3 &v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
}
const CVector3 CVector3::operator / (const CVector3 &v) const {
	return CVector3(x / v.x, y / v.y, z / v.z);
}
void CVector3::operator /= (const CVector3 &v) {
	x /= v.x;
	y /= v.y;
	z /= v.z;
}
const CVector3 CVector3::operator * (float f) const {
	return CVector3(x * f, y * f, z * f);
}
void CVector3::operator *= (float f) {
	x *= f;
	y *= f;
	z *= f;
}
const CVector3 CVector3::operator / (float f) const {
	return CVector3(x / f, y / f, z / f);
}
void CVector3::operator /= (float f) {
	x /= f;
	y /= f;
	z /= f;
}
/*内積を求める
ただし、x,y,zのみ
*/
float CVector3::dot(const CVector3 &v) const {
	return x*v.x + y*v.y + z*v.z;
}
/* ベクトルの大きさを返す
ただし、x,y,zのみ
*/
//30
float CVector3::length() const {
//float CVector3::length() {
	return sqrt(x*x + y*y + z*z);
}
/* 正規化したベクトルを返す
ベクトルの正規化：大きさを1にする
*/
//30
CVector3 CVector3::normalize() const {
	float len = length();
	//28
	if (len == 0)
		return CVector3();
	return CVector3(x / len, y / len, z / len);
}
/* 指定されたベクトルの方向へ向ける為の回転角度を得る
return:｜X軸の回転角度　Y軸の回転角度　０度｜
*/
CVector3 CVector3::getRotationTowards(const CVector3 &dir) {
	//目的となるベクトルの、XZ平面上での長さを求める
	float sx = sqrt(dir.x*dir.x + dir.y*dir.y);
	//目的となるベクトルでのX軸での回転角度、Y軸での回転角度を求める
	CVector3 rot = CVector3(atan2f(-dir.y, sx)*180.0f / M_PI, atan2f(-dir.z, dir.x)*180.0f / M_PI, 0.0f);
	//自分のベクトルの、XZ平面上での長さを求める
	sx = sqrt(x * x + z * z);
	//自分のベクトルでのX軸での回転角度、Y軸での回転角度を求める
	CVector3 rot1(atan2f(-y, sx)*180.0f / M_PI, atan2f(-z, x)*180.0f / M_PI, 0.0f);
	//マイナスの角度はプラスの角度へ変換する（0度～360度の間にする）
	if (rot.x < 0.0f) rot.x += 360.0f;
	if (rot.y < 0.0f) rot.y += 360.0f;
	if (rot1.x < 0.0f) rot1.x += 360.0f;
	if (rot1.y < 0.0f) rot1.y += 360.0f;
	//目的の回転値と自分の回転値との差を求める
	rot1 = rot + rot1 * -1.0f;
	//マイナスの角度はプラスの角度へ変換する（0度～360度の間にする）
	if (rot1.x < 0.0f) rot1.x += 360.0f;
	if (rot1.y < 0.0f) rot1.y += 360.0f;
	return rot1;	//求めた角度を戻す
}
/* 指定された半径の球上の位置をランダムに設定する
ベクトル｜0.0 0.0 1.0｜をX軸でランダムに回転させ、次に
Y軸でランダムに回転させ、半径を掛けた値を設定する
*/
void CVector3::setRandomPositionSphere(float radius) {
	CMatrix44 rotx, roty;
	rotx.rotationX(rand() % 360);	//X軸の回転行列を作成
	roty.rotationY(rand() % 360);	//Y軸の回転行列を作成
	CVector3 vec(0.0f, 0.0f, 1.0f);	//ベクトル作成
	vec = vec * rotx * roty * radius;	//回転し半径を掛ける
	//ベクトル値を設定する
	x = vec.x;
	y = vec.y;
	z = vec.z;
}
