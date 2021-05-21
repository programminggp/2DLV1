#ifndef CRENDERTEXTURE_H
#define CRENDERTEXTURE_H
#include "glfw/glfw3.h"

//レンダーテクスチャクラス
class CRenderTexture
{
private:
	GLuint mColorBuffer;	//カラーバッファ
	GLuint mRenderBuffer;	//レンダーバッファ
	GLuint mFrameBuffer;	//フレームバッファ
public:
	//コンストラクタ
	CRenderTexture();
	//初期設定処理
	void Init();
	//レンダリング開始
	void Start();
	//レンダリング終了
	void End();
	//テクスチャの取得
	GLuint GetColorBuffer();
};

#endif
