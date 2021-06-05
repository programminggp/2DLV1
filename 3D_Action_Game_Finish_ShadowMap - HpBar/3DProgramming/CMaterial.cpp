#include "CMaterial.h"

#include "string.h"

/*
Materialデータの読み込みと設定
*/
CMaterial::CMaterial()
: mpName(0)
, mpTextureFilename(0)
, mTextureId(0)
{
	memset(this, 0, sizeof(CMaterial));
}

/*
SetMaterial
マテリアルを適用する
*/
void CMaterial::SetMaterial() {
	glMaterialfv(GL_FRONT, GL_EMISSION, mEmissive);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &mPower);
	//テクスチャが有る場合
	if (mTextureId > 0) {
		//テクスチャを使用可能にする
		glEnable(GL_TEXTURE_2D);
		/* テクスチャユニット0に切り替える */
//		glActiveTexture(GL_TEXTURE0);
		//テクスチャをバインドする
		glBindTexture(GL_TEXTURE_2D, mTextureId);
		//テクスチャマッピングのデータを有効にする
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}
/*
UnSetMaterial
テクスチャマッピングを無効にする
*/
void CMaterial::UnSetMaterial() {
	//テクスチャが有る時
	if (mTextureId > 0) {
		/* テクスチャユニット0に切り替える */
//		glActiveTexture(GL_TEXTURE0);
		//テクスチャのバインドを解く
		glBindTexture(GL_TEXTURE_2D, 0);
		//テクスチャを無効にする
//		glDisable(GL_TEXTURE_2D);
		//テクスチャマッピングのデータを無効にする
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}
