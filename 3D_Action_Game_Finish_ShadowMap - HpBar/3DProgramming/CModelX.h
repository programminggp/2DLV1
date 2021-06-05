#ifndef CMODELX_H
#define CMODELX_H
#include "CMyShader.h" //シェーダーのインクルード
#include <vector>	//vectorクラスのインクルード（動的配列）
#include "CMatrix44.h"	//マトリクスクラスのインクルード
#include "CTexture.h"
#include "CMaterial.h"

//#define MODEL_FILE "sample.blend.x"
//#define MODEL_FILE "ラグナ.x"	//入力ファイル名

//ポインタ配列の破棄
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}
//配列のサイズ取得をマクロ化
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

/*
頂点バッファデータクラス
頂点毎にデータをまとめます
*/
class CMyVertex {
public:
	//位置
	CVector3 mPosition;
	//法線
	CVector3 mNormal;
	//テクスチャマッピング
	CVector2 mTextureCoords;
	//スキンウェイト
	float mBoneWeight[4];
	//スキンインデックス
	float mBoneIndex[4];

	CMyVertex() {
		for (int i = 0; i < 4; i++) {
			mBoneIndex[i] = 0;
			mBoneWeight[i] = 0.0f;
		}
		mBoneWeight[0] = 1.0f;
	}
};


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
	CMatrix44 mMatrix;
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
		: mpFrameName(0), mpKey(0)
	{}

	CAnimation(CModelX *model);

	~CAnimation() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);
	}

	CAnimation(const CAnimation& c) {
		mpFrameName = new char[strlen(c.mpFrameName) + 1];
		strcpy(mpFrameName, c.mpFrameName);
		mFrameIndex = c.mFrameIndex;
		mKeyNum = c.mKeyNum;
		mpKey = new CAnimationKey[mKeyNum];
		for (int i = 0; i < mKeyNum; i++) {
			mpKey[i] = c.mpKey[i];
		}
	}

	const CAnimation operator=(const CAnimation &c) {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);

		mpFrameName = new char[strlen(c.mpFrameName) + 1];
		strcpy(mpFrameName, c.mpFrameName);
		mFrameIndex = c.mFrameIndex;
		mKeyNum = c.mKeyNum;
		mpKey = new CAnimationKey[mKeyNum];
		for (int i = 0; i < mKeyNum; i++) {
			mpKey[i] = c.mpKey[i];
		}
		return (*this);
	}

};
/*
CAnimationSet
アニメーションセット
*/
class CAnimationSet {
public:
	//アニメーション名
	char *mpName;
	//アニメーション
	std::vector<CAnimation*> mAnimation;

	float mTime;	//現在時間
	float mWeight;	//重み
	float mMaxTime;	//最大時間

	CAnimationSet()
		: mpName(0), mTime(0), mMaxTime(0), mWeight(0)
	{}

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
	CMatrix44 mOffset;	//オフセットマトリックス

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
	CVector3 *mpVertex;	//頂点データ
	int mFaceNum;	//面数
	int *mpVertexIndex;	//面を構成する頂点番号
	int mNormalNum;	//法線数
	CVector3 *mpNormal;//法線データ
	int mMaterialNum;	//マテリアル数
	int mMaterialIndexNum;//マテリアル番号数（面数）
	int *mpMaterialIndex;	  //マテリアル番号
	std::vector<CMaterial*> mMaterial;//マテリアルデータ
	//スキンウェイト
	std::vector<CSkinWeights*> mSkinWeights;
	CVector3 *mpAnimateVertex;	//アニメーション用頂点
	CVector3 *mpAnimateNormal;	//アニメーション用法線
	//テクスチャ座標データ
	CVector2 *mpTextureCoords;

	//37
	//マテリアル毎の面数
	std::vector<int> mMaterialVertexCount;
	//頂点バッファ識別子
	GLuint	  mMyVertexBufferId;
	//頂点バッファの作成
	void CreateVertexBuffer();


	//コンストラクタ
	CMesh()
		: mVertexNum(0)
		, mpVertex(0)
		, mFaceNum(0)
		, mpVertexIndex(0)
		, mNormalNum(0)
		, mpNormal(0)
		, mMaterialNum(0)
		, mMaterialIndexNum(0)
		, mpMaterialIndex(0)
		, mpAnimateVertex(0)
		, mpAnimateNormal(0)
		, mpTextureCoords(0)
		, mMyVertexBufferId(0)
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
	void AnimateVertex(CMatrix44*);
};

//CModelXFrameクラスの定義
class CModelXFrame {
public:
	std::vector<CModelXFrame*> mChild;	//子フレームの配列
	CMatrix44 mTransformMatrix;	//変換行列
	char* mpName;	//フレーム名前
	int mIndex;		//フレーム番号
	CMesh mMesh;	//Meshデータ
	CMatrix44 mCombinedMatrix;	//合成行列
	CModelXFrame()
		: mIndex(0)
		, mpName(0)
	{};
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
	void Animate(CMatrix44* parent);

};

class CModelX {
public:
	char* mpPointer;	//読み込み位置
	char mToken[1024];	//取り出した単語の領域
	std::vector<CModelXFrame*> mFrame;	//フレームの配列
	//アニメーションセットの配列
	std::vector<CAnimationSet*> mAnimationSet;
	std::vector<CMaterial*> mMaterial;	//マテリアルの配列
	std::vector<CTexture*> mTexture;	//テクスチャの配列
	//37
	CMatrix44 *mpSkinningMatrix; //シェーダー用スキンマトリックス
	CMyShader mShader; //シェーダーのインスタンス

	CModelX()
		: mpPointer(0)
		, mpSkinningMatrix(0) //37
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
		//テクスチャの解放
		for (int i = 0; i < mTexture.size(); i++) {
			delete mTexture[i];
		}
		//37
		SAFE_DELETE_ARRAY(mpSkinningMatrix);
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
	void AnimateVertex(CMatrix44*);
	//マテリアルの検索
	CMaterial* FindMaterial(char* name);
	//テクスチャの検索
	CTexture* FindTexture(char* name);
	//37
	//シェーダーを使った描画
	void RenderShader(CMatrix44 *m);

	void AddMaterial(CModelX*, CMaterial*);
	void SeparateAnimationSet(int start, int end, char* name);
};

#endif
