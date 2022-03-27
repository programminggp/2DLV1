#include "CTexture.h"
#include <stdio.h>	//ファイルの入力に使用
#include <string.h>
#include "soil.h"
//std::map<std::string, CTexture>CTexture::mTexFile;

CTexture::CTexture()
	: mId(0)
	, mpName(nullptr)
	, mRow(1)
	, mCol(1)
{
}

CTexture::CTexture(char *file)
	: CTexture()
{
	Load(file);
}

CTexture::~CTexture() {
	Destory();
}

void CTexture::Destory() {
	//テクスチャデータがあれば削除する
	if (mId != 0) {
		//テクスチャデータの削除
		glDeleteTextures(1, &mId);
		mId = 0;
	}
	if (mpName) {
		delete[] mpName;
		mpName = nullptr;
	}
}

#include <string>
void CTexture::Load(const char* filename)
{
	//ファイルオープン
	std::string file(filename);
	file = RES_DIR + file;	//ファイル名の退避
	mpName = new char[strlen(filename) + 1];
	strcpy(mpName, filename);
	//画像データ
	unsigned char* data;
	//ファイルの入力
	data = SOIL_load_image(file.data(), &mHeader.width,
		&mHeader.height, &mHeader.depth,
		SOIL_LOAD_AUTO);
	if (!data)
	{
		printf("CTexture::Load Error:%s\n", file.data());
		return;
	}
	//テクスチャの作成
	mId = SOIL_create_OGL_texture(data,
		mHeader.width, mHeader.height, mHeader.depth,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_POWER_OF_TWO
		| SOIL_FLAG_MIPMAPS
		| SOIL_FLAG_MULTIPLY_ALPHA
		| SOIL_FLAG_COMPRESS_TO_DXT
		| SOIL_FLAG_DDS_LOAD_DIRECT
		| SOIL_FLAG_INVERT_Y
		| SOIL_FLAG_TEXTURE_REPEATS
	);
	//データの解放
	SOIL_free_image_data(data);
	mHeader.depth *= 8;
	return;
}

//	//if (mTexFile.count(filename)) {
//	//	*this = mTexFile[filename];
//	//	return;
//	//}
//	//画像データ
//	unsigned char *data, *data2;
//	//ファイルポインタの作成
//	FILE *fp;
//	//ファイルオープン
//	std::string file(filename);
//	file = "res\\" + file;
//	fp = fopen(file.data(), "rb");
//	//エラーのときはリターン
//	if (!fp) {
//		printf("file not found:%s\n", filename);
//		return;
//	}
//	mpName = new char[strlen(filename) + 1];
//	strcpy(mpName, filename);
//	//ヘッダ情報を読み込む
//	fread(&mHeader, sizeof(mHeader), 1, fp);
//	//画像データのバイト数を計算する
//	int length = mHeader.width * mHeader.height * mHeader.depth / 8;
//	//画像データの格納領域を確保
//	data2 = new unsigned char[length];
//	data = new unsigned char[length];
//	//画像データをヘッダの続きから読み込む
//	fread(data2, length, 1, fp);
//	//画像ファイルのクローズ
//	fclose(fp);
//	
//	for (int i = 0; i < mHeader.width * mHeader.height; i++) {
//		int x, y;
////		if (mHeader.discripter >> 4 & 0x01) {
//		if (mHeader.discripter & 0x10) {
//			x = mHeader.width - i % mHeader.width - 1;
//		}
//		else {
//			x = i % mHeader.width;
//		}
////		if (mHeader.discripter >> 5 & 0x01) {
//		if (mHeader.discripter & 0x20) {
//			y = mHeader.height - i / mHeader.width - 1;
//		}
//		else {
//			y = i / mHeader.width;
//		}
//		x = x * mHeader.depth / 8;
//		y = y * mHeader.width * mHeader.depth / 8;
//		for (int j = 0; j < mHeader.depth / 8; j++) {
//			data[x + y + j] = data2[i * mHeader.depth / 8 + j];
//		}
//	}
//
//	//テクスチャデータの作成
//	glGenTextures(1, &mId);
//	//mTexFile[filename] = *this;
//
//	/* テクスチャユニット１に切り替える */
////	glActiveTexture(GL_TEXTURE1);
//
//	glBindTexture(GL_TEXTURE_2D, mId);
//	glTexParameteri(GL_TEXTURE_2D,
//		GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D,
//		GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	if (mHeader.depth == 32)
//		//アルファ有りのテクスチャ作成
//		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, mHeader.width,
//		mHeader.height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
//	else
//		//アルファ無しのテクスチャ作成
//		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, mHeader.width,
//		mHeader.height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	/* テクスチャユニット０に戻す */
////	glActiveTexture(GL_TEXTURE0);
//	//格納領域を解放
//	delete[] data;
//	delete[] data2;
//}

void CTexture::Draw(float left, float right, float bottom, float top, float tleft, float tright, float tbottom, float ttop) {
	DrawImage(left, right, bottom, top, tleft, tright, tbottom, ttop);
}

void CTexture::DrawImage(float left, float right, float bottom, float top, float tleft, float tright, float tbottom, float ttop) const
{
	//テクスチャを有効にする
	glEnable(GL_TEXTURE_2D);
	//アルファブレンドを有効にする
	glEnable(GL_BLEND);
	//ブレンド方法を指定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//テクスチャを指定
	glBindTexture(GL_TEXTURE_2D, mId);

	float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//色の設定
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glColor4fv(diffuse);

	glBegin(GL_TRIANGLES);
	glTexCoord2f(tleft,  ttop);
	glVertex2d(left, top);
	glTexCoord2f(tleft, tbottom);
	glVertex2d(left, bottom);
	glTexCoord2f(tright, tbottom);
	glVertex2d(right, bottom);
	glTexCoord2f(tleft, ttop);
	glVertex2d(left, top);
	glTexCoord2f(tright, tbottom);
	glVertex2d(right, bottom);
	glTexCoord2f(tright, ttop);
	glVertex2d(right, top);
	glEnd();

	//テクスチャを解放
	glBindTexture(GL_TEXTURE_2D, 0);
	//アルファブレンドを無効
	glDisable(GL_BLEND);
	//テクスチャを無効
	glDisable(GL_TEXTURE_2D);
}

void CTexture::Draw(float left, float right, float bottom, float top, int tleft, int tright, int tbottom, int ttop) const
{
	DrawImage(left, right, bottom, top, tleft, tright, tbottom, ttop);
}

void CTexture::DrawImage(float left, float right, float bottom, float top, int tleft, int tright, int tbottom, int ttop) const
{
	DrawImage(left, right, bottom, top,
		(float)tleft / mHeader.width,
		(float)tright / mHeader.width,
		(float)(mHeader.height - tbottom) / mHeader.height,
		(float)(mHeader.height - ttop) / mHeader.height);

	return;
/*
	//テクスチャを有効にする
	glEnable(GL_TEXTURE_2D);
	//アルファブレンドを有効にする
	glEnable(GL_BLEND);
	//ブレンド方法を指定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//テクスチャを指定
	glBindTexture(GL_TEXTURE_2D, mId);

	float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//色の設定
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glColor4fv(diffuse);

	glBegin(GL_TRIANGLES);
	glTexCoord2f(tleft / mHeader.width, (mHeader.height - ttop) / mHeader.height);
	glVertex2d(left, top);
	glTexCoord2f(tleft / mHeader.width, (mHeader.height - tbottom) / mHeader.height);
	glVertex2d(left, bottom);
	glTexCoord2f(tright / mHeader.width, (mHeader.height - tbottom) / mHeader.height);
	glVertex2d(right, bottom);
	glTexCoord2f(tleft / mHeader.width, (mHeader.height - ttop) / mHeader.height);
	glVertex2d(left, top);
	glTexCoord2f(tright / mHeader.width, (mHeader.height - tbottom) / mHeader.height);
	glVertex2d(right, bottom);
	glTexCoord2f(tright / mHeader.width, (mHeader.height - ttop) / mHeader.height);
	glVertex2d(right, top);
	glEnd();

	//テクスチャを解放
	glBindTexture(GL_TEXTURE_2D, 0);
	//アルファブレンドを無効
	glDisable(GL_BLEND);
	//テクスチャを無効
	glDisable(GL_TEXTURE_2D);
*/
}

void CTexture::SetParts(int row, int col) {
	mRow = row;
	mCol = col;
}

void CTexture::DrawImage(float left, float right, float bottom, float top, int index) {
	int row = index / mCol + 1;
	int col = index % mCol;
	DrawImage(left, right, bottom, top,
		mHeader.width * col++ / mCol,
		mHeader.width * col / mCol,
		mHeader.height * row-- / mRow,
		mHeader.height * row / mRow);
}

int CTexture::Row()
{
	return mRow;
}

int CTexture::Col()
{
	return mCol;
}

const STgamHeader& CTexture::Header() const
{
	return mHeader;
}

const GLuint& CTexture::Id() const
{
	return mId;
}

//行数列数の設定
//SetRowCol(行数, 列数)
void CTexture::SetRowCol(int row , int col) {
	mRow = row;
	mCol = col;
}
