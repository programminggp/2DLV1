#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include "CModelX.h"
#include "CMatrix.h"
#include "CCharacter3.h"

class CXCharacter : public CCharacter3 {
public:
	void AnimationFrame(float per);
	virtual ~CXCharacter() {
		SAFE_DELETE_ARRAY(mpCombinedMatrix);
	}

	CXCharacter();
	CXCharacter(CCharacter3::ETag tag);
	void Update();
	//初期化処理
	void Init(CModelX* model);
	//アニメーションの変更
	void ChangeAnimation(int index, bool loop, float framesize);
	//更新処理
	void Update(CMatrix& m);
	//描画処理
	void Render();
	//アニメーションの再生終了判定
	//true:終了　false:再生中
	bool IsAnimationFinished();
	int AnimationIndex(); //アニメーション番号の取得
protected:
	CMatrix* mpCombinedMatrix;	//合成行列退避
	CModelX* mpModel;	//モデルデータ
	int mAnimationIndex;	//アニメーション番号
	bool mAnimationLoopFlg;	//true:アニメーションを繰り返す
	float mAnimationFrame; //アニメーションの再生フレーム
	float mAnimationFrameSize;//アニメーションの再生フレーム数
};
#endif
