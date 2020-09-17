#ifndef CMODELX_H	//インクルードガード
#define CMODELX_H

#define MODEL_FILE "ラグナ.x"	//入力ファイル名
//#define MODEL_FILE "sample.blend.x"	//入力ファイル名

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
	char *mpFrameName;//フレーム名
	int mFrameIndex;	//フレーム番号
	int mKeyNum;	//キー数（時間数）
	CAnimationKey *mpKey;	//キーの配列

	CAnimation()
		: mpFrameName(0)
		, mpKey(0)
	{}

	CAnimation(CModelX *model);

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
	char *mpName;
	//アニメーション
	std::vector<CAnimation*> mAnimation;

	float mTime;	//現在時間
	float mWeight;	//重み
	float mMaxTime;	//最大時間

	CAnimationSet(){}

	CAnimationSet(CModelX *model);

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
	char *mpFrameName;	//フレーム名
	int mFrameIndex;	//フレーム番号
	int mIndexNum;	//頂点番号数
	int *mpIndex;	//頂点番号配列
	float *mpWeight;	//頂点ウェイト配列
	CMatrix mOffset;	//オフセットマトリックス

	CSkinWeights(CModelX *model);

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
	//スキンウェイト
	std::vector<CSkinWeights*> mSkinWeights;

	CVector *mpAnimateVertex;	//アニメーション用頂点
	CVector *mpAnimateNormal;	//アニメーション用法線
	//テクスチャ座標データ
	float *mpTextureCoords;

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
		//
		, mpAnimateVertex(0)
		, mpAnimateNormal(0)
		, mpTextureCoords(0)
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
		SAFE_DELETE_ARRAY(mpAnimateVertex);
		SAFE_DELETE_ARRAY(mpAnimateNormal);
		SAFE_DELETE_ARRAY(mpTextureCoords);
	}
	//読み込み処理
	void Init(CModelX *model);
	void Render();
	//頂点にアニメーション適用
	void AnimateVertex(CModelX *model);
	void AnimateVertex(CMatrix*);
};


//CModelXFrameクラスの定義
class CModelXFrame {
public:
	std::vector<CModelXFrame*> mChild;	//子フレームの配列
	CMatrix mTransformMatrix;	//変換行列
	char* mpName;	//フレーム名前
	int mIndex;		//フレーム番号

	CMesh mMesh;	//Meshデータ

	CMatrix mCombinedMatrix;	//合成行列

	CModelXFrame()
		: mpName(0)
		, mIndex(0) {}


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
	//合成行列の作成
	void AnimateCombined(CMatrix* parent);
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
	//アニメーションセットの配列
	std::vector<CAnimationSet*> mAnimationSet;
	std::vector<CMaterial*> mMaterial;	//マテリアルの配列

	CModelX() 
		: mpPointer(0)
	{}

	~CModelX() {
		delete mFrame[0];
		for (int i = 0; i < mAnimationSet.size(); i++) {
			delete mAnimationSet[i];
		}
		//マテリアルの解放
		for (int i = 0; i < mMaterial.size(); i++) {
			delete mMaterial[i];
		}
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
	CModelXFrame* FindFrame(char* name);
	void AnimateFrame();
	//スキンウェイトのフレーム番号設定
	void SetSkinWeightFrameIndex();
	//頂点にアニメーションを適用
	void AnimateVertex();
	//マテリアルの検索
	CMaterial* FindMaterial(char* name);
	void AnimateVertex(CMatrix*);
	//アニメーションを抜き出す
	void CModelX::SeparateAnimationSet(int idx, int start, int end, char* name);
};

#endif
