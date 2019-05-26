#include "CCollision.h"
#include "CRectangle.h"

bool CCollision::Collision(const CRectangle& col1, const CRectangle& col2, float *mx, float*my) {
	//四角形衝突時の移動量を求める
	float x = col1.CollisionX(col2);
	float y = col1.CollisionY(col2);
	if (x * y == 0.0f)
		return false;
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

bool CCollision::Collision(const CRectangle& col1, const CRectangle& col2) {
	//四角形衝突時の移動量を求める
	float x = col1.CollisionX(col2);
	float y = col1.CollisionY(col2);
	if (x * y == 0.0f) return false;
	return true;
}

