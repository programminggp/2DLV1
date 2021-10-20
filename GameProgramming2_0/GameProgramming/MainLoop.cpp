#include "glut.h"

/*２．
* 三角形のプログラム
* CTriangleプログラム（クラス）を定義する
*/
class CTriangle
{
	//３．変数を宣言する
	float x0, y0, x1, y1, x2, y2;
public:
	//３．デフォルトコンストラクタを宣言する
	CTriangle();
	//４．引数付きのコンストラクタを宣言する
	CTriangle(float x0, float y0, float x1, float y1, float x2, float y2);
	//２．Render処理（メソッド）を宣言する
	void Render();
};
//３．デフォルトコンストラクタを定義する
CTriangle::CTriangle()
	//３．変数に値を代入する
	: x0(-100.0f), y0(100.0f), x1(0.0f), y1(-100.0f), x2(100.0f), y2(100.0f)
{
}
//４．引数付きのコンストラクタを定義する
CTriangle::CTriangle(float ax0, float ay0, float ax1, float ay1, float ax2, float ay2)
	: x0(ax0), y0(ay0), x1(ax1), y1(ay1), x2(ax2), y2(ay2)
{}
//２．Render処理（メソッド）を定義する
void CTriangle::Render()
{
	//３．変数の値を参照する
	glBegin(GL_TRIANGLES);
	glVertex2f(x0, y0);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}
//２．CTriangleクラスの変数（インスタンス）を作成する
//３．この時デフォルトコンストラクタを呼び出す
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
