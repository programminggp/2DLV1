#include "CRectangle.h"
#include "glut.h"

//描画処理の定義
void CRectangle::Render() {
	if (mpTexture) {
		Render(*mpTexture, 0);
	}
	else {
		Render(0);
	}
}

void CRectangle::Render(int index) {
	if (mpTexture) {
		Render(*mpTexture, index);
	}
	else if (mTexture.mId) {
		mTexture.DrawImage(mX - mW, mX + mW, mY - mH, mY + mH, index);
	}
	else {
		//描画開始(四角形)
		glBegin(GL_QUADS);
		//頂点座標の設定
		glVertex2d(mX - mW, mY + mH);
		glVertex2d(mX - mW, mY - mH);
		glVertex2d(mX + mW, mY - mH);
		glVertex2d(mX + mW, mY + mH);
		//描画終了
		glEnd();
	}
}
//コンストラクタの定義
CRectangle::CRectangle()
: mX(0.0f)
, mY(0.0f)
, mW(1.0f)
, mH(1.0f)
, mpTexture(0)
{
}

CRectangle::CRectangle(float x, float y, float w, float h)
	: mX(x)//X座標の代入
	, mY(y)//Y座標の代入
	, mW(w / 2.0f)//幅の代入
	, mH(h / 2.0f)//高さの代入
	, mpTexture(0)
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
//6
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
	mX = posx;
	mY = posy;
	mW = width / 2.0f;
	mH = height / 2.0f;
}

void CRectangle::Set(int posx, int posy, int width, int height) {
	SetXYWH(posx, posy, width, height);
}

void CRectangle::LoadTexture(char* filename) {
	if (mTexture.mId) {
		mTexture.Destory();
	}
	mTexture.Load(filename);
}

void CRectangle::LoadTexture(char* filename, int row, int col) {
	if (mTexture.mId) {
		mTexture.Destory();
	}
	mTexture.Load(filename);
	mTexture.SetParts(row, col);
}

void CRectangle::Render(CTexture& texture) {
	Render(texture, 0);
}

void CRectangle::Render(CTexture& texture, int index) {
	if (texture.mId) {
		texture.DrawImage(mX - mW, mX + mW, mY - mH, mY + mH, index);
	}
	else {
		//描画開始(四角形)
		glBegin(GL_QUADS);
		//頂点座標の設定
		glVertex2d(mX - mW, mY + mH);
		glVertex2d(mX - mW, mY - mH);
		glVertex2d(mX + mW, mY - mH);
		glVertex2d(mX + mW, mY + mH);
		//描画終了
		glEnd();
	}
}

void CRectangle::SetTexture(CTexture *texture) {
	mpTexture = texture;
}

void CRectangle::SetPosition(float x, float y) {
	mX = x;
	mY = y;
}

void CRectangle::SetSize(float sx, float sy) {
	mW = sx / 2.0f;
	mH = sy / 2.0f;
}

void CRectangle::Translate(float x, float y) {
	mX += x;
	mY += y;
}

void CRectangle::Scale(float sx, float sy) {
	mW *= sx;
	mH *= sy;
}
