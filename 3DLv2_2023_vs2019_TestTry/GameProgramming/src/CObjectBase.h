#pragma once
#include "CTask.h"
#include "CTransform.h"
#include "ObjectTag.h"
#include "CCollider.h"
#include "CColor.h"

/// <summary>
/// 3D空間に配置するオブジェクトのベースクラス
/// </summary>
class CObjectBase : public CTask, public CTransform
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="tag">オブジェクトのタグ</param>
	/// <param name="prio">タスクの優先度</param>
	CObjectBase(ETag tag = ETag::eNone,
		ETaskPriority prio = ETaskPriority::eDefault,
		int sortOrder = 0,
		ETaskPauseType pause = ETaskPauseType::eDefault);

	// デストラクタ
	virtual ~CObjectBase();

	// オブジェクトタグを取得
	ETag Tag() const;

	// 衝突判定を行うか設定
	void SetEnableCol(bool isEnable);
	// 衝突判定を行うかどうか
	bool IsEnableCol() const;

	// カラーを設定
	virtual void SetColor(const CColor& color);
	// カラーを取得
	const CColor& GetColor() const;
	// アルファ値設定
	void SetAlpha(float alpha);
	// アルファ値取得
	float GetAlpha() const;

	// カメラまでの距離を計算
	virtual void CalcDepth();
	// カメラからの距離を取得
	float GetDepth() const;

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した相手のコライダー</param>
	/// <param name="hit">衝突した時の情報</param>
	virtual void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

private:
	ETag mTag;			//オブジェクト識別用のタグ
	bool mIsEnableCol;	// 衝突判定を行うかどうか

protected:
	float mDepth;		// カメラからの距離
	CColor mColor;		//オブジェクトの色
};