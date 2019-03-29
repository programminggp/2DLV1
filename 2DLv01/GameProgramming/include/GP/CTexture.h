#ifndef CTEXTURE_H
#define CTEXTURE_H
#include "glew.h"
#include "glut.h"
#include <stdio.h>	//ファイルの入力に使用
#include <string.h>
/*
TGAファイルのヘッダフォーマット
*/
struct STgamHeader {
	unsigned char	dummy1[12];
	unsigned short	width;	//幅
	unsigned short	height;	//高さ
	unsigned char	depth;	//ビットの深さ
	unsigned char	dummy2;
};
/*
テクスチャークラス
*/
//#include <map>

class CTexture {
//	static std::map<std::string, CTexture>mTexFile;
	//ファイル名
	char* mpName;
public:
	//TGAファイルのヘッダ情報
	STgamHeader mHeader;
	//テクスチャID
	GLuint mId;
	//
	int mCol;
	int mRow;
	/*
	デフォルトコンストラクタ
	*/
	CTexture();
	CTexture(char *file);
	/*
	デストラクタ（このインスタンスが破棄されるときに実行される）
	*/
	~CTexture();
	/*
	画像ファイルの読み込み（テクスチャファイルの読み込み）
	*/
	void Load(const char* filename);
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
	void DrawImage(float left, float right, float bottom, float top, float tleft, float tright, float tbottom, float ttop);
	void DrawImage(float left, float right, float bottom, float top, int index);
	void Destory();
	void SetParts(int row, int col);
};

#endif
