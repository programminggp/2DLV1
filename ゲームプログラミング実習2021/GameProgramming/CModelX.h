#ifndef CMODEL_H
#define CMODEL_H

#define MODEL_FILE "sample.blend.x"

#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}
//配列のサイズ取得をマクロ化
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))



#include <vector>	//vectorクラスのインクルード（動的配列）
#include "CMatrix.h"	//マトリクスクラスのインクルード
#include "CVector.h"

class CModelX;	// CModelXクラスの宣言


//CMeshクラスの定義
class CMesh {
public:
	int mVertexNum;	//頂点数
	CVector* mpVertex;	//頂点データ
	int mFaceNum;	//面数
	int* mpVertexIndex;	//面を構成する頂点番号

	//コンストラクタ
	CMesh()
		: mVertexNum(0)
		, mpVertex(0)
		, mFaceNum(0)
		, mpVertexIndex(nullptr)
	{}
	//デストラクタ
	~CMesh() {
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
	}
	//読み込み処理
	void Init(CModelX* model);
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
			delete* itr;
		}
		//名前のエリアを解放する
		SAFE_DELETE_ARRAY(mpName);
	}
};


class CModelX {
public:
	char* mpPointer;
	char mToken[1024];
	std::vector<CModelXFrame*> mFrame;	//フレームの配列

	CModelX()
		: mpPointer(nullptr)
	{}

	~CModelX() {
		if (mFrame.size() > 0)
		{
			delete mFrame[0];
		}
	}

	void Load(char* file);

	//単語の取り出し
	void GetToken();

	//ノードの読み飛ばし
	void SkipNode();

	//浮動小数点データの取得
	float GetFloatToken();

	//整数データの取得
	int GetIntToken();

};

#endif
