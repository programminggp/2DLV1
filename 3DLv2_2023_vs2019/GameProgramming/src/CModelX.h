#ifndef CMODELX_H	//インクルードガード
#define CMODELX_H
#include <vector>	//vectorクラスのインクルード（動的配列）
#include "CMatrix.h"	//マトリクスクラスのインクルード
#include "CVector.h"

class CModelX;	// CModelXクラスの宣言
class CModelXFrame;	// CModelXFrameクラスの宣言
class CMesh;	// CMeshクラスの宣言
class CMaterial;	//マテリアルの宣言
class CSkinWeights;	//スキンウェイトクラス
class CAnimationSet; //アニメーションセットクラス
class CAnimation; //アニメーションクラス
class CAnimationKey;  //アニメーションキークラス

#define MODEL_FILE "res\\sample.blend.x"	//入力ファイル名

//領域解放をマクロ化
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = nullptr;}

//配列のサイズ取得をマクロ化
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

/*
 CModelX
 Xファイル形式の3Dモデルデータをプログラムで認識する
*/
class CModelX {
	friend CModelXFrame;
	friend CAnimationSet;

//	friend CMesh;
//	friend CMaterial;
public:
	//頂点にアニメーションを適用
	void AnimateVertex();
	//スキンウェイトのフレーム番号設定
	void SetSkinWeightFrameIndex();
	std::vector<CModelXFrame*>& Frames();

	void AnimateFrame();
	std::vector<CAnimationSet*>& AnimationSet();
	//フレーム名に該当するフレームのアドレスを返す
	CModelXFrame* FindFrame(char* name);
	bool EOT();	//トークン終了するとtrue
	//単語の取り出し
	char* GetToken();
	char* Token();
	void Render();
	//浮動小数点データの取得
	float GetFloatToken();
	~CModelX();
	//ノードの読み飛ばし
	void SkipNode();

	CModelX();
	//ファイル読み込み
	void Load(char* file);
private:
	//アニメーションセットの配列
	std::vector<CAnimationSet*> mAnimationSet;
	std::vector<CModelXFrame*> mFrame;	//フレームの配列

	//cが区切り文字ならtrueを返す
	bool IsDelimiter(char c);

	char* mpPointer;	//読み込み位置
	char mToken[1024];	//取り出した単語の領域
};

//CModelXFrameクラスの定義
class CModelXFrame {
	friend CModelX;
	friend CAnimationSet;
public:
	const CMatrix& CombinedMatrix();
	//合成行列の作成
	void AnimateCombined(CMatrix* parent);
	void Render();
	//コンストラクタ
	CModelXFrame(CModelX* model);
	//デストラクタ
	~CModelXFrame();
	int Index();
private:
	CMatrix mCombinedMatrix;	//合成行列
	CMesh *mpMesh;	//Meshデータ
	std::vector<CModelXFrame*> mChild;	//子フレームの配列
	CMatrix mTransformMatrix;	//変換行列
	char* mpName;	//フレーム名前
	int mIndex;		//フレーム番号
};

//CMeshクラスの定義
class CMesh {
//	friend CModelX;
//	friend CModelXFrame;
public:
	//頂点にアニメーション適用
	void AnimateVertex(CModelX* model);
	//スキンウェイトにフレーム番号を設定する
	void SetSkinWeightFrameIndex(CModelX *model);
	void Render();
	//コンストラクタ
	CMesh();
	//デストラクタ
	~CMesh();
	//読み込み処理
	void Init(CModelX* model);
private:
	CVector* mpAnimateVertex;  //アニメーション用頂点
	CVector* mpAnimateNormal;  //アニメーション用法線
	//スキンウェイト
	std::vector<CSkinWeights*> mSkinWeights;
	int mMaterialNum;	//マテリアル数
	int mMaterialIndexNum;//マテリアル番号数（面数）
	int* mpMaterialIndex;	  //マテリアル番号
	std::vector<CMaterial*> mMaterial;//マテリアルデータ
	int mNormalNum;	//法線数
	CVector* mpNormal;//法線ベクトル
	int mFaceNum;	//面数
	int* mpVertexIndex;	//面を構成する頂点インデックス
	int mVertexNum;	//頂点数
	CVector* mpVertex;	//頂点データ
};

/*
 CSkinWeights
 スキンウェイトクラス
*/
class CSkinWeights {
	friend CModelX;
	friend CMesh;
public:
	CSkinWeights(CModelX* model);
	~CSkinWeights();
	const int& FrameIndex();
	const CMatrix& Offset();
private:
	char* mpFrameName;	//フレーム名
	int mFrameIndex;	//フレーム番号
	int mIndexNum;	//頂点番号数
	int* mpIndex;	//頂点番号配列
	float* mpWeight;	//頂点ウェイト配列
	CMatrix mOffset;	//オフセットマトリックス
};

/*
 CAnimationSet
 アニメーションセット
*/
class CAnimationSet {
	friend CModelX;
public:
	float Time();
	float MaxTime();

	void AnimateMatrix(CModelX* model);
	std::vector<CAnimation*>& Animation();

	void Time(float time);
	void Weight(float weight);
//	float Weight();
	CAnimationSet(CModelX* model);
	~CAnimationSet();
private:
	float mTime;		//現在時間
	float mWeight;	//重み
	float mMaxTime;	//最大時間
	//アニメーション
	std::vector<CAnimation*> mAnimation;

	//アニメーションセット名
	char* mpName;
};

/*
 CAnimation
 アニメーションクラス
*/
class CAnimation {
	friend CAnimationSet;
	friend CModelX;
public:
//	int FrameIndex();  // return mFrameIndex
//	CAnimationKey* Key(); //return mpKey
//	int KeyNum();  // return mKeyNum
	CAnimation(CModelX* model);
	~CAnimation();
private:
	int mKeyNum;	//キー数（時間数）
	CAnimationKey* mpKey;	//キーの配列
	char* mpFrameName;//フレーム名
	int mFrameIndex;	//フレーム番号
};

/*
 CAnimationKey
 アニメーションキークラス
*/
class CAnimationKey {
	friend CAnimation;
	friend CAnimationSet;
//	friend CModelX;
private:
	//時間
	float mTime;
	//行列
	CMatrix mMatrix;
};

#endif