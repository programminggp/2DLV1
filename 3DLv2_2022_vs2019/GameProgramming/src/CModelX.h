#ifndef CMODELX_H
#define CMODELX_H

#define MODEL_FILE "ラグナ.x"

#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}
//配列のサイズ取得をマクロ化
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#include <vector>	//vectorクラスのインクルード（動的配列）
#include "CMatrix.h"	//マトリクスクラスのインクルード
#include "CVector.h"
#include "CMyShader.h" //シェーダーのインクルード

class CModelX;	// CModelXクラスの宣言
class CMaterial;	//クラスの宣言
class CAnimation;
class CAnimationSet;
class CModelXFrame;
/*
 CAnimationKey
 アニメーションキークラス
*/
class CAnimationKey {
	friend CAnimation;
	friend CAnimationSet;
	friend CModelX;

	//時間
	float mTime;
	//行列
	CMatrix mMatrix;
public:
	CAnimationKey();
};
/*
 CAnimation
 アニメーションクラス
*/
class CAnimation {
	friend CAnimationSet;
	friend CModelX;

	char* mpFrameName;//フレーム名
	int mFrameIndex;	//フレーム番号
	int mKeyNum;	//キー数（時間数）
	CAnimationKey* mpKey;	//キーの配列
public:
	CAnimation();
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
	friend CModelX;

	//アニメーションセット名
	char* mpName;
	//アニメーション
	std::vector<CAnimation*> mAnimation;
	float mTime;	//現在時間
	float mWeight;	//重み
	float mMaxTime;	//最大時間
public:
	CAnimationSet();
	CAnimationSet(CModelX* model);

	~CAnimationSet() {
		SAFE_DELETE_ARRAY(mpName);
		//アニメーション要素の削除
		for (size_t i = 0; i < mAnimation.size(); i++) {
			delete mAnimation[i];
		}
	}

	const float& Time();
	const float& MaxTime();
	void Time(float time);
	void Weight(float wight);
};
/*
 CSkinWeights
 スキンウェイトクラス
*/
class CSkinWeights {
	friend CModelX;
	friend CMesh;

	char* mpFrameName;	//フレーム名
	int mFrameIndex;	//フレーム番号
	int mIndexNum;	//頂点番号数
	int* mpIndex;	//頂点番号配列
	float* mpWeight;	//頂点ウェイト配列
	CMatrix mOffset;	//オフセットマトリックス
public:
	CSkinWeights(CModelX* model);

	~CSkinWeights() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
	}

	const int& FrameIndex();
	const CMatrix& Offset();
};

//CMeshクラスの定義
class CMesh {
	friend CModelX;
	friend CModelXFrame;

	//マテリアル毎の面数
	std::vector<int> mMaterialVertexCount;
	//頂点バッファ識別子
	GLuint	  mMyVertexBufferId;
	unsigned int mVertexNum;	//頂点数
	CVector* mpVertex;	//頂点データ
	unsigned int mFaceNum;	//面数
	unsigned int* mpVertexIndex;	//面を構成する頂点番号
	unsigned int mNormalNum;	//法線数
	CVector* mpNormal;//法線データ

	unsigned int mMaterialNum;	//マテリアル数
	unsigned int mMaterialIndexNum;//マテリアル番号数（面数）
	unsigned int* mpMaterialIndex;	  //マテリアル番号
	std::vector<CMaterial*> mMaterials;//マテリアルデータ
	CVector* mpAnimateVertex;	//アニメーション用頂点
	CVector* mpAnimateNormal;	//アニメーション用法線
	//テクスチャ座標データ
	float* mpTextureCoords;

	//スキンウェイト
	std::vector<CSkinWeights*> mSkinWeights;

public:

	const unsigned int& FaceNum();
	std::vector<CSkinWeights*>& SkinWeights();
	const GLuint& MyVertexBufferId();
	std::vector<CMaterial*>& Materials();
	std::vector<int>& MaterialVertexCount();

	//コンストラクタ
	CMesh()
		: mVertexNum(0)
		, mpVertex(nullptr)
		, mFaceNum(0)
		, mpVertexIndex(nullptr)
		, mNormalNum(0)
		, mpNormal(nullptr)
		, mMaterialNum(0)
		, mMaterialIndexNum(0)
		, mpMaterialIndex(nullptr)
		, mpAnimateVertex(nullptr)
		, mpAnimateNormal(nullptr)
		, mpTextureCoords(nullptr)
		, mMyVertexBufferId(0)
	{}
	//デストラクタ
	~CMesh() {
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
		SAFE_DELETE_ARRAY(mpAnimateVertex);
		SAFE_DELETE_ARRAY(mpAnimateNormal);
		SAFE_DELETE_ARRAY(mpTextureCoords);
		//スキンウェイトの削除
		for (size_t i = 0; i < mSkinWeights.size(); i++) {
			delete mSkinWeights[i];
		}
	}
	//読み込み処理
	void Init(CModelX* model);

	void Render();
	//頂点にアニメーション適用
	void AnimateVertex(CModelX* model);

	void AnimateVertex(CMatrix*);
	//頂点バッファの作成
	void CreateVertexBuffer();
};

//CModelXFrameクラスの定義
class CModelXFrame {
	friend CModelX;
	friend CAnimation;
	friend CMesh;

	std::vector<CModelXFrame*> mChild;	//子フレームの配列
	CMatrix mTransformMatrix;	//変換行列
	char* mpName;	//フレーム名前
	int mIndex;		//フレーム番号
	CMesh mMesh;	//Meshデータ
	CMatrix mCombinedMatrix;	//合成行列
public:

	CMesh& Mesh();	//Meshデータ
	const CMatrix& CombinedMatrix();	//合成行列
	void TransformMatrix(const CMatrix& matrix);

	CModelXFrame()
		: mpName(nullptr)
		, mIndex(0) {}	//コンストラクタ

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
	//合成行列の作成
	void AnimateCombined(CMatrix* parent);

};


class CModelX {
	friend CModelXFrame;
	friend CMesh;
	friend CSkinWeights;
	friend CAnimationSet;
	friend CAnimation;

	CMyShader mShader; //シェーダーのインスタンス
	//シェーダー用スキンマトリックス
	CMatrix* mpSkinningMatrix;
	char* mpPointer;
	char mToken[1024];
	std::vector<CModelXFrame*> mFrames;	//フレームの配列
	//アニメーションセットの配列
	std::vector<CAnimationSet*> mAnimationSets;
	std::vector<CMaterial*> mMaterials;	//マテリアルの配列
public:
	std::vector<CMaterial*>& Materials();
	char* Token();
	std::vector<CModelXFrame*>& Frames();
	CMatrix* SkinningMatrix();
	std::vector<CAnimationSet*>& AnimationSets();

	CModelX();
	~CModelX();

	void Load(char* file);
	//ファイルからアニメーションセットを追加する
	void AddAnimationSet(char* file);

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

	//フレームの変換行列をアニメーションデータで更新する
	void AnimateFrame();

	//スキンウェイトのフレーム番号設定
	void SetSkinWeightFrameIndex();

	//頂点にアニメーションを適用
	void AnimateVertex();
	void AnimateVertex(CMatrix*);

	//マテリアルの検索
	CMaterial* FindMaterial(char* name);

	/*
	アニメーションを抜き出す
	idx:分割したいアニメーションセットの番号
	start:分割したいアニメーションの開始時間
	end:分割したいアニメーションの終了時間
	name:追加するアニメーションセットの名前
	*/
	void CModelX::SeparateAnimationSet(int idx, int start, int end, char* name);
	//シェーダーを使った描画
	void RenderShader(CMatrix* m);
	//モデルの入力状況
	//戻り値：true：入力済  false：未入力
	bool IsLoaded();
};

#endif
