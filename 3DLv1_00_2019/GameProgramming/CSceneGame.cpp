#include "CSceneGame.h"
//OpenGL
#include "glut.h"

void CSceneGame::Init() {
}

void CSceneGame::Update() {
	//視点の設定
	//gluLookAt(視点X, 視点Y, 視点Z, 目標X, 目標Y, 目標Z, 上向X, 上向Y, 上向Z)
	gluLookAt(1.0f, 2.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//描画開始
	//glBegin(形)
	//GL_TRIANGLES：三角形
	glBegin(GL_TRIANGLES);

	//法線（面の向き）の設定
	//glNormal3f(X座標, Y座標, Z座標)
	glNormal3f(0.0f, 1.0f, 0.0f);

	//頂点座標の設定
	//glVertex3f(X座標, Y座標, Z座標)
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -0.5f);

	//面の向きはZ軸方向
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, -0.5f, 0.0f);

	//描画終了
	glEnd();
}
