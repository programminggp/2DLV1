#pragma once
#include "glut.h"

class CShadowMap
{
	GLfloat mLightPos[3]; //光源の位置
	GLfloat mShadowCol[4]; //影の色
	int mTextureWidth; //デプステクスチャの幅
	int mTextureHeight; //デプステクスチャの高さ
	GLuint mDepthTextureID; //デプステクスチャID
	GLuint mFb; //フレームバッファ識別子
	void (*mpRender)(); //Render関数のポインタ
public:
	CShadowMap();
	~CShadowMap();
	//初期化処理
	void Init();
	/* 初期化処理
	void Init(int width, int height, void (*funcRender)(), float shadowCol[], float lightPos[])
	width:デプステクスチャの幅
	height:デプステクスチャの高さ
	funcRender:描画関数のポインタ
	shadowCol:影の色
	lightPos:光源の位置
	*/
	void Init(int width, int height, void (*funcRender)(), float shadowCol[], float lightPos[]);
	//描画処理
	void Render();
};
