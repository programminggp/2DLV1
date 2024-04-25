#include "CBillBoardImage.h"

// �R���X�g���N�^
CBillBoardImage::CBillBoardImage(std::string path, ETag tag, ETaskPauseType pause)
	: CBillBoard(tag, pause)
	, mpAnimData(nullptr)
	, mAnimNo(0)
	, mElapsedTime(0.0f)
{
	// �e�N�X�`���ǂݍ���
	mMaterial.LoadTexture("", path, false);
	CTexture* tex = mMaterial.Texture();

	CVector2 size;
	size.X(tex->Header().width / 256.0f);
	size.Y(tex->Header().height / 256.0f);
	SetSize(size);

	SetColor(CColor::white);

	// UV�ݒ�
	SetUV(CRect(0.0f, 0.0f, 1.0f, 1.0f));
}

// �f�X�g���N�^
CBillBoardImage::~CBillBoardImage()
{
}

// UV�ݒ�
void CBillBoardImage::SetUV(const CRect& uv)
{
	float l = uv.X();
	float t = uv.Y();
	float r = l + uv.W();
	float b = t + uv.H();

	mT[0].UV
	(
		CVector(r, t, 0.0f),
		CVector(l, b, 0.0f),
		CVector(r, b, 0.0f)
	);
	mT[1].UV
	(
		CVector(l, t, 0.0f),
		CVector(l, b, 0.0f),
		CVector(r, t, 0.0f)
	);
}

// �A�j���[�V�������Đ��ł��邩�ǂ���
bool CBillBoardImage::IsEnableAnim() const
{
	if (mpAnimData == nullptr) return false;
	if (mpAnimData->frames.size() == 0) return false;
	return true;
}

// �A�j���[�V�����f�[�^��ݒ�
void CBillBoardImage::SetAnimData(TexAnimData* animData)
{
	mpAnimData = animData;
	mAnimNo = 0;
	mElapsedTime = 0.0f;

	// �A�j���[�V�������L���ł���΁A
	// ��ԍŏ��̉摜��UV��ݒ�
	if (IsEnableAnim())
	{
		CRect uv = mMaterial.Texture()->CalcUV
		(
			mpAnimData->row,
			mpAnimData->col,
			0
		);
		SetUV(uv);

		CTexture* tex = mMaterial.Texture();
		CVector2 size;
		float ratio = (float)mpAnimData->col / mpAnimData->row;
		size.X(tex->Header().width / 256.0f);
		size.Y(tex->Header().height / 256.0f * ratio);
		SetSize(size);
	}
}

// �A�j���[�V�������I��������ǂ���
bool CBillBoardImage::IsEndAnim() const
{
	if (mpAnimData == nullptr) return true;
	int size = mpAnimData->frames.size();
	return mAnimNo == size;
}

// �X�V
void CBillBoardImage::Update()
{
	// �A�j���[�V�������L���ł����
	if (IsEnableAnim())
	{
		int size = mpAnimData->frames.size();
		if (mAnimNo < size)
		{
			TexAnimFrameData data = mpAnimData->frames[mAnimNo];
			// ���݂̉摜�̕\�����Ԃ𒴂�����
			if (mElapsedTime >= data.time)
			{
				// ���̉摜�֐؂�ւ�
				mElapsedTime -= data.time;

				mAnimNo++;
				if (mAnimNo >= size)
				{
					if (mpAnimData->loop)
					{
						mAnimNo -= size;
					}
					else
					{
						mAnimNo = size;
					}
				}
				CRect uv = mMaterial.Texture()->CalcUV
				(
					mpAnimData->row,
					mpAnimData->col,
					mAnimNo
				);
				SetUV(uv);
			}
			// �o�ߎ��Ԃ��v��
			mElapsedTime += Time::DeltaTime();
		}
	}

	CBillBoard::Update();
}

// �`��
void CBillBoardImage::Render()
{
	CBillBoard::Render();
}
