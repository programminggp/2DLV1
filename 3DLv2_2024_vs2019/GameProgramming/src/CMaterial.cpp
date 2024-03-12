#include "CMaterial.h"
//memset,strncpyのインクルード
#include <string.h>
#include "glut.h"
/*
* strncpy(char* str1, const char* str2, int len)
* コピー先str1にコピー元str2の文字をlen文字数までコピーする
*/
char* strncpy(char* str1, const char* str2, int len)
{
	int i = 0;
	//iがlenより小さく、かつ、コピー元が終わりでない間繰り返し
	while (i < len && *str2 != '\0')
	{
		*(str1 + i) = *str2; //コピー先にコピー元を代入
		str2++; //コピー元を次へ
		i++;
	}
	str1[i] = '\0'; //コピー先の文字列に終わり
	return str1; //コピー先の先頭アドレスを返却
}

/*
Materialデータの読み込みと設定
*/
CMaterial::CMaterial(CModelX* model)
	: mpTextureFilename(nullptr)
{
	//CModelXにマテリアルを追加する
	model->Material().push_back(this);

	model->GetToken(); // { ? Name
	if (strcmp(model->Token(), "{") != 0) {
		//{でないときはマテリアル名
		strcpy(mName, model->Token());
		model->GetToken(); // {
	}

	mDiffuse[0] = atof(model->GetToken());
	mDiffuse[1] = atof(model->GetToken());
	mDiffuse[2] = atof(model->GetToken());
	mDiffuse[3] = atof(model->GetToken());

	mPower = atof(model->GetToken());

	mSpecular[0] = atof(model->GetToken());
	mSpecular[1] = atof(model->GetToken());
	mSpecular[2] = atof(model->GetToken());

	mEmissive[0] = atof(model->GetToken());
	mEmissive[1] = atof(model->GetToken());
	mEmissive[2] = atof(model->GetToken());

	model->GetToken(); // TextureFilename or }

	if (strcmp(model->Token(), "TextureFilename") == 0) {
		//テクスチャありの場合、テクスチャファイル名取得
		model->GetToken(); // {
		model->GetToken(); // filename
		mpTextureFilename =
			new char[strlen(model->Token()) + 1];
		strcpy(mpTextureFilename, model->Token());
		model->GetToken(); // }
		model->GetToken(); // }
	}
}


CMaterial::~CMaterial()
{
	if (mpTextureFilename) {
		delete[] mpTextureFilename;
	}
	mpTextureFilename = nullptr;
}

CTexture* CMaterial::Texture()
{
	return &mTexture;
}

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

//デフォルトコンストラクタ
CMaterial::CMaterial()
	:mVertexNum(0)
	, mpTextureFilename(nullptr)
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
//マテリアルの名前の取得
char* CMaterial::Name()
{
	return mName;
}
// マテリアルの名前を設定する
// Name(マテリアルの名前)
void CMaterial::Name(char* name)
{
	strncpy(mName, name, MATERIAL_NAME_LEN);
}
//mDiffuse配列の取得
float* CMaterial::Diffuse()
{
	return mDiffuse;
}

void CMaterial::VertexNum(int num)
{
	mVertexNum = num;
}

int CMaterial::VertexNum()
{
	return mVertexNum;
}
