#ifndef CSHADOWMAP_H
#define CSHADOWMAP_H

#include "CVector.h"
#include "glfw/glfw3.h"

class CShadowMap
{
	GLint	mTextureWidth, mTextureHeight; //Depthテクスチャの幅と高さ
	GLuint	mDepthTextureID; //DepthテクスチャのID
	GLint	viewport[4]; //ビューポートの保存用
	CMatrix	modelview; //モデルビュー変換行列の保存用
	CMatrix	projection; //透視変換行列の保存用
public:
	~CShadowMap();
	//Init(Depthテクスチャの幅,Depthテクスチャの高さ)
	void Init(GLuint width, GLuint height);
	//Step1Init(ライトの位置)
	void Step1Init(const CVector &lightPosition);
	//影の描画開始
	void Step2Begin();
	//影の描画終了
	void Step3End();
};

#endif
