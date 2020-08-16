#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include "CModelX.h"
#include "CMatrix.h"
#include "CTransform.h"

class CXCharacter : public CTransform {
public:
	CModelX *mpModel;	//モデルデータ
	int mAnimationIndex;	//アニメーション番号
	bool mAnimationLoopFlg;	//true:繰り返す
	float mAnimationFrame; //アニメーションの再生フレーム
	float mAnimationFrameSize;//アニメーションの再生フレーム数
	CMatrix *mpCombinedMatrix;	//合成行列退避

	CXCharacter()
		: mpCombinedMatrix(0)
	{
	}
	virtual ~CXCharacter() {
		SAFE_DELETE_ARRAY(mpCombinedMatrix);
	}
	//初期化処理
	void Init(CModelX *model);
	//アニメーションの変更
	void ChangeAnimation(int index, bool loop, float framesize);
	//更新処理
	void Update(CMatrix &m);
	//描画処理
	void Render();
	//
	void Update();
};

#endif