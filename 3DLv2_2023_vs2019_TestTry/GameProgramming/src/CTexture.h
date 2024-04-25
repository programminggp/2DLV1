#ifndef CTEXTURE_H
#define CTEXTURE_H
#include "glut.h"
#include "CRect.h"
#include <vector>
#include "CResource.h"

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

class CTexture : public CResource
{
	friend CResourceManager;

public:
	int Row();
	int Col();
	const STgamHeader& Header() const;
	const GLuint& Id() const;
	//行数列数の設定
	//SetRowCol(行数, 列数)
	void SetRowCol(int row = 1, int col = 1);

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

	/// <summary>
	/// 行数と列数を指定してUVを計算
	/// </summary>
	/// <param name="row">行数</param>
	/// <param name="col">列数</param>
	/// <param name="num">取得するUVの番号</param>
	/// <returns></returns>
	CRect CalcUV(int row, int col, int num) const;
	/// <summary>
	/// 座標を指定してUVを計算
	/// </summary>
	/// <param name="left">左側の座標</param>
	/// <param name="top">上側の座標</param>
	/// <param name="right">右側の座標</param>
	/// <param name="bottom">下側の座標</param>
	/// <returns></returns>
	CRect CalcUV(float left, float top, float right, float bottom) const;
	/// <summary>
	/// 開始位置とサイズを指定してUVを計算
	/// </summary>
	/// <param name="pos">開始位置</param>
	/// <param name="size">サイズ</param>
	/// <returns></returns>
	CRect CalcUV(const CVector2& pos, const CVector2& size) const;

private:
	/*
	デフォルトコンストラクタ
	*/
	CTexture();
	CTexture(char* file);
	/*
	デストラクタ（このインスタンスが破棄されるときに実行される）
	*/
	~CTexture();
	/*
	Load(ファイル名)
	画像ファイルの読み込み（テクスチャファイルの読み込み）
	*/
	bool Load(std::string path, bool dontDelete) override;

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

// テクスチャのアニメーションのフレーム情報
struct TexAnimFrameData
{
	int no;		// 画像番号
	float time;	// 次の画像までの時間
};

// テクスチャのアニメーションデータ
class TexAnimData
{
public:
	int row;	// 行数
	int col;	// 列数
	bool loop;	// ループするかどうか
	// フレーム情報リスト
	std::vector<TexAnimFrameData> frames;

	TexAnimData(int r, int c, bool l, std::vector<TexAnimFrameData> f)
		: row(r)
		, col(c)
		, loop(l)
		, frames(f)
	{
	}

	TexAnimData(int r, int c, bool l, int fc, float fr)
		: row(r)
		, col(c)
		, loop(l)
	{
		for (int i = 0; i < fc; i++)
		{
			frames.push_back({ i, fr });
		}
	}
};

#endif
