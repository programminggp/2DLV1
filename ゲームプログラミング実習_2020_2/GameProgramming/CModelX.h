#ifndef CMODELX_H	//インクルードガード
#define CMODELX_H

#define MODEL_FILE "sample.blend.x"	//入力ファイル名

//領域解放をマクロ化
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}

#include <vector>	//vectorクラスのインクルード（動的配列）
#include "CMatrix.h"	//マトリクスクラスのインクルード
class CModelX;	// CModelXクラスの宣言

//CModelXFrameクラスの定義
class CModelXFrame {
public:
	std::vector<CModelXFrame*> mChild;	//子フレームの配列
	CMatrix mTransformMatrix;	//変換行列
	char* mpName;	//フレーム名前
	int mIndex;		//フレーム番号
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
};

#endif
