#include "glut.h"

//Init関数
//最初に一度だけ呼ばれる関数
void Init() {
}
//MailLoop関数
//プログラムの実行中、繰り返し呼ばれる関数
void MainLoop() {
	//１．三角形を描画する
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0f, 100.0f);
	glVertex2f(-100.0f, -100.0f);
	glVertex2f(100.0f, -100.0f);
	glEnd();
}
