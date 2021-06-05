#include "CTriangle.h"
//#include "../Camera/CCamera.h"
//#include "../Convenient/CConvenient.h"
#include <cassert>


/*コンストラクタ*/
CTriangle::CTriangle()
: mpTexture(0), r(1.0f), g(1.0f), b(1.0f), a(1.0f), mEnabled(false),mFlagSaveTex(false){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			mUv[i][j] = 0.0f;
		}
	}
}



//カラーを設定
void CTriangle::SetDiffuse(float cr, float cg, float cb, float ca){
	r = cr;
	g = cg;
	b = cb;
	a = ca;
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
}

/*法線設定*/
void CTriangle::SetNormal(float x, float y, float z){
	mNormal.x = x;
	mNormal.y = y;
	mNormal.z = z;
}

/*
SetUv
left	画像の左上端を原点(0,0)とし、貼り付けたい領域の左の座標値
top		画像の左上端を原点(0,0)とし、貼り付けたい領域の上の座標値
right	画像の左上端を原点(0,0)とし、貼り付けたい領域の右の座標値
bottom	画像の左上端を原点(0,0)とし、貼り付けたい領域の下の座標値
*/
void CTriangle::SetUv(CTexture *t, int left, int top, int right, int bottom) {
	mpTexture = t;
	mUv[0][0] = (float)left / mpTexture->header.width;
	mUv[0][1] = (float)(mpTexture->header.height - top) / mpTexture->header.height;
	mUv[1][0] = (float)left / mpTexture->header.width;
	mUv[1][1] = (float)(mpTexture->header.height - bottom) / mpTexture->header.height;
	mUv[2][0] = (float)right / mpTexture->header.width;
	mUv[2][1] = (float)(mpTexture->header.height - bottom) / mpTexture->header.height;
	mUv[3][0] = (float)right / mpTexture->header.width;
	mUv[3][1] = (float)(mpTexture->header.height - top) / mpTexture->header.height;

	/*テクスチャの値保存*/
	if (!mFlagSaveTex){
		mSaveInitTexVer[E_TOP] = top;
		mSaveInitTexVer[E_BOTTOM] = bottom;
		mSaveInitTexVer[E_LEFT] = left;
		mSaveInitTexVer[E_RIGHT] = right;
		mFlagSaveTex = true;
	}
	mSaveTexVer[E_TOP] = top;
	mSaveTexVer[E_BOTTOM] = bottom;
	mSaveTexVer[E_LEFT] = left;
	mSaveTexVer[E_RIGHT] = right;
}
/*回転させるよう*/
void CTriangle::SetUvRot() {

	float saveUv0[2] = { mUv[0][0], mUv[0][1] };
	mUv[0][0] = mUv[3][0];
	mUv[0][1] = mUv[3][1];

	float saveUv2[2] = { mUv[2][2], mUv[2][1] };
	mUv[2][0] = mUv[1][0];
	mUv[2][1] = mUv[1][1];

	mUv[1][0] = saveUv0[0];
	mUv[1][1] = saveUv0[1];

	mUv[3][0] = saveUv2[0];
	mUv[3][1] = saveUv2[1];
}
/*
SetVertex
v0～v3：頂点１～４までの座標
*/
void CTriangle::SetVertex(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2) {
	mEnabled = true;//設定された
	mVertex[E_LEFT_TOP] = v0;
	mVertex[E_LEFT_BOTTOM] = v1;
	mVertex[E_RIGHT_BOTTOM] = v2;
}



//描画する
void CTriangle::Render() {
	if (mpTexture == 0) {
		////描画色を設定
		glColor4f(r, g, b, a);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glNormal3f(mNormal.x, mNormal.y, mNormal.z);
		//三角形の描画
		glBegin(GL_TRIANGLES);	//三角形の頂点指定開始
		glVertex3f(mVertex[0].x, mVertex[0].y, mVertex[0].z);	//頂点の指定
		glVertex3f(mVertex[1].x, mVertex[1].y, mVertex[1].z);	//頂点の指定
		glVertex3f(mVertex[2].x, mVertex[2].y, mVertex[2].z);	//頂点の指定

		glEnd();	//頂点指定終了

	}
	else {
		//テクスチャを有効にする
		glEnable(GL_TEXTURE_2D);
		//アルファブレンドを有効にする
		glEnable(GL_BLEND);
		//ブレンド方法を指定
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//テクスチャを指定
		glBindTexture(GL_TEXTURE_2D, mpTexture->id);


		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glNormal3f(mNormal.x, mNormal.y, mNormal.z);

		glBegin(GL_TRIANGLES);	//三角形の頂点指定開始

		glTexCoord2fv(mUv[0]);	//頂点のテクスチャマッピング
		glVertex3f(mVertex[0].x, mVertex[0].y, mVertex[0].z);	//頂点の指定
		glTexCoord2fv(mUv[1]);	//頂点のテクスチャマッピング
		glVertex3f(mVertex[1].x, mVertex[1].y, mVertex[1].z);	//頂点の指定
		glTexCoord2fv(mUv[2]);	//頂点のテクスチャマッピング
		glVertex3f(mVertex[2].x, mVertex[2].y, mVertex[2].z);	//頂点の指定

		glEnd();	//頂点指定終了

		//テクスチャを解放
		glBindTexture(GL_TEXTURE_2D, 0);
		//アルファブレンドを無効
		glDisable(GL_BLEND);
		//テクスチャを無効
		glDisable(GL_TEXTURE_2D);
	}
}


/*フェード関数*/
#define SET_C3 r,g,b //元の四角形rgb


void CTriangle::Fade(float speed, float alaha){
	float mFade4 = a + speed;		//フェード関数で使う
	mFade4 += speed;
	if (mFade4 >= alaha){
		mFade4 = alaha;
	}
	SetDiffuse(SET_C3, mFade4);
}

/*フェード関数*/
void CTriangle::FadeOut(float speed, float alaha){
	float mFade4 = a - speed;		//フェード関数で使う
	mFade4 -= speed;
	if (mFade4 <= alaha){
		mFade4 = alaha;
	}
	SetDiffuse(SET_C3, mFade4);
}


/*テクスチャ横スクロール関数*/
void CTriangle::TexSideScroll(float speed){
	float left, top, right, bottom;
	/*保存*/
	left = mSaveTexVer[E_LEFT];
	top = mSaveTexVer[E_TOP];
	right = mSaveTexVer[E_RIGHT];
	bottom = mSaveTexVer[E_BOTTOM];
	/*計算*/
	//CConvenient::LoopPlus(&left, speed, mSaveInitTexVer[E_RIGHT], mSaveInitTexVer[E_LEFT]);
	//CConvenient::LoopPlus(&right, speed, mSaveInitTexVer[E_RIGHT], mSaveInitTexVer[E_LEFT]);
	SetUv(mpTexture, left, top, right, bottom);
		
}


/*テクスチャ縦スクロール関数*/
void CTriangle::TexVerticalScroll(float speed){
	float left, top, right, bottom;
	/*保存*/
	left = mSaveTexVer[E_LEFT];
	top = mSaveTexVer[E_TOP];
	right = mSaveTexVer[E_RIGHT];
	bottom = mSaveTexVer[E_BOTTOM];
	/*計算*/
	//CConvenient::LoopPlus(&top, speed, mSaveInitTexVer[E_TOP], mSaveInitTexVer[E_BOTTOM]);
	//CConvenient::LoopPlus(&bottom, speed, mSaveInitTexVer[E_TOP], mSaveInitTexVer[E_BOTTOM]);
	SetUv(mpTexture, left, top, right, bottom);

}