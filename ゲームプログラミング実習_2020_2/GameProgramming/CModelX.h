#ifndef CMODELX_H	//インクルードガード
#define CMODELX_H

#define MODEL_FILE "sample.blend.x"	//入力ファイル名

//領域解放をマクロ化
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}
//配列のサイズ取得をマクロ化
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#include <vector>	//vectorクラスのインクルード（動的配列）
#include "CMatrix.h"	//マトリクスクラスのインクルード
#include "CVector.h"
//09
class CMaterial;

class CModelX;	// CModelXクラスの宣言


//CMeshクラスの定義
class CMesh {
public:
	int mVertexNum;	//頂点数
	CVector *mpVertex;	//頂点データ
	int mFaceNum;	//面数
	int *mpVertexIndex;	//面を構成する頂点番号
	int mNormalNum;	//法線数
	CVector *mpNormal;//法線データ

	//09
	int mMaterialNum;	//マテリアル数
	int mMaterialIndexNum;//マテリアル番号数（面数）
	int *mpMaterialIndex;	  //マテリアル番号
	std::vector<CMaterial*> mMaterial;//マテリアルデータ


	//コンストラクタ
	CMesh()
		: mVertexNum(0)
		, mpVertex(0)
		, mFaceNum(0)
		, mpVertexIndex(0)
		, mNormalNum(0)
		, mpNormal(0)
		//
		, mMaterialNum(0)
		, mMaterialIndexNum(0)
		, mpMaterialIndex(0)
	{}
	//デストラクタ
	~CMesh() {
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
	}
	//読み込み処理
	void Init(CModelX *model);
	void Render();
};


//CModelXFrameクラスの定義
class CModelXFrame {
public:
	std::vector<CModelXFrame*> mChild;	//子フレームの配列
	CMatrix mTransformMatrix;	//変換行列
	char* mpName;	//フレーム名前
	int mIndex;		//フレーム番号

	CMesh mMesh;	//Meshデータ

	//コンストラクタ
	CModelXFrame(CModelX* model);
	//デストラクタ
	~CModelXFrame() {
		//子フレームを全て解放する
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++) {
			delete *itr;
		}
		//名前のエリアを解放する
		SAFE_DELETE_ARRAY(mpName);
	}
	void Render();
};
/*
CModelX
Xファイル形式の3Dモデルデータをプログラムで認識する
*/
class CModelX {
public:
	char* mpPointer;	//読み込み位置
	char mToken[1024];	//取り出した単語の領域
	std::vector<CModelXFrame*> mFrame;	//フレームの配列

	CModelX() 
		: mpPointer(0)
	{}

	~CModelX() {
		delete mFrame[0];
	}
	//ファイル読み込み
	void Load(char* file);
	//単語の取り出し
	void GetToken();
	//ノードの読み飛ばし
	void SkipNode();
	//浮動小数点データの取得
	float GetFloatToken();
	//整数データの取得
	int GetIntToken();
	void Render();

};

#endif
