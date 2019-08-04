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

bool CCollision::CollisionCR(const CRectangle& circ, const CRectangle& rect, float *mx, float*my) {
	float dx = rect.mX - circ.mX;
	dx = (dx < 0.0f) ? -dx : dx;
	dx = dx - rect.mW - circ.mW;
	if (dx < 0.0f) {
		float dy = rect.mY - circ.mY;
		dy = (dy < 0.0f) ? -dy : dy;
		dy = dy - rect.mW - circ.mW;
		if (dy < 0.0f) {
			dx = (dx < 0.0f) ? -dx : dx;
			dy = (dy < 0.0f) ? -dy : dy;
			if (dx < dy) {
				if (circ.mX < rect.mX) {
					*mx -= dx;
				}
				else {
					*mx += dx;
				}
			}
			else {
				if (circ.mY < rect.mY) {
					*my -= dy;
				}
				else {
					*my += dy;
				}
			}
			return true;
		}
	}
	return false;
}


