#include "CCollision.h"
#include "CCharacter.h"

bool CCollision::Collision(const CCharacter *col1, const CCharacter *col2, float *mx, float*my) {
	//四角形衝突時の移動量を求める
	float x = col1->mX - col2->mX;
	if (x < 0.0f) x = -x;
	x = x - col1->mW - col2->mW;
	if (x > 0.0f) return false;

	float y = col1->mY - col2->mY;
	if (y < 0.0f) y = -y;
	y = y - col1->mH - col2->mH;
	if (y > 0.0f) return false;

	//移動量を求める
	if (col2->mX < col1->mX) {
		x = -x;
	}
	if (col2->mY < col1->mY) {
		y = -y;
	}
	//移動量の絶対値を求める
	float absx = x, absy = y;
	if (x < 0) absx = -x;
	if (y < 0) absy = -y;
	//絶対値の小さい方向に移動量を加算する
	if (absx < absy) {
		*mx += x;
	}
	else {
		*my += y;
	}
	return true;
}

bool CCollision::Collision(const CCharacter *col1, const CCharacter *col2) {
	//四角形衝突時の移動量を求める
	float x = col1->mX - col2->mX;
	if (x < 0.0f) x = -x;
	x = x - col1->mW - col2->mW;
	if (x > 0.0f) return false;
	float y = col1->mY - col2->mY;
	if (y < 0.0f) y = -y;
	y = y - col1->mH - col2->mH;
	if (y > 0.0f) return false;
	return true;
}

