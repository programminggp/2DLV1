#pragma once
#include "CBillBoardImage.h"

// 電撃
class CElectricShock : public CBillBoardImage
{
public:
	// コンストラクタ
	CElectricShock(ETag tag);
	// デストラクタ
	~CElectricShock();

	/// <summary>
	/// 各パラメータを設定
	/// </summary>
	/// <param name="pos">初期位置</param>
	/// <param name="dir">移動方向</param>
	/// <param name="speed">移動速度</param>
	void Setup(const CVector& pos, const CVector& dir, float speed);

	// カラーを設定
	void SetColor(const CColor& color) override;
	// ブレンドタイプを設定
	void SetBlendType(EBlend type);

	// 削除フラグが立っているかどうか
	bool IsDeath() const;

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した相手のコライダー</param>
	/// <param name="hit">衝突した時の情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// 更新
	void Update() override;

private:
	// アニメーションデータ
	static TexAnimData msAnimData;
	CVector mMoveSpeed;	// 移動速度
	float mElapsedTime;	// 経過時間
	bool mIsDeath;		// 削除フラグ
};