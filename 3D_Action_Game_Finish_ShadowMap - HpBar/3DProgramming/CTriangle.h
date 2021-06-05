#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "CVector3.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CTask.h"

class CTriangle : public CTask {
private: 
	enum  E_TEXVER
	{
		E_TOP,
		E_BOTTOM,
		E_LEFT,
		E_RIGHT,
		E_TEX_ARRAY
	};
	float mSaveInitTexVer[E_TEX_ARRAY];//テクスチャのサイズ保存 初めの値
	float mSaveTexVer[E_TEX_ARRAY];//テクスチャのサイズ保存 現在の値
	bool mFlagSaveTex;//テクスチャがセーブされたか判断
public:
	/*頂点数*/
	enum E_VER{
		E_LEFT_TOP,//左上
		E_LEFT_BOTTOM,//左下
		E_RIGHT_BOTTOM,//右下
		E_VER_ARRAY,//配列数
	};

	CVector3 mVertex[E_VER_ARRAY];	//頂点の座標　3頂点分
	CVector3 mNormal;		//面の法線
	CTexture *mpTexture;	//テクスチャ
	bool mEnabled;			//四角形が設定されているかのフラグ
	float mUv[4][2];		//テクスチャマッピング
	float r,g,b,a;			//色データ
	float diffuse[4];


	//頂点データの設定
	void SetVertex(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2);

	//カラーを設定
	void SetDiffuse(float cr, float cg, float cb, float ca);

	/*法線設定*/
	void SetNormal(float x, float y, float z);
	

	//テクスチャとテクスチャマッピングの設定
	void SetUv(CTexture *texture, int left, int top, int right, int bottom);
	//ローテーションさせる
	void SetUvRot();

	CTriangle();

	/*描画処理*/
	void Render();	

	/*
	フェード関数 speed = フェードの速さ
	a = ALPHA
	*/
	void Fade(float speed, float alaha);
	/*
	フェード関数 speed = フェードの速さ
	a = ALPHA
	*/
	void FadeOut(float speed, float alaha);


	/*テクスチャ横スクロール関数*/
	void TexSideScroll(float speed);
	/*テクスチャ縦スクロール関数*/
	void TexVerticalScroll(float speed);
};

#endif
