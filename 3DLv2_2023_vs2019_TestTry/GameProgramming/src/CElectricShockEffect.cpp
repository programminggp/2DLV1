#include "CElectricShockEffect.h"
#include "CElectricShock.h"
#include "Maths.h"

// �d���̊Ԋu����
#define THROW_INTERVAL 0.4f
// �d���̕����̃u����
#define FLAME_DIR_RAND 0.02f
// �d���̈ړ����x
#define FLAME_MOVE_SPEED 100.0f
// �d���̐F
#define FLAME_COLOR CColor(1.0f, 1.0f, 0.0f)

// �R���X�g���N�^
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

// �f�X�g���N�^
CElectricShockEffect::~CElectricShockEffect()
{
	for (CElectricShock* electricShock :mElectricShock)
	{
		electricShock->Kill();
	}
}

// �d�����J�n
void CElectricShockEffect::Start()
{
	mIsThrowing = true;
	mElapsedTime = 0.0f;
}

// �d�����~
void CElectricShockEffect::Stop()
{
	mIsThrowing = false;
}

// �d�������Ă��邩�ǂ���
bool CElectricShockEffect::IsThrowing() const
{
	return mIsThrowing;
}

// �d�����̃I�t�Z�b�g�ʒu��ݒ�
void CElectricShockEffect::SetThrowOffsetPos(const CVector& pos)
{
	mThrowOffsetPos = pos;
}

// �d�����̃I�t�Z�b�g��]�l��ݒ�
void CElectricShockEffect::SetThrowOffsetRot(const CMatrix& rot)
{
	mThrowOffsetRot = rot;
}

// �d���̈ʒu���擾
CVector CElectricShockEffect::GetThrowPos() const
{
	// �A�^�b�`����s�񂪐ݒ肳��Ă���ꍇ�́A�s��̍��W��Ԃ�
	if (mpAttachMtx != nullptr)
	{
		CVector pos = mpAttachMtx->Position();
		pos += mpAttachMtx->VectorX() * mThrowOffsetPos.X()
			+ mpAttachMtx->VectorY() * mThrowOffsetPos.Y()
			+ mpAttachMtx->VectorZ() * mThrowOffsetPos.Z();
		return pos;
	}
	// �����傪�ݒ肳��Ă���ꍇ�́A������̍��W��Ԃ�
	else if (mpOwner != nullptr)
	{
		return mpOwner->Position() + (mpOwner->Rotation() * mThrowOffsetPos);
	}

	return CVector::zero;
}

// �d���̕������擾
CVector CElectricShockEffect::GetThrowDir() const
{
	// �A�^�b�`����s�񂪐ݒ肳��Ă���ꍇ�́A�s��̐��ʕ����x�N�g����Ԃ�
	if (mpAttachMtx != nullptr)
	{
		return mThrowOffsetRot * mpAttachMtx->VectorZ();
	}
	// �����傪�ݒ肳��Ă���ꍇ�́A������̐��ʕ����x�N�g����Ԃ�
	else if (mpOwner != nullptr)
	{
		return mThrowOffsetRot * mpOwner->VectorZ();
	}

	return CVector::forward;
}

// �d�����쐬
void CElectricShockEffect::CreateSlash()
{
	// �d�����쐬
	CElectricShock* electricShock = new CElectricShock(ETag::eElectricShock);

	// �ʒu���擾
	CVector pos = GetThrowPos();// + CVector(0.0f, 10.0f, 0.0f);
	// �������擾
	CVector dir = GetThrowDir();// + CVector(0.0f, -1.0f, 0.0f);
	// �����������_���Ńu����
	dir.X(dir.X() + Math::Rand(-FLAME_DIR_RAND, FLAME_DIR_RAND));
	dir.Y(dir.Y() + Math::Rand(-FLAME_DIR_RAND, FLAME_DIR_RAND));
	dir.Z(dir.Z() + Math::Rand(-FLAME_DIR_RAND, FLAME_DIR_RAND));
	dir.Normalize();
	// �ʒu�A�����A�ړ����x��ݒ�
	electricShock->Setup(pos, dir, FLAME_MOVE_SPEED);

	// �d���̃J���[��ݒ�
	electricShock->SetColor(FLAME_COLOR);
	// ���Z�u�����h�ɂ��āA�d�����������Ă���悤�Ɍ�����
	electricShock->SetBlendType(EBlend::eAdd);
	// �쐬�������̃G�t�F�N�g�����X�g�ɒǉ�
	mElectricShock.push_back(electricShock);
}

// �X�V
void CElectricShockEffect::Update()
{
	// �d���𔭎˂��Ă�����
	if (mIsThrowing)
	{
		// �o�ߎ��Ԃɉ����āA�d�����쐬
		if (mElapsedTime >= THROW_INTERVAL)
		{
			CreateSlash();
			mElapsedTime -= THROW_INTERVAL;
		}
		mElapsedTime += Time::DeltaTime();
	}
	// �����ς݂̓d���̃G�t�F�N�g�̍폜����
	auto itr = mElectricShock.begin();
	auto end = mElectricShock.end();
	while (itr != end)
	{
		CElectricShock* electricShock = *itr;
		// �폜�t���O�������Ă�����A�폜
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