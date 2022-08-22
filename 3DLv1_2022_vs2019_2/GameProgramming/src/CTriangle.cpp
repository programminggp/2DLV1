#include "CTriangle.h"
#include "glut.h"

//頂点座標設定
//Vertex(頂点1, 頂点2, 頂点3)
void CTriangle::Vertex(const CVector& v0, const CVector& v1, const CVector& v2) {
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}

//法線設定
//Normal(法線ベクトル)
void CTriangle::Normal(const CVector& n) {
	mN = n;
}

//描画
void CTriangle::Render() {
	glBegin(GL_TRIANGLES);
	glNormal3f(mN.X(), mN.Y(), mN.Z());
	glVertex3f(mV[0].X(), mV[0].Y(), mV[0].Z());
	glVertex3f(mV[1].X(), mV[1].Y(), mV[1].Z());
	glVertex3f(mV[2].X(), mV[2].Y(), mV[2].Z());
	glEnd();
}
