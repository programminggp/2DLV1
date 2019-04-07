#include "CRectangle.h"
#include "glut.h"

//描画処理の定義
void CRectangle::Render() {
	//描画開始(四角形)
	glBegin(GL_QUADS);
	//頂点座標の設定
	glVertex2d(300, 300);
	glVertex2d(300, 200);
	glVertex2d(400, 200);
	glVertex2d(400, 300);
	//描画終了
	glEnd();
}
