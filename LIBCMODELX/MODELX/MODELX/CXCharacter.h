#ifndef CXCHARACTER_H
#define CXCHARACTER_H
#include "CTransform.h"

namespace modelx {

	class CTransform;
	class CMatrix;
	class CModelX;

	class CXCharacter : public CTransform {
	public:
		virtual ~CXCharacter();
		CXCharacter();
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
}

#endif
