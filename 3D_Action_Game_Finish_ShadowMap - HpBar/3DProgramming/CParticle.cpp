#include "CParticle.h"
#include "stdlib.h"

CParticle::CParticle(CTexture *texture
	, const CVector3& position
	, const CVector3& velocity
	, const CVector3& scale
	, const CVector4& color
	, int life)
	: CBillBoard(position, scale)
	, mVelocity(velocity)
	, mLife(life)
{
	mColor = color;
	SetTexture(texture);
}

void CParticle::Update() {
	if (mLife < 0) {
		mEnabled = false;
		return;
	}
	mLife--;
	mPosition = mPosition + mVelocity;
}

void CParticle::Render() {
	if (mEnabled) {
		//���F���ݒ�F��
		if (mLife > PARTICLE_LIFE / 3)
			CBillBoard::mColor = CVector4(1.0f, 1.0f, 1.0f, 0.4f);
		else
			CBillBoard::mColor = mColor;
		CBillBoard::Render();
	}
}

CEmitter::CEmitter(char* texture
	, int nums
	, float velocity
	, const CVector3& scale
	, const CVector4& color
	, int life)
	: mNums(nums)
	, mVelocity(velocity)
	, mScale(scale)
	, mColor(color)
	, mLife(life)
{
	mTexture.load(texture);
}
//�p�[�e�B�N�����o
//position�F���o�ʒu
void CEmitter::Emit(const CVector3& position) {
	//mNums���쐬
	for (int i = 0; i < mNums; i++) {
		//�ړ����x�̐ݒ�
		CVector3 velocity((float)(rand() % 20 - 10) / 10
			, (float)(rand() % 20 - 10) / 10
			, (float)(rand() % 20 - 10) / 10);
		velocity = velocity.normalize();
		velocity = velocity * mVelocity;
		//�p�[�e�B�N������
		new CParticle(&mTexture, position, velocity,mScale, mColor, mLife);
	}
}

