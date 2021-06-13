#include "glew.h"
#include "CSceneShadowMap.h"

#define TEXWIDTH (800)
#define TEXHEIGHT (600)

CSceneShadowMap::~CSceneShadowMap()
{
	delete mpPlayer;
	delete mpGround;
}

void CSceneShadowMap::Init()
{
	mRover.Load("Rover1.obj", "material\\racing_mat\\single_color\\white.mtl");//プレイヤー
	//地面の読み込み
	mPlane.Load("plane.obj", "plane.mtl");

	mpPlayer = new CObj(&mRover, CVector(50.0f, 10.0f, 30.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	mpGround = new CObj(&mPlane, CVector(), CVector(), CVector(70.0f, 1.0f, 70.0f));

	//Shadow Map ************************************

	/* テクスチャユニット１をDepthテクスチャで使用 */
	glActiveTexture(GL_TEXTURE1);
	//テクスチャの生成
	glGenTextures(1, &mDepthTextureID);
	//使用するテクスチャのバインド
	glBindTexture(GL_TEXTURE_2D, mDepthTextureID);

	/* Depthテクスチャの割り当て */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, TEXWIDTH, TEXHEIGHT, 0,
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

	/* テクスチャ座標に視点座標系における物体の座標値を用いる */
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

	/* 生成したテクスチャ座標をそのまま (S, T, R, Q) に使う */
	static const GLdouble genfunc[][4] = {
	  { 1.0, 0.0, 0.0, 0.0 },
	  { 0.0, 1.0, 0.0, 0.0 },
	  { 0.0, 0.0, 1.0, 0.0 },
	  { 0.0, 0.0, 0.0, 1.0 },
	};

	glTexGendv(GL_S, GL_EYE_PLANE, genfunc[0]);
	glTexGendv(GL_T, GL_EYE_PLANE, genfunc[1]);
	glTexGendv(GL_R, GL_EYE_PLANE, genfunc[2]);
	glTexGendv(GL_Q, GL_EYE_PLANE, genfunc[3]);

	//テクスチャの解除
	glBindTexture(GL_TEXTURE_2D, 0);
	//テクスチャユニットを0に戻す
	glActiveTexture(GL_TEXTURE0);

	//************************************ Shadow Map

}

void CSceneShadowMap::Update()
{
	mpPlayer->mRotation.mY++;
	CTaskManager::Get()->Update();
	Camera3D(90.0f, 50.0f, 90.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//Shadow Map ************************************

	GLint	viewport[4]; //ビューポートの保存用
	CMatrix	modelview; //モデルビュー変換行列の保存用
	CMatrix	projection; //透視変換行列の保存用

	/*
	** 第１ステップ：デプステクスチャの作成
	*/

	/* デプスバッファをクリアする */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* 現在のビューポートを保存しておく */
	glGetIntegerv(GL_VIEWPORT, viewport);

	/* ビューポートをテクスチャのサイズに設定する */
	glViewport(0, 0, TEXWIDTH, TEXHEIGHT);

	/* 透視変換行列を設定する */
	glMatrixMode(GL_PROJECTION); //透視変換行列に切り替え
	glPushMatrix(); //現在の設定はスタックに保存
	glLoadIdentity(); //行列の初期化

	/* Depthテクスチャの透視変換行列を保存しておく */
	gluPerspective(75.0, (GLdouble)TEXWIDTH / (GLdouble)TEXHEIGHT, 1.0, 100000.0);
	glGetFloatv(GL_PROJECTION_MATRIX, projection.mM[0]); //透視変換行列の保存

	GLfloat lightpos[] = { 0.0f, 200.0f, 200.0f, 0.0f }; //ライトの位置データ
	/* 光源位置を視点としシーンが視野に収まるようモデルビュー変換行列を設定する */
	glMatrixMode(GL_MODELVIEW); //モデルビュー行列に切り替え
	glPushMatrix(); //現在の設定はスタックに保存
	glLoadIdentity(); //行列の初期化
	//ライト位置から見るように行列を設定する
	gluLookAt(lightpos[0], lightpos[1], lightpos[2], lightpos[0] - 1, 0, lightpos[2] - 1, 0.0, 1.0, 0.0);
	/* 設定したモデルビュー変換行列を保存しておく */
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview.mM[0]);

	/* デプスバッファの内容だけを取得するのでフレームバッファには書き込まない */
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	/* したがって陰影付けも不要なのでライティングをオフにする */
	glDisable(GL_LIGHTING);

	/* デプスバッファには背面のポリゴンの奥行きを記録するようにする */
	glCullFace(GL_FRONT);
	//************************************ Shadow Map

	//Depthテクスチャを作成する描画
	CTaskManager::Get()->Render();

	//Shadow Map ************************************
	/* テクスチャユニット１に切り替える */
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mDepthTextureID);
	/* デプスバッファの内容をテクスチャメモリに転送する */
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, TEXWIDTH, TEXHEIGHT);

	/* 通常の描画の設定に戻す */
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

	glMatrixMode(GL_PROJECTION); //透視変換行列に切り替え
	glPopMatrix(); //設定をスタックから戻す

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_LIGHTING);
	glCullFace(GL_BACK);

	/*
	** 第２ステップ：全体の描画
	*/

	/* フレームバッファとデプスバッファをクリアする */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* モデルビュー変換行列の設定 */
	glMatrixMode(GL_MODELVIEW); //モデルビュー行列に切り替え
	glPopMatrix(); //スタックから元に戻す
	/* モデルビュー変換行列を保存しておく */
	CMatrix modelviewCamera;
	glGetFloatv(GL_MODELVIEW_MATRIX, modelviewCamera.mM[0]);

	/* 光源の位置を設定する */
	//glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	/* テクスチャ変換行列を設定する */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	/* テクスチャ座標の [-1,1] の範囲を [0,1] の範囲に収める */
	glTranslated(0.5, 0.5, 0.5);
	glScaled(0.5, 0.5, 0.5);
	/* テクスチャのモデルビュー変換行列と透視変換行列の積をかける */
	glMultMatrixf(projection.mM[0]);
	glMultMatrixf(modelview.mM[0]);

	/* 現在のモデルビュー変換の逆変換をかけておく */
	glMultMatrixf(modelviewCamera.GetInverse().mM[0]);

	/* モデルビュー変換行列に戻す */
	glMatrixMode(GL_MODELVIEW);

	/* テクスチャマッピングとテクスチャ座標の自動生成を有効にする */
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_GEN_Q);

	const GLfloat lightcol[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	/* 光源の明るさを日向の部分での明るさに設定 */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcol);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightcol);
	//************************************ Shadow Map

	//影の描画
	mpGround->Render();

	//Shadow Map ************************************
	/* テクスチャマッピングとテクスチャ座標の自動生成を無効にする */
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);
	glDisable(GL_TEXTURE_2D);
	//テクスチャを解除する
	glBindTexture(GL_TEXTURE_2D, 0);
	/* テクスチャ変換行列を設定する */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);

	glActiveTexture(GL_TEXTURE0);
	//************************************ Shadow Map

	//全体の描画
	CTaskManager::Get()->Render();
}
