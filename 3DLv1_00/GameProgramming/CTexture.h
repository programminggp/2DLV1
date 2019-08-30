#ifndef CTEXTURE_H
#define CTEXTURE_H

#include <stdio.h>	//ファイルの入力に使用
#include "glut.h"
#include <string.h>

/*
TGAファイルのヘッダフォーマット
*/
struct STgaheader {
	unsigned char	dummy1[12];
	unsigned short	width;		//幅
	unsigned short	height;	//高さ
	unsigned char	depth;	//ビットの深さ
	unsigned char	dummy2;
};
/*
テクスチャークラス
*/
class CTexture {
public:
	//テクスチャID
	GLuint mId;
	//TGAファイルのヘッダ情報
	STgaheader mHeader;
	//ファイル名
	char* mpName;
	/*
	デフォルトコンストラクタ
	*/
	CTexture()
		: mId(0)
		, mpName(0) {}
	CTexture(char *file)
		: mId(0)
		, mpName(0) {
		Load(file);
	}
	/*
	デストラクタ（このインスタンスが破棄されるときに実行される）
	*/
	~CTexture() {
		//テクスチャデータがあれば削除する
		if (mId != 0) {
			//テクスチャデータの削除
			glDeleteTextures(1, &mId);
			mId = 0;
		}
		if (mpName) {
			delete[] mpName;
			mpName = 0;
		}
	}

	/*
	画像ファイルの読み込み（テクスチャファイルの読み込み）
	*/
	void Load(const char* filename) {
		//テクスチャデータがあれば削除する
		if (mId) {
			//テクスチャデータの削除
			glDeleteTextures(1, &mId);
			mId = 0;
		}
		if (mpName) {
			delete[] mpName;
			mpName = 0;
		}
		//画像データ
		unsigned char* data;
		//ファイルポインタの作成
		FILE *fp;
		//ファイルオープン
		fp = fopen(filename, "rb");
		//エラーのときはリターン
		if (!fp) {
			printf("file not found:%s\n", filename);
			return;
		}
		mpName = new char[strlen(filename) + 1];
		strcpy(mpName, filename);
		//ヘッダ情報を読み込む
		fread(&mHeader, sizeof(mHeader), 1, fp);
		//画像データのバイト数を計算する
		int length = mHeader.width * mHeader.height * mHeader.depth / 8;
		//画像データの格納領域を確保
		data = new unsigned char[length];
		//画像データをヘッダの続きから読み込む
		fread(data, length, 1, fp);
		//画像ファイルのクローズ
		fclose(fp);

		//テクスチャデータの作成
		glGenTextures(1, &mId);
		glBindTexture(GL_TEXTURE_2D, mId);
		glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		if (mHeader.depth == 32)
			//アルファ有りのテクスチャ作成
			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, mHeader.width,
			mHeader.height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
		else
			//アルファ無しのテクスチャ作成
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, mHeader.width,
			mHeader.height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, 0);
		//格納領域を解放
		delete[] data;
	}
	/*
	DrawImage
	left:四角形左座標
	right:四角形右座標
	bottom:四角形下座標
	top:四角形上座標
	tleft:画像左座標
	tright:画像右座標
	tbottom:画像下座標
	ttop:画像上座標
	*/
	void DrawImage(int left, int right, int bottom, int top, float tleft, float tright, float tbottom, float ttop)  const {
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
	}

};

#endif
