#pragma once
#include "CTask.h"
#include "CObjectBase.h"

class CElectricShock;

// 電撃エフェクトクラス
class CElectricShockEffect : public CTask
{
public:
	// コンストラクタ
	CElectricShockEffect(CObjectBase* owner, const CMatrix* attach,
		const CVector& offsetPos = CVector::zero,
		const CMatrix& offsetRot = CMatrix::identity);
	// デストラクタ
	~CElectricShockEffect();

	// 電撃を開始
	void Start();
	// 電撃を停止
	void Stop();

	// 電撃をしているかどうか
	bool IsThrowing() const;

	// 電撃時のオフセット位置を設定
	void SetThrowOffsetPos(const CVector& pos);
	// 電撃時のオフセット回転値を設定
	void SetThrowOffsetRot(const CMatrix& rot);

	// 更新
	void Update() override;

private:
	// 電撃を作成
	void CreateSlash();

	// 電撃の位置を取得
	CVector GetThrowPos() const;
	// 電撃の方向を取得
	CVector GetThrowDir() const;

	// 発射した雷のエフェクトのリスト
	std::list<CElectricShock*> mElectricShock;
	CObjectBase* mpOwner;		// このエフェクトの持ち主
	const CMatrix* mpAttachMtx;	// エフェクトをアタッチする行列
	CVector mThrowOffsetPos;	// ビーム時のオフセット位置
	CMatrix mThrowOffsetRot;	// ビーム時のオフセット回転値
	float mElapsedTime;			// 経過時間計測用
	bool mIsThrowing;			// 電撃をしているか
};