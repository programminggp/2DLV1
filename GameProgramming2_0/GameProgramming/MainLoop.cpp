#include "glut.h"

/*２．
* 三角形のプログラム
* CTriangleプログラム（クラス）を定義する
*/
class CTriangle
{
public:
	//２．Render処理（メソッド）を宣言する
	void Render();
};
//２．Render処理（メソッド）を定義する
void CTriangle::Render()
{
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0f, 100.0f);
	glVertex2f(-100.0f, -100.0f);
	glVertex2f(100.0f, -100.0f);
	glEnd();
}
//２．CTriangleクラスの変数（インスタンス）を作成する
CTriangle Triangle;

//Init関数
//最初に一度だけ呼ばれる関数
void Init() {
}
//MailLoop関数
//プログラムの実行中、繰り返し呼ばれる関数
void MainLoop() {
	//２．変数TriangleのRender処理を呼び出す
	Triangle.Render();
}
