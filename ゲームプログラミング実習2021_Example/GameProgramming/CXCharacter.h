#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include "CModelX.h"
#include "CMatrix.h"
#include "CCharacter.h"

class CXCharacter : public CCharacter {
public:
	CModelX* mpModel;	//モデルデータ
	int mAnimationIndex;	//アニメーション番号
	bool mAnimationLoopFlg;	//true:アニメーションを繰り返す
	float mAnimationFrame; //アニメーションの再生フレーム
	float mAnimationFrameSize;//アニメーションの再生フレーム数
	CMatrix* mpCombinedMatrix;	//合成行列退避
	CXCharacter();
	~CXCharacter()
	{
		SAFE_DELETE_ARRAY(mpCombinedMatrix);
	}
	//初期化処理
	void Init(CModelX* model);
	//アニメーションの変更
	void ChangeAnimation(int index, bool loop, float framesize);
	//更新処理
	void Update(CMatrix& m);
	void Update();
	//描画処理
	void Render();
};

#endif
