#include "CCamera.h"
#include "glut.h"

void CCamera::Start(double left, double right, double bottom, double top)
{
	//プロジェクション行列へ切り替え
	glMatrixMode(GL_PROJECTION);
	//プロジェクション行列の退避
	glPushMatrix();
	//プロジェクション行列の初期化
	glLoadIdentity();
	//表示エリアの設定
	gluOrtho2D(left, right, bottom, top);
}

void CCamera::End()
{
	//プロジェクション行列を戻す
	glPopMatrix();
	//モデルビューモードへ切り替え
	glMatrixMode(GL_MODELVIEW);
}
