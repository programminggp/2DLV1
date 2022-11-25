#ifndef CSHADOWMAP_H
#define CSHADOWMAP_H

#include "CVector.h"
#include "glew.h"

class CShadowMap {
	/*
	** テクスチャオブジェクト・フレームバッファオブジェクト
	*/
	GLuint mTex, mFb;
	GLint viewport[4];       /* ビューポートの保存用　　　　 */
	GLdouble modelview[16];  /* モデルビュー変換行列の保存用 */
	GLdouble projection[16]; /* 透視変換行列の保存用　　　　 */

public:
	CVector mLightPosition;	//光源位置
	CVector mLightCenter;		//光源先
	float mDepthTextureWidth;	//深度テクスチャの幅
	float mDepthTextureHeight;	//深度テクスチャの高さ
	float mFov;					//深度テクスチャ作成時の投影画角
	void SetLight(const CVector& pos, const CVector& center, float fov);
	void SetTextureSize(float width, float height);
	void Init(float width, float height);
	void RenderInit();
	void RenderBegin();
	void RenderEnd();
};

#endif
