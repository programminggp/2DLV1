#ifndef CTEXTURE_H
#define CTEXTURE_H
#include "glut.h"

//リソースファイルフォルダ
#define RES_DIR "res\\"

/*
TGAファイルのヘッダフォーマット
*/
struct STgamHeader {
	unsigned char dummy1[12];
	int	width;	//幅
	int	height;	//高さ
	int	depth;	//ビットの深さ
	unsigned char	discripter;
};

/*
テクスチャークラス
*/
//#include <map>

class CTexture {
public:
	int Row();
	int Col();
	const STgamHeader& Header() const;
	const GLuint& Id() const;
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
	Load(ファイル名)
	画像ファイルの読み込み（テクスチャファイルの読み込み）
	*/
	void Load(const char* file);
	/*
	DrawImage(四角形左座標, 四角形右座標, 四角形下座標, 四角形上座標,
	    画像左座標, 画像右座標, 画像下座標, 画像上座標)
	画像の描画
	*/
	void DrawImage(float left, float right, float bottom, float top, int tleft, int tright, int tbottom, int ttop) const;
	void DrawImage(float left, float right, float bottom, float top, float tleft, float tright, float tbottom, float ttop) const;
	void DrawImage(float left, float right, float bottom, float top, int index);
	void Destory();
	void SetParts(int row, int col);
	void Draw(float left, float right, float bottom, float top, float tleft, float tright, float tbottom, float ttop);
	void Draw(float left, float right, float bottom, float top, int tleft, int tright, int tbottom, int ttop) const ;
private:
	//	static std::map<std::string, CTexture>mTexFile;
		//ファイル名
	char* mpName;
	//TGAファイルのヘッダ情報
	STgamHeader mHeader;
	//テクスチャID
	GLuint mId;
	//
	int mRow;//行数
	int mCol;//列数
};

#endif
