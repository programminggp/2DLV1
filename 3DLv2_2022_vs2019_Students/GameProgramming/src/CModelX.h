#pragma once
#ifndef CMODELX_H	//インクルードガード
#define CMODELX_H
#include "CMyShader.h" //シェーダーのインクルード

class CMaterial;	//クラスの宣言

#define MODEL_FILE "res\\ラグナ.x"	//入力ファイル名
//#define MODEL_FILE "res\\sample.blend.x"	//入力ファイル名

//領域解放をマクロ化
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}
//配列のサイズ取得をマクロ化
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))


#include <vector>	//vectorクラスのインクルード（動的配列）
#include "CMatrix.h"	//マトリクスクラスのインクルード
class CModelX;	// CModelXクラスの宣言
class CModelXFrame;
class CMesh;
class CAnimationSet;
class CAnimation;
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
};

/*
 CAnimation
 アニメーションクラス
*/
class CAnimation {
	friend CAnimationKey;
	friend CAnimationSet;
	friend CModelX;

	int mKeyNum;	//キー数（時間数）
	CAnimationKey* mpKey;	//キーの配列

	char* mpFrameName;//フレーム名
	int mFrameIndex;	//フレーム番号
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
	float mTime;		//現在時間
	float mWeight;	//重み
	float mMaxTime;	//最大時間
	//アニメーション
	std::vector<CAnimation*> mAnimation;

	//アニメーションセット名
	char* mpName;
public:
	CAnimationSet();
	float Time();
	float MaxTime();
	void Time(float time); //時間の設定
	void Weight(float weight); //重みの設定
	CAnimationSet(CModelX* model);

	~CAnimationSet() {
		SAFE_DELETE_ARRAY(mpName);
		//アニメーション要素の削除
		for (size_t i = 0; i < mAnimation.size(); i++) {
			delete mAnimation[i];
		}
	}
};

/*
 CSkinWeights
 スキンウェイトクラス
*/
class CSkinWeights {
	friend CMyShader;
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
	friend CMyShader;
	friend CModelX;
	friend CModelXFrame;
private:
	//マテリアル毎の面数
	std::vector<int> mMaterialVertexCount;
	//頂点バッファ識別子
	GLuint	  mMyVertexBufferId;
	//頂点バッファの作成
	void CreateVertexBuffer();

	//テクスチャ座標データ
	float* mpTextureCoords;
	CVector* mpAnimateVertex;	//アニメーション用頂点
	CVector* mpAnimateNormal;	//アニメーション用法線
	int mVertexNum;	//頂点数
	CVector* mpVertex;	//頂点データ
	int mFaceNum;	//面数
	int* mpVertexIndex;	//面を構成する頂点番号
	int mNormalNum;	//法線数
	CVector* mpNormal;//法線ベクトル
	int mMaterialNum;	//マテリアル数
	int mMaterialIndexNum;//マテリアル番号数（面数）
	int* mpMaterialIndex;	  //マテリアル番号
	std::vector<CMaterial*> mMaterial;//マテリアルデータ
	//スキンウェイト
	std::vector<CSkinWeights*> mSkinWeights;

public:
	void AnimateVertex(CMatrix*);
	//頂点にアニメーション適用
	void AnimateVertex(CModelX* model);
	void Render();
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
		//スキンウェイトの削除
		for (size_t i = 0; i < mSkinWeights.size(); i++)
		{
			delete mSkinWeights[i];
		}
		SAFE_DELETE_ARRAY(mpTextureCoords);
	}
	//読み込み処理
	void Init(CModelX* model);
};

//CModelXFrameクラスの定義
class CModelXFrame {
	friend CMyShader;
//	friend CMesh;
	friend CAnimation;
	friend CModelX;

	CMatrix mCombinedMatrix;	//合成行列
	std::vector<CModelXFrame*> mChild;	//子フレームの配列
	CMatrix mTransformMatrix;	//変換行列
	char* mpName;	//フレーム名前
	int mIndex;		//フレーム番号
	CMesh mMesh;	//Meshデータ
public:
	CModelXFrame()
		: mpName(nullptr)
		, mIndex(0) {}	//コンストラクタ
	const CMatrix& CombinedMatrix();	//合成行列
	//合成行列の作成
	void AnimateCombined(CMatrix* parent);
	void Render();
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

/*
 CModelX
 Xファイル形式の3Dモデルデータをプログラムで認識する
*/
class CModelX {
	friend CMyShader;
	friend CAnimation;
	friend CAnimationSet;
	friend CModelXFrame;
	friend CMesh;
private:
	//シェーダー用スキンマトリックス
	CMatrix* mpSkinningMatrix;
	CMyShader mShader; //シェーダーのインスタンス

	std::vector<CMaterial*> mMaterial;	//マテリアルの配列
	char* mpPointer;	//読み込み位置
	char mToken[1024];	//取り出した単語の領域
	std::vector<CModelXFrame*> mFrame;	//フレームの配列
	//アニメーションセットの配列
	std::vector<CAnimationSet*> mAnimationSet;
public:
	//シェーダーを使った描画
	void RenderShader(CMatrix* m);

	/*
	アニメーションを抜き出す
	idx:分割したいアニメーションセットの番号
	start:分割したいアニメーションの開始時間
	end:分割したいアニメーションの終了時間
	name:追加するアニメーションセットの名前
	*/
	void CModelX::SeparateAnimationSet(
		int idx, int start, int end, char* name);

	void AnimateVertex(CMatrix*);
	std::vector<CModelXFrame*>& Frames();	//フレームの配列
	std::vector<CMaterial*>& Material();
	//マテリアルの検索
	CMaterial* FindMaterial(char* name);
	//頂点にアニメーションを適用
	void AnimateVertex();
	//スキンウェイトのフレーム番号設定
	void SetSkinWeightFrameIndex();
	void AnimateFrame();
	std::vector<CAnimationSet*>& AnimationSet();
	//フレーム名に該当するフレームのアドレスを返す
	CModelXFrame* FindFrame(char* name);

	void Render();
	CModelX();
	~CModelX();

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
	char* Token();
};


#endif

