#ifndef CCOLLISION_H
#define CCOLLISION_H

class CRectangle;
/*
CCollision
衝突判定を行います
*/
class CCollision {
public:
	/*
	四角形と四角形の衝突判定を行います
	戻り値：衝突している場合はtrue。衝突していない場合はfalse
	col1:四角形のインスタンス
	col2:四角形のインスタンス
	*x,*y:衝突している場合は、X軸とY軸で重なっている大きさを比較して、
	　　　小さい方の軸を、大きさ分減算する。
	*/
	static bool Collision(const CRectangle& col1, const CRectangle& col2, float *x, float*y);
	/*
	四角形と四角形の衝突判定を行います
	戻り値：衝突している場合はtrue。衝突していない場合はfalse
	col1:四角形のインスタンス
	col2:四角形のインスタンス
	*/
	static bool Collision(const CRectangle& col1, const CRectangle& col2);
	/*
	四角形と円の衝突判定
	戻り値：衝突している場合はtrue。衝突していない場合はfalse
	circ:円のインスタンス
	rect:四角形のインスタンス
	*mx,*my:衝突している場合は、X軸とY軸で重なっている大きさを比較して、
	　　　小さい方の軸を、大きさ分減算する。
	 */
	static bool CollisionCR(const CRectangle& circ, const CRectangle& rect, float *mx, float*my);
};


#endif
