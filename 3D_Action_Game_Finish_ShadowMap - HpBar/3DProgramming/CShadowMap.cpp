#include "main.h"
#include "CTask.h"
#include "CShadowMap.h"

void CShadowMap::SetLight(const CVector3& pos, const CVector3& center, float fov) {
	mLightPosition = pos;
	mLightCenter = center;
	mFov = fov;
}

void CShadowMap::SetTextureSize(float width, float height) {
	mDepthTextureHeight = height;
	mDepthTextureWidth = width;
}

void CShadowMap::Init(float width, float height) {
	//テクスチャサイズ設定
	SetTextureSize(width, height);
	/* テクスチャユニット１に切り替える */
	glActiveTexture(GL_TEXTURE1);
	/* テクスチャオブジェクトを生成して結合する */
	glGenTextures(1, &mTex);
	glBindTexture(GL_TEXTURE_2D, mTex);

	//デプステクスチャの割り当て
	/* テクスチャの割り当て */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, mDepthTextureWidth, mDepthTextureHeight, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);

	/* テクスチャを拡大・縮小する方法の指定 */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	/* テクスチャの繰り返し方法の指定 */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	/* 書き込むポリゴンのテクスチャ座標値のＲとテクスチャとの比較を行うようにする */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	/* もしＲの値がテクスチャの値以下なら真（つまり日向） */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	/* 比較の結果を輝度値として得る */
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);

	/* テクスチャオブジェクトの結合を解除する */
	glBindTexture(GL_TEXTURE_2D, 0);

	/* フレームバッファオブジェクトを生成して結合する */
	glGenFramebuffersEXT(1, &mFb);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFb);

	/* フレームバッファオブジェクトにデプスバッファ用のテクスチャを結合する */
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,
		GL_TEXTURE_2D, mTex, 0);

	/* カラーバッファが無いので読み書きしない */
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	/* フレームバッファオブジェクトの結合を解除する */
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	/* テクスチャユニット0に切り替える */
	glActiveTexture(GL_TEXTURE0);

}

void CShadowMap::RenderInit() {
	/*
	** 第１ステップ：デプステクスチャの作成
	*/

	/* フレームバッファオブジェクトへのレンダリング開始 */
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFb);

	/* デプスバッファをクリアする */
	glClear(GL_DEPTH_BUFFER_BIT);

	/* 現在のビューポートを保存しておく */
	glGetIntegerv(GL_VIEWPORT, viewport);

	/* ビューポートをテクスチャのサイズに設定する */
	glViewport(0, 0, mDepthTextureWidth, mDepthTextureHeight);

	/* 現在の透視変換行列を保存しておく */
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	/* 透視変換行列を単位行列に設定する */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* テクスチャ変換行列を設定する */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	/* 光源位置を視点としシーンが視野に収まるようモデルビュー変換行列を設定する */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//透視変換行列設定
	gluPerspective(mFov, (GLdouble)mDepthTextureWidth / (GLdouble)mDepthTextureHeight, 1.0, 1000.0);
	//カメラの設定
	//CVector3 vec = CLight::getLight(0)->getPosition();
	//gluLookAt(vec.x, vec.y, vec.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(mLightPosition.x, mLightPosition.y, mLightPosition.z, mLightCenter.x, mLightCenter.y, mLightCenter.z, 0.0, 1.0, 0.0);

	/* 設定した透視変換行列×モデルビュー変換行列を保存しておく */
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

	/* デプスバッファの内容だけを取得するのでフレームバッファには書き込まない */
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	/* したがって陰影付けも不要なのでライティングをオフにする */
	glDisable(GL_LIGHTING);

	/* デプスバッファには背面のポリゴンの奥行きを記録するようにする */
	glCullFace(GL_FRONT);
}

void CShadowMap::RenderBegin() {
	/* フレームバッファオブジェクトへのレンダリング終了 */
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	/**全体の描画**/
	/* 通常の描画の設定に戻す */
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projection);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_LIGHTING);
	glCullFace(GL_BACK);

	/* フレームバッファとデプスバッファをクリアする */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* テクスチャユニット１に切り替える */
	glActiveTexture(GL_TEXTURE1);

	/* テクスチャ変換行列を設定する */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	/* テクスチャ座標の [-1,1] の範囲を [0,1] の範囲に収める */
	glTranslated(0.5, 0.5, 0.5);
	glScaled(0.5, 0.5, 0.5);

	/* テクスチャのモデルビュー変換行列と透視変換行列の積をかける */
	glMultMatrixd(modelview);

	/* モデルビュー変換行列に戻す */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* テクスチャオブジェクトを結合する */
	glBindTexture(GL_TEXTURE_2D, mTex);

	/* テクスチャマッピングを有効にする */
	glEnable(GL_TEXTURE_2D);

	/* テクスチャユニット0に切り替える */
	glActiveTexture(GL_TEXTURE0);
}

void CShadowMap::RenderEnd() {
	/* テクスチャユニット１に切り替える */
	glActiveTexture(GL_TEXTURE1);
	/* テクスチャオブジェクトの結合を解除する */
	glBindTexture(GL_TEXTURE_2D, 0);
	/* テクスチャマッピングを無効にする */
	glDisable(GL_TEXTURE_2D);
	/* テクスチャユニット0に切り替える */
	glActiveTexture(GL_TEXTURE0);
}
