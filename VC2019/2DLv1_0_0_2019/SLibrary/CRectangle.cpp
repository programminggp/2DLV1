#include "CRectangle.h"
#include "glut.h"

//描画処理の定義
void CRectangle::Render() {
	glPushMatrix();
	glTranslatef(mX, mY, 0.0f);
	glRotatef(mR, 0.0f, 0.0f, 1.0f);
	//描画開始(四角形)
	glBegin(GL_QUADS);
	//頂点座標の設定
	glVertex2d(-mW, mH);
	glVertex2d(-mW, -mH);
	glVertex2d(mW, -mH);
	glVertex2d(mW, mH);
	//描画終了
	glEnd();
	glPopMatrix();
}

void CRectangle::Render(CTexture* pTexture, float left, float right, float bottom, float top) {
	glPushMatrix();
	glTranslatef(mX, mY, 0.0f);
	glRotatef(mR, 0.0f, 0.0f, 1.0f);
	//描画開始(四角形)

	//テクスチャを有効にする
	glEnable(GL_TEXTURE_2D);
	//アルファブレンドを有効にする
	glEnable(GL_BLEND);
	//ブレンド方法を指定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//テクスチャを指定
	glBindTexture(GL_TEXTURE_2D, pTexture->mId);

	float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//色の設定
	glColor4fv(diffuse);

	glBegin(GL_QUADS);
	glTexCoord2f(left / pTexture->mHeader.width, (pTexture->mHeader.height - top) / pTexture->mHeader.height);
	glVertex2d(-mW, mH);
	glTexCoord2f(left / pTexture->mHeader.width, (pTexture->mHeader.height - bottom) / pTexture->mHeader.height);
	glVertex2d(-mW, -mH);
	glTexCoord2f(right / pTexture->mHeader.width, (pTexture->mHeader.height - bottom) / pTexture->mHeader.height);
	glVertex2d(mW, -mH);
	glTexCoord2f(right / pTexture->mHeader.width, (pTexture->mHeader.height - top) / pTexture->mHeader.height);
	glVertex2d(mW, mH);
	glEnd();

	//テクスチャを解放
	glBindTexture(GL_TEXTURE_2D, 0);
	//アルファブレンドを無効
	glDisable(GL_BLEND);
	//テクスチャを無効
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

//コンストラクタの定義
CRectangle::CRectangle()
: mX(0.0f)
, mY(0.0f)
, mW(1.0f)
, mH(1.0f)
, mR(0.0f)
{
}

CRectangle::CRectangle(float x, float y, float w, float h)
	: mX(x)//X座標の代入
	, mY(y)//Y座標の代入
	, mW(w)//幅の代入
	, mH(h)//高さの代入
	, mR(0.0f)
{
}

//中心座標(0,0)で幅と高さを指定するコンストラクタ
CRectangle::CRectangle(float w, float h)
	: CRectangle(0, 0, w, h)//他のコンストラクタの呼び出し
{}//他に処理なし

/*
CollisionYメソッド
自分と四角形rがY軸で重なっているか判定する。
重なっている場合、重ならない位置までの移動量を戻す。
重なっていない場合、0を戻す。
*/
float CRectangle::CollisionY(const CRectangle &r) const {
	//df:四角形と四角形の中心のY軸方向の距離を求める
	float df;
	//mYがrのmYより大きいか判定する
	if (mY > r.mY) {
		//大きい値から小さい値を引いて距離を求める
		df = mY - r.mY;
	}
	else {
		//rのmYの方が大きい場合
		df = r.mY - mY;
	}
	//距離が四角形の高さの合計より小さければ衝突している
	df = mH + r.mH - df;
	if (df > 0) {
		//衝突しない位置まで戻す
		//上にあるか
		if (mY > r.mY) {
			//上に移動
			return df;
		}
		else {
			//下に移動
			return -df;
		}
	}
	//衝突していない
	return 0;
}

/*
CollisionXメソッド
自分と四角形rがX軸で重なっているか判定する。
重なっている場合、重ならない位置までの移動量を戻す。
重なっていない場合、0を戻す。
*/
float CRectangle::CollisionX(const CRectangle &r) const {
	//df:四角形と四角形の中心のX軸方向の距離を求める
	float df;
	//mXがrのmCより大きいか判定する
	if (mX > r.mX) {
		//大きい値から小さい値を引いて距離を求める
		df = mX - r.mX;
	}
	else {
		//rのmXの方が大きい場合
		df = r.mX - mX;
	}
	//距離が四角形の幅の合計より小さければ衝突している
	df = mW + r.mW - df;
	if (df > 0) {
		//衝突しない位置まで戻す
		//右にあるか
		if (mX > r.mX) {
			//右に移動
			return df;
		}
		else {
			//左に移動
			return -df;
		}
	}
	//衝突していない
	return 0;
}
//7
//四角形の衝突処理
//void CRectangle::Collision(CRectangle &r, float &mx, float &my) {
//	//四角形衝突時の移動量を求める
//	float x = CollisionX(r);
//	float y = CollisionY(r);
//	//移動量の絶対値を求める
//	float absx = x, absy = y;
//	if (x < 0) absx = -x;
//	if (y < 0) absy = -y;
//	//絶対値の小さい方向に移動量を加算する
//	if (absx < absy) {
//		mx += x;
//	}
//	else {
//		my += y;
//	}
//}

//bool CRectangle::Collision(CRectangle &r) {
//	//四角形衝突時の移動量を求める
//	float x = CollisionX(r);
//	float y = CollisionY(r);
//	if (x * y == 0.0f) return false;
//	return true;
//}


void CRectangle::SetXYWH(int posx, int posy, int width, int height) {
	Set(posx, posy, width, height);
}

void CRectangle::Set(int posx, int posy, int width, int height) {
	mX = posx;
	mY = posy;
	mW = width;
	mH = height;
}

//
void CRectangle::SetPosition(float x, float y) {
	mX = x;
	mY = y;
}

void CRectangle::SetSize(float sx, float sy) {
	mW = sx;
	mH = sy;
}

void CRectangle::Translate(float x, float y) {
	mX += x;
	mY += y;
}

void CRectangle::Scale(float sx, float sy) {
	mW *= sx;
	mH *= sy;
}

void CRectangle::Render(float x, float y, float w, float h, CTexture *pTexture, float left, float right, float bottom, float top) {
	glPushMatrix();
	glTranslatef(x, y, 0.0f);

	//テクスチャを有効にする
	glEnable(GL_TEXTURE_2D);
	//アルファブレンドを有効にする
	glEnable(GL_BLEND);
	//ブレンド方法を指定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//テクスチャを指定
	glBindTexture(GL_TEXTURE_2D, pTexture->mId);

	float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//色の設定
	glColor4fv(diffuse);

	//描画開始(四角形)
	glBegin(GL_QUADS);
	glTexCoord2f(left / pTexture->mHeader.width, (pTexture->mHeader.height - top) / pTexture->mHeader.height);
	glVertex2d(-w, h);
	glTexCoord2f(left / pTexture->mHeader.width, (pTexture->mHeader.height - bottom) / pTexture->mHeader.height);
	glVertex2d(-w, -h);
	glTexCoord2f(right / pTexture->mHeader.width, (pTexture->mHeader.height - bottom) / pTexture->mHeader.height);
	glVertex2d(w, -h);
	glTexCoord2f(right / pTexture->mHeader.width, (pTexture->mHeader.height - top) / pTexture->mHeader.height);
	glVertex2d(w, h);
	glEnd();

	//テクスチャを解放
	glBindTexture(GL_TEXTURE_2D, 0);
	//アルファブレンドを無効
	glDisable(GL_BLEND);
	//テクスチャを無効
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void CRectangle::Render(float x, float y, float w, float h) {
	glPushMatrix();
	glTranslatef(x, y, 0.0f);

	float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//色の設定
	glColor4fv(diffuse);

	//描画開始(四角形)
	glBegin(GL_QUADS);
	glVertex2d(-w, h);
	glVertex2d(-w, -h);
	glVertex2d(w, -h);
	glVertex2d(w, h);
	glEnd();

	glPopMatrix();
}
