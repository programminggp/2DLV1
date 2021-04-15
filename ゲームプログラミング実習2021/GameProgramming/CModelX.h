#ifndef CMODELX_H
#define CMODELX_H

#define MODEL_FILE "sample.blend.x"

#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}
//配列のサイズ取得をマクロ化
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))



#include <vector>	//vectorクラスのインクルード（動的配列）
#include "CMatrix.h"	//マトリクスクラスのインクルード
#include "CVector.h"

class CModelX;	// CModelXクラスの宣言
class CMaterial;	//クラスの宣言

/*
 CAnimationKey
 アニメーションキークラス
*/
class CAnimationKey {
public:
	//時間
	float mTime;
	//行列
	CMatrix mMatrix;
};
/*
 CAnimation
 アニメーションクラス
*/
class CAnimation {
public:
	char* mpFrameName;//フレーム名
	int mFrameIndex;	//フレーム番号
	int mKeyNum;	//キー数（時間数）
	CAnimationKey* mpKey;	//キーの配列

	CAnimation(CModelX* model);

	~CAnimation() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);
	}
};
/*
 CAnimationSet
 アニメーションセット
*/
class CAnimationSet {
public:
	//アニメーションセット名
	char* mpName;
	//アニメーション
	std::vector<CAnimation*> mAnimation;

	CAnimationSet(CModelX* model);

	~CAnimationSet() {
		SAFE_DELETE_ARRAY(mpName);
		//アニメーション要素の削除
		for (int i = 0; i < mAnimation.size(); i++) {
			delete mAnimation[i];
		}
	}
};
/*
 CSkinWeights
 スキンウェイトクラス
*/
class CSkinWeights {
public:
	char* mpFrameName;	//フレーム名
	int mFrameIndex;	//フレーム番号
	int mIndexNum;	//頂点番号数
	int* mpIndex;	//頂点番号配列
	float* mpWeight;	//頂点ウェイト配列
	CMatrix mOffset;	//オフセットマトリックス

	CSkinWeights(CModelX* model);

	~CSkinWeights() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
	}
};

//CMeshクラスの定義
class CMesh {
public:
	int mVertexNum;	//頂点数
	CVector* mpVertex;	//頂点データ
	int mFaceNum;	//面数
	int* mpVertexIndex;	//面を構成する頂点番号
	int mNormalNum;	//法線数
	CVector* mpNormal;//法線データ

	int mMaterialNum;	//マテリアル数
	int mMaterialIndexNum;//マテリアル番号数（面数）
	int* mpMaterialIndex;	  //マテリアル番号
	std::vector<CMaterial*> mMaterial;//マテリアルデータ

	//スキンウェイト
	std::vector<CSkinWeights*> mSkinWeights;

	//コンストラクタ
	CMesh()
		: mVertexNum(0)
		, mpVertex(0)
		, mFaceNum(0)
		, mpVertexIndex(nullptr)
		, mNormalNum(0)
		, mpNormal(nullptr)
		, mMaterialNum(0)
		, mMaterialIndexNum(0)
		, mpMaterialIndex(nullptr)
	{}
	//デストラクタ
	~CMesh() {
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
		//スキンウェイトの削除
		for (int i = 0; i < mSkinWeights.size(); i++) {
			delete mSkinWeights[i];
		}
	}
	//読み込み処理
	void Init(CModelX* model);

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
			delete* itr;
		}
		//名前のエリアを解放する
		SAFE_DELETE_ARRAY(mpName);
	}

	void Render();
};


class CModelX {
public:
	char* mpPointer;
	char mToken[1024];
	std::vector<CModelXFrame*> mFrame;	//フレームの配列
	//アニメーションセットの配列
	std::vector<CAnimationSet*> mAnimationSet;

	CModelX()
		: mpPointer(nullptr)
	{}

	~CModelX() {
		if (mFrame.size() > 0)
		{
			delete mFrame[0];
		}
		for (int i = 0; i < mAnimationSet.size(); i++) {
			delete mAnimationSet[i];
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

	void Render();

	//フレーム名に該当するフレームのアドレスを返す
	CModelXFrame* FindFrame(char* name);

};

#endif
