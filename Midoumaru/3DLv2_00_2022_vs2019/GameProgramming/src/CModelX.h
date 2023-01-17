#ifndef CMODELX_H //インクルードガード
#define CMODELX_H

#include<vector>//vecotrクラスのインクルード(動的配置)
#include"CMatrix.h"//マトリクスクラスのインクルード
#include"CMyShader.h" //シェーダーのインクルード
#include"CVector.h"



#define MODEL_FILE "res\\sample.blend.x"//入力ファイル名
//領域解放をマクロ化
#define SAFE_DELETE_ARRAY(a){if(a)delete[]a;a=0;}
#define ARRAY_SIZE(a)(sizeof(a)/sizeof(a[0]))
//#define MODEL_FILE "res\\ラグナ.x"    //入力ファイル名


class CModelX;//cNodelXクラスの宣言
class CModelXFrame;
class CMaterial;
class CMesh;//フレンド定義用
class CAnimationSet; //フレンド用
class CAnimation;


/*
CAnimationKey
アニメーションキークラス
*/
class CAnimationKey {
	friend CAnimation;
	friend CAnimationSet;
	friend CModelX;
	//friend CMyShader;
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
	//friend CMyShader;
	char* mpFrameName; //フレーム名
	int mFrameIndex; //フレーム番号
public:
	CAnimation(CModelX* model);
	~CAnimation() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);
	}
	CAnimation();
private:
	int mKeyNum; //キー数(時間)
	CAnimationKey* mpKey; //キーの配列
};

/*
CAnimationSet
アニメーションセット
*/
class CAnimationSet {
	friend CModelX;
	//friend CMyShader;
	//アニメーションセット名
	char* mpName;
public:
	CAnimationSet(CModelX* model);
	~CAnimationSet() {
		SAFE_DELETE_ARRAY(mpName);
		//アニメーション要素の削除
		for (size_t i = 0; i < mAnimation.size(); i++)
		{
			delete mAnimation[i];
		}
	}
	void Time(float time);
	void Weight(float weight);
	int Time();
	int MaxTime();
	CAnimationSet();
private:
	//アニメーション
	std::vector<CAnimation*>mAnimation;
	float mTime; //現在時間
	float mWeight; //重み
	float mMaxTime;//最大時間
};

/*
CSkinWeights
スキンウェイトクラス
*/
class CSkinWeights {
	friend CModelX;
	friend CMesh;
	friend CMyShader;
	char* mpFrameName; //フレーム名
	int mFrameIndex; //フレーム番号
	int mIndexNum; //頂点番号数
	int* mpIndex; //頂点番号配列
	float* mpWeight; //頂点ウェイト配列
	CMatrix mOffset; //オフセットマトリクス
public:
	CSkinWeights(CModelX* model);
	~CSkinWeights() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
		const int& FrameIndex();
		const CMatrix& Offset();
	}
};


//CMeshクラスの定義
class CMesh {
	friend CModelX;
	friend CModelXFrame;
	friend CMyShader;
	int mVertexNum; //頂点数
	CVector* mpVertex; //頂点データ
	int mFaceNum; //画像
	int* mpVertexIndex; //画を構成する頂点番号
	int mNormalNum; //法線数
	CVector* mpNormal; //法線ベクトル
	int mMaterialNum; //マテリアル数
	int mMaterialIndexNum; //mマテリアル番号数(画数)
	int* mpMaterialIndex; //マテリアル番号
	std::vector<CMaterial*>mMaterial; //マテリアルデータ
	std::vector<CSkinWeights*>mSkinWeights;
	//テクスチャ座標データ
	float* mpTextureCoords;
public:
	//コンストラクタ
	CMesh()
		:mVertexNum(0)
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
	~CMesh();
	//読み込み処理
	void Init(CModelX* model);
	void Render();
	//頂点にアニメーション適用
	void AnimateVertex(CModelX* model);
	void AnimateVertex(CMatrix*);
	//マテリアル毎面数
	std::vector<int> mMaterialVertexCount;
	//頂点バッファ識別子
	GLuint mMyVertexBufferId;
	//頂点バッファ作成
	void CreateVertexBuffer();
private:
	CVector* mpAnimateVertex; //アニメーション用頂点
	CVector* mpAnimateNormal;//アニメーション用法線

};


//CNodelXFrameクラスの定義
class CModelXFrame {
	friend CModelX;
	friend CAnimation;
	friend CMyShader;
	std::vector<CModelXFrame*>mChild;//子フレームの配置
	CMatrix mTransformMatrix;//変換行列
	char* mpName;//フレーム名前
	int mIndex;//フレーム番号
public:
	CModelXFrame(CModelX* model);//コンストラクタ
	~CModelXFrame() {
		//子フレームを全て解放する
		std::vector<CModelXFrame*>::iterator itr;
		for (itr  = mChild.begin(); itr != mChild.end(); itr++)
		{
			delete* itr;
		}
		//名前のエリアを解放する
		SAFE_DELETE_ARRAY(mpName);
		
	}
	void Render();
	void AnimateCombined(CMatrix* parent);
	const CMatrix& CombinedMatrix();
	CModelXFrame()
		:mpName(nullptr)
		, mIndex(0){}
private:
	CMesh mMesh; //Meshデータ
	CMatrix mCombinedMatrix; //合成行列
};

/*
CModelX
Xファイル形式の3Dモデルデータをプログラムで認識する
*/
class CModelX {
	friend CModelXFrame;
	friend CMesh;
	friend CAnimationSet;
	friend CAnimation;
	friend CMyShader;
	char* mpPointer;//読み取り位置
	char mToken[1024];//取り出した単語の領域
	std::vector<CModelXFrame*>mFrame;//フレームの配置
	std::vector<CMaterial*>mMaterial;
public:
	CModelX();
	~CModelX();
	//ファイルの読み込み
	void Load(char* file);
	void GetToken();//ノードの読み飛ばし
	void SkipNode();
	//浮動小数点データの取得
	float GetFloatToken();
	//整数データの取得
	int GetIntToken();
	void Render();
	char* Token();
	//フレーム名に該当するフレームのアドレスを返す
	CModelXFrame* FindFrame(char* name);
	std::vector<CAnimationSet*>& AnimationSet();
	void AnimateFrame();
	std::vector<CModelXFrame*>& Frames();
	//スキンウェイトのフレーム番号設定
	void SetSkinWeightFrameIndex();
	//頂点にアニメーションを適用
	void AnimateVertex();
	//マテリアルの検索
	CMaterial* FindMaterial(char* name);
	std::vector<CMaterial*>&Material();
	void AnimateVertex(CMatrix*);
	/*
    アニメーションを抜き出す
    idx:分割したいアニメーションセットの番号
    start:分割したいアニメーションセットの開始時間
    end:分割したいアニメーションセットの終了時間
    name:追加するアニメーションセットの名前
    */
	void CModelX::SeparateAnimationSet(int idx, int start, int end, char* name);
	//シェーダーを使った描画
	void RenderShader(CMatrix* m);
	//アニメーションセットの追加
	void AddAnimationSet(const char* file);


private:
	//アニメーションセットの配列
	std::vector<CAnimationSet*>mAnimationSet;
	//シェーダー用スキンマトリックス
	CMatrix* mpSkinningMatrix;
	CMyShader mShader;//シェーダーのインスタンス

};

#endif 

