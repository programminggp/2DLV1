#ifndef CTEXTURE_H
#define CTEXTURE_H
#include "glut.h"
/*
TGAファイルのヘッダフォーマット
*/
struct STgamHeader {
	unsigned char	dummy1[12];
	unsigned short	width;	//幅
	unsigned short	height;	//高さ
	unsigned char	depth;	//ビットの深さ
	unsigned char	discripter;
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
	int mRow;//行数
	int mCol;//列数
	//行数列数の設定
	//SetRowCol(行数, 列数)
	void SetRowCol(int row = 1, int col = 1);

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
	void Load(const char* file);
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
	void DrawImage(float left, float right, float bottom, float top, float tleft, float tright, float tbottom, float ttop) ;
	void DrawImage(float left, float right, float bottom, float top, int tleft, int tright, int tbottom, int ttop);
	void DrawImage(float left, float right, float bottom, float top, int index);
	void Destory();
	void SetParts(int row, int col);
	void Draw(float left, float right, float bottom, float top, float tleft, float tright, float tbottom, float ttop);
	void Draw(float left, float right, float bottom, float top, int tleft, int tright, int tbottom, int ttop);
};

#endif
