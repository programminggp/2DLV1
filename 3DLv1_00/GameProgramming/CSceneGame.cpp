#include "CSceneGame.h"
#include "glut.h"
#include "CVector.h"

void CSceneGame::Init() {

}

void CSceneGame::Update() {
	gluLookAt(2.0f, 3.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	float mDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -5.0f);
	glVertex3f(1.0f, 0.0f, -5.0f);
	glVertex3f(1.0f, 1.0f, -5.0f);
	glVertex3f(0.0f, 0.0f, 5.0f);
	glVertex3f(1.0f, 0.0f, 5.0f);
	glVertex3f(1.0f, 1.0f, 5.0f);
	glVertex3f(5.0f, 0.0f, 0.0f);
	glVertex3f(6.0f, 0.0f, 0.0f);
	glVertex3f(6.0f, 1.0f, 0.0f);
	glVertex3f(-5.0f, 0.0f, 0.0f);
	glVertex3f(-4.0f, 0.0f, 0.0f);
	glVertex3f(-4.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glVertex3f(1.0f, 5.0f, 0.0f);
	glVertex3f(1.0f, 6.0f, 0.0f);
	glVertex3f(0.0f, -5.0f, 0.0f);
	glVertex3f(1.0f, -5.0f, 0.0f);
	glVertex3f(1.0f, -4.0f, 0.0f);
	glEnd();
}

//デストラクタ
CSceneGame::~CSceneGame() {

}
