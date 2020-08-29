#include "CMaterial.h"
//memsetのインクルード
#include <string.h>
#include <assert.h>
#include "glut.h"

//デフォルトコンストラクタ
CMaterial::CMaterial()
: mpTexture(0), mVertexNum(0)
{
	//名前を0で埋め
	memset(mName, 0, sizeof(mName));
	//0で埋める
//	memset(mDiffuse, 0, sizeof(mDiffuse));
	mDiffuse[0] = mDiffuse[1] = mDiffuse[2] = mDiffuse[3] = 1.0f;
}
//マテリアルを有効にする
void CMaterial::Enabled() {
	//アルファブレンドを有効にする
	glEnable(GL_BLEND);
	//ブレンド方法を指定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//拡散光の設定
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	//テクスチャが無い時、戻る
	if (mpTexture == 0)
		return;
	//テクスチャ有り
	if (mpTexture->mId) {
		//テクスチャを使用可能にする
		glEnable(GL_TEXTURE_2D);
		//テクスチャをバインドする
		glBindTexture(GL_TEXTURE_2D, mpTexture->mId);
	}
}
//マテリアルを無効にする
void CMaterial::Disabled() {
	//アルファブレンドを無効
	glDisable(GL_BLEND);
	//テクスチャが無い時、戻る
	if (mpTexture == 0)
		return;
	//テクスチャ有り
	if (mpTexture->mId) {
		//テクスチャのバインドを解く
		glBindTexture(GL_TEXTURE_2D, 0);
		//テクスチャを無効にする
		glDisable(GL_TEXTURE_2D);
	}
}

CMaterial::~CMaterial()
{
	if (mpTexture)
	{
		delete mpTexture;
		mpTexture = 0;
	}
}

void CMaterial::SetTexture(char *file)
{
	assert(mpTexture == 0);
	if (!mpTexture)
	{
		mpTexture = new CTexture();
		mpTexture->Load(file);
	}
}
