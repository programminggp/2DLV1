#include "CRectangle.h"
#include "glut.h"

//描画処理の定義
void CRectangle::Render() {
	//描画開始(四角形)
	glBegin(GL_QUADS);
	//頂点座標の設定
	glVertex2d(mPx - mSx, mPy + mSy);
	glVertex2d(mPx - mSx, mPy - mSy);
	glVertex2d(mPx + mSx, mPy - mSy);
	glVertex2d(mPx + mSx, mPy + mSy);
	//描画終了
	glEnd();
}
