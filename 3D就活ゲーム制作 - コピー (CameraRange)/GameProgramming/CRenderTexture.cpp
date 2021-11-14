#include "glew.h"
#include "CRenderTexture.h"
#define FBOWIDTH 512	//フレームバッファの幅
#define FBOHEIGHT 512	//フレームバッファの高さ
CRenderTexture::CRenderTexture()
: mColorBuffer(0)
, mRenderBuffer(0)
, mFrameBuffer(0)
{}
void CRenderTexture::Init()
{
	// カラーバッファ用のテクスチャを用意する
	glGenTextures(1, &mColorBuffer);
	glBindTexture(GL_TEXTURE_2D, mColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FBOWIDTH, FBOHEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// デプスバッファ用のレンダーバッファを用意する
	glGenRenderbuffers(1, &mRenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, mRenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, FBOWIDTH, FBOHEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// フレームバッファオブジェクトを作成する
	glGenFramebuffers(1, &mFrameBuffer);
}

void CRenderTexture::Start()
{
	//フレームバッファのバインド
	glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);
	// フレームバッファオブジェクトにカラーバッファとしてテクスチャを結合する
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorBuffer, 0);
	// フレームバッファオブジェクトにデプスバッファとしてレンダーバッファを結合する
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRenderBuffer);
	//各バッファーをクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CRenderTexture::End()
{
	// フレームバッファオブジェクトの結合を解除する
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//テクスチャを返す
GLuint CRenderTexture::GetTexture()
{
	return mColorBuffer;
}
