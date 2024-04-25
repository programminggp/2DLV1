#include "CElectricShockEffect.h"
#include "CElectricShock.h"
#include "Maths.h"

// 電撃の間隔時間
#define THROW_INTERVAL 0.4f
// 電撃の方向のブレ幅
#define FLAME_DIR_RAND 0.02f
// 電撃の移動速度
#define FLAME_MOVE_SPEED 100.0f
// 電撃の色
#define FLAME_COLOR CColor(1.0f, 1.0f, 0.0f)

// コンストラクタ
CElectricShockEffect::CElectricShockEffect(CObjectBase* owner, const CMatrix* attach,
	const CVector& offsetPos, const CMatrix& offsetRot)
	: mpOwner(owner)
	, mpAttachMtx(attach)
	, mThrowOffsetPos(offsetPos)
	, mThrowOffsetRot(offsetRot)
	, mElapsedTime(0.0f)
	, mIsThrowing(false)
{
}

// デストラクタ
CElectricShockEffect::~CElectricShockEffect()
{
	for (CElectricShock* electricShock :mElectricShock)
	{
		electricShock->Kill();
	}
}

// 電撃を開始
void CElectricShockEffect::Start()
{
	mIsThrowing = true;
	mElapsedTime = 0.0f;
}

// 電撃を停止
void CElectricShockEffect::Stop()
{
	mIsThrowing = false;
}

// 電撃をしているかどうか
bool CElectricShockEffect::IsThrowing() const
{
	return mIsThrowing;
}

// 電撃時のオフセット位置を設定
void CElectricShockEffect::SetThrowOffsetPos(const CVector& pos)
{
	mThrowOffsetPos = pos;
}

// 電撃時のオフセット回転値を設定
void CElectricShockEffect::SetThrowOffsetRot(const CMatrix& rot)
{
	mThrowOffsetRot = rot;
}

// 電撃の位置を取得
CVector CElectricShockEffect::GetThrowPos() const
{
	// アタッチする行列が設定されている場合は、行列の座標を返す
	if (mpAttachMtx != nullptr)
	{
		CVector pos = mpAttachMtx->Position();
		pos += mpAttachMtx->VectorX() * mThrowOffsetPos.X()
			+ mpAttachMtx->VectorY() * mThrowOffsetPos.Y()
			+ mpAttachMtx->VectorZ() * mThrowOffsetPos.Z();
		return pos;
	}
	// 持ち主が設定されている場合は、持ち主の座標を返す
	else if (mpOwner != nullptr)
	{
		return mpOwner->Position() + (mpOwner->Rotation() * mThrowOffsetPos);
	}

	return CVector::zero;
}

// 電撃の方向を取得
CVector CElectricShockEffect::GetThrowDir() const
{
	// アタッチする行列が設定されている場合は、行列の正面方向ベクトルを返す
	if (mpAttachMtx != nullptr)
	{
		return mThrowOffsetRot * mpAttachMtx->VectorZ();
	}
	// 持ち主が設定されている場合は、持ち主の正面方向ベクトルを返す
	else if (mpOwner != nullptr)
	{
		return mThrowOffsetRot * mpOwner->VectorZ();
	}

	return CVector::forward;
}

// 電撃を作成
void CElectricShockEffect::CreateSlash()
{
	// 電撃を作成
	CElectricShock* electricShock = new CElectricShock(ETag::eElectricShock);

	// 位置を取得
	CVector pos = GetThrowPos();// + CVector(0.0f, 10.0f, 0.0f);
	// 方向を取得
	CVector dir = GetThrowDir();// + CVector(0.0f, -1.0f, 0.0f);
	// 方向をランダムでブラす
	dir.X(dir.X() + Math::Rand(-FLAME_DIR_RAND, FLAME_DIR_RAND));
	dir.Y(dir.Y() + Math::Rand(-FLAME_DIR_RAND, FLAME_DIR_RAND));
	dir.Z(dir.Z() + Math::Rand(-FLAME_DIR_RAND, FLAME_DIR_RAND));
	dir.Normalize();
	// 位置、方向、移動速度を設定
	electricShock->Setup(pos, dir, FLAME_MOVE_SPEED);

	// 電撃のカラーを設定
	electricShock->SetColor(FLAME_COLOR);
	// 加算ブレンドにして、電撃が発光しているように見せる
	electricShock->SetBlendType(EBlend::eAdd);
	// 作成した雷のエフェクトをリストに追加
	mElectricShock.push_back(electricShock);
}

// 更新
void CElectricShockEffect::Update()
{
	// 電撃を発射していたら
	if (mIsThrowing)
	{
		// 経過時間に応じて、電撃を作成
		if (mElapsedTime >= THROW_INTERVAL)
		{
			CreateSlash();
			mElapsedTime -= THROW_INTERVAL;
		}
		mElapsedTime += Time::DeltaTime();
	}
	// 生成済みの電撃のエフェクトの削除処理
	auto itr = mElectricShock.begin();
	auto end = mElectricShock.end();
	while (itr != end)
	{
		CElectricShock* electricShock = *itr;
		// 削除フラグが立っていたら、削除
		if (electricShock->IsDeath())
		{
			itr = mElectricShock.erase(itr);
			electricShock->Kill();
		}
		else
		{
			itr++;
		}
	}
}