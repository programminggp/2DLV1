#ifndef CMODEL_H
#define CMODEL_H

#define MODEL_FILE "sample.blend.x"

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

};

#endif
