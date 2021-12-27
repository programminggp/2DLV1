#include "CMaterial.h"
//memsetのインクルード
#include <string.h>
#include "glut.h"

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

CTexture* CMaterial::Texture()
{
	return &mTexture;
}

//デフォルトコンストラクタ
CMaterial::CMaterial()
:mVertexNum(0)
,mpTextureFilename(nullptr)
, mPower(0.0f)
{
	//名前を0で埋め
	memset(mName, 0, sizeof(mName));
	//0で埋める
	memset(mDiffuse, 0, sizeof(mDiffuse));
	memset(mSpecular, 0, sizeof(mSpecular));
	memset(mEmissive, 0, sizeof(mEmissive));
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
float CMaterial::Power()
{
	return mPower;
}
float* CMaterial::Specular()
{
	return mSpecular;
}
float* CMaterial::Emissive()
{
	return mEmissive;
}
/*
Materialデータの読み込みと設定
*/
CMaterial::CMaterial(CModelX* model)
	: CMaterial()
{
	//CModelXにマテリアルを追加する
	model->Materials().push_back(this);

	model->GetToken(); // { ? Name
	if (strcmp(model->Token(), "{") != 0) {
		//{でないときはマテリアル名
		strcpy(mName, model->Token());
		model->GetToken(); // {
	}

	mDiffuse[0] = model->GetFloatToken();
	mDiffuse[1] = model->GetFloatToken();
	mDiffuse[2] = model->GetFloatToken();
	mDiffuse[3] = model->GetFloatToken();

	mPower = model->GetFloatToken();
	mSpecular[0] = model->GetFloatToken();
	mSpecular[1] = model->GetFloatToken();
	mSpecular[2] = model->GetFloatToken();

	mEmissive[0] = model->GetFloatToken();
	mEmissive[1] = model->GetFloatToken();
	mEmissive[2] = model->GetFloatToken();

	model->GetToken(); // TextureFilename or }

	if (strcmp(model->Token(), "TextureFilename") == 0) {
		//テクスチャありの場合、テクスチャファイル名取得
		model->GetToken(); // {
		model->GetToken(); // filename
		mpTextureFilename = new char[strlen(model->Token()) + 1];
		strcpy(mpTextureFilename, model->Token());
		//テクスチャファイルの読み込み
		mTexture.Load(mpTextureFilename);
		model->GetToken(); // }
		model->GetToken(); // }
	}

	//#ifdef _DEBUG
	//	printf("%s\n", mName);
	//	printf("Diffuse:%f %f %f %f\n", mDiffuse[0], mDiffuse[1], mDiffuse[2], mDiffuse[3]);
	//	printf("Power:%f\n", mPower);
	//	printf("Specular:%f %f %f\n", mSpecular[0], mSpecular[1], mSpecular[2]);
	//	printf("Emissive:%f %f %f\n", mEmissive[0], mEmissive[1], mEmissive[2]);
	//#endif
}

CMaterial::~CMaterial() {
	if (mpTextureFilename) {
		delete[] mpTextureFilename;
	}
	mpTextureFilename = nullptr;
}