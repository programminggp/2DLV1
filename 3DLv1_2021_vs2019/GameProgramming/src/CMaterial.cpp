#include "CMaterial.h"
//memsetのインクルード
#include <string.h>
#include "glut.h"

void CMaterial::Diffuse(float r, float g, float b, float a)
{
	mDiffuse[0] = r;
	mDiffuse[1] = g;
	mDiffuse[2] = b;
	mDiffuse[3] = a;
}

void CMaterial::VertexNum(int num)
{
	mVertexNum = num;
}

int CMaterial::VertexNum()
{
	return mVertexNum;
}

float* CMaterial::Diffuse()
{
	return mDiffuse;
}

//マテリアルの名前の取得
char* CMaterial::Name()
{
	return mName;
}

//マテリアルの名前を設定する
//Name(マテリアルの名前)
void CMaterial::Name(char* name)
{
	strncpy(mName, name, MATERIAL_NAME_LEN - 1);
}

CTexture& CMaterial::Texture()
{
	return mTexture;
}

//デフォルトコンストラクタ
CMaterial::CMaterial()
:mVertexNum(0)
{
	//名前を0で埋め
	memset(mName, 0, sizeof(mName));
	//0で埋める
	memset(mDiffuse, 0, sizeof(mDiffuse));
}

//マテリアルを有効にする
void CMaterial::Enabled() {
	//拡散光の設定
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	//テクスチャ有り
	if (mTexture.Id())
	{
		//テクスチャを使用可能にする
		glEnable(GL_TEXTURE_2D);
		//テクスチャをバインドする
		glBindTexture(GL_TEXTURE_2D, mTexture.Id());
		//アルファブレンドを有効にする
		glEnable(GL_BLEND);
		//ブレンド方法を指定
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}

//テクスチャを読み込む
void CMaterial::LoadTexture(char *file)
{
	mTexture.Load(file);
}
//マテリアルを無効にする
void CMaterial::Disabled()
{
	//テクスチャ有り
	if (mTexture.Id())
	{
		//アルファブレンドを無効
		glDisable(GL_BLEND);
		//テクスチャのバインドを解く
		glBindTexture(GL_TEXTURE_2D, 0);
		//テクスチャを無効にする
		glDisable(GL_TEXTURE_2D);
	}
}
