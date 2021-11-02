#include "glut.h"

/*２．
* 四角形のプログラム
* CRectangleプログラム（クラス）を定義する
*/
class CRectangle
{
public:
	//３．デフォルトコンストラクタを宣言する
	CRectangle();
	//４．引数コンストラクタを宣言する
	CRectangle(float left, float right, float bottom, float top);
	//２．Render処理（メソッド）を宣言する
	void Render();
//３．privateアクセス権限
private:
	//３．変数を宣言する
	float left, right, bottom, top;
//	float mX, mY, mW, mH;
};
//３．デフォルトコンストラクタを定義する
CRectangle::CRectangle()
	//３．変数に値を代入する
	: left(-30.0f), right(30.0f), bottom(-30.0f), top(30.0f)
{
}
//４．引数コンストラクタを定義する
CRectangle::CRectangle(float l, float r, float b, float t)
	: left(l), right(r), bottom(b), top(t)
{}
//２．Render処理（メソッド）を定義する
void CRectangle::Render()
{
	//２．四角形の描画
	//glBegin(GL_QUADS);
	//glVertex2f(-30.0f, -30.0f);
	//glVertex2f(30.0f, -30.0f);
	//glVertex2f(30.0f, 30.0f);
	//glVertex2f(-30.0f, 30.0f);
	//glEnd();
	//３．変数の値を参照する
	glBegin(GL_QUADS);
	glVertex2f(left, bottom);
	glVertex2f(right, bottom);
	glVertex2f(right, top);
	glVertex2f(left, top);
	glEnd();
}
//２．CRectangleクラスの変数（インスタンス）を作成する
//３．この時デフォルトコンストラクタを呼び出す
CRectangle Rectangle;
//４．引数コンストラクタを使ったインスタンスの作成
CRectangle Rect(30.0f, 90.0f, 30.0f, 90.0f);

//Init関数
//最初に一度だけ呼ばれる関数
void Init() {
}
//MailLoop関数
//プログラムの実行中、繰り返し呼ばれる関数
void MainLoop() {
	//１．四角形の描画
	//glBegin(GL_QUADS);
	//glVertex2f(-30.0f, -30.0f);
	//glVertex2f(30.0f, -30.0f);
	//glVertex2f(30.0f, 30.0f);
	//glVertex2f(-30.0f, 30.0f);
	//glEnd();
	//２．変数RectangleのRender処理を呼び出す
	Rectangle.Render();
	//４．
	Rect.Render();
}
