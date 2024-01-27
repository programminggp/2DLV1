#ifndef CMODELX_H	//インクルードガード
#define CMODELX_H
#include <vector>	//vectorクラスのインクルード（動的配列）

class CModelX;	// CModelXクラスの宣言
class CModelXFrame;	// CModelXFrameクラスの宣言
class CMesh;	// CMeshクラスの宣言
class CMaterial;	//マテリアルの宣言
class CSkinWeights;	//スキンウェイトクラス
class CAnimationSet; //アニメーションセットクラス
class CAnimation; //アニメーションクラス
class CAnimationKey;  //アニメーションキークラス

#define MODEL_FILE "res\\tsample.fbx"	//入力ファイル名

//領域解放をマクロ化
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = nullptr;}

//配列のサイズ取得をマクロ化
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

/*
 CModelX
 Xファイル形式の3Dモデルデータをプログラムで認識する
*/
class CModelX {
public:

	std::vector<CModelXFrame*>& Frames();

	bool EOT();	//トークン終了するとtrue
	//単語の取り出し
	char* GetToken();
	char* Token();
	//void Render();
	//浮動小数点データの取得
	float GetFloatToken();
	~CModelX();
	//ノードの読み飛ばし
	void SkipNode();

	CModelX();
	//ファイル読み込み
	void Load(const char* file);
	bool IsLoaded();
private:


	bool mLoaded;
	std::vector<CMaterial*> mMaterial;  //マテリアル配列
	//アニメーションセットの配列
	std::vector<CAnimationSet*> mAnimationSet;
	std::vector<CModelXFrame*> mFrame;	//フレームの配列

	//cが区切り文字ならtrueを返す
	bool IsDelimiter(char c);

	char* mpPointer;	//読み込み位置
	char mToken[1024];	//取り出した単語の領域
};


#endif