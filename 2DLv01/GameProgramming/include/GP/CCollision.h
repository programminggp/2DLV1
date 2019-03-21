#ifndef CCOLLISION_H
#define CCOLLISION_H

class CRectangle;

class CCollision {
public:
	static bool Collision(const CRectangle& col1, const CRectangle& col2, float *x, float*y);
	static bool Collision(const CRectangle& col1, const CRectangle& col2);
};


#endif
