#ifndef CPARTICLE_H
#define CPARTICLE_H

#include "CBillBoard.h"
//�F
#define PARTICLE_COLOR 0.9f, 0.9f, 0.4f, 0.4f
//���� 10�t���[��
#define PARTICLE_LIFE 10
//�傫��
#define PARTICLE_SCALE 0.2, 0.2, 0.0f
//�ړ��̑���
#define PARTICLE_VELOCITY 0.025f
/*
�p�[�e�B�N���N���X
*/
class CParticle : public CBillBoard {
public:
	//�ړ��̌���
	CVector3 mVelocity;
	//�F
	CVector4 mColor;
	//����
	int mLife;
	//�R���X�g���N�^
	CParticle() {}
	CParticle(CTexture *texture
		, const CVector3& position
		, const CVector3& velocity
		, const CVector3& scale = CVector3(PARTICLE_SCALE)
		, const CVector4& color = CVector4(PARTICLE_COLOR)
		, int life = PARTICLE_LIFE);
	void Update();
	void Render();
};
/*
�p�[�e�B�N�������N���X
*/
class CEmitter {
public:
	//�摜
	CTexture mTexture;
	//���o��
	int mNums;
	//�ړ��̑���
	float mVelocity;
	//�傫��
	CVector3 mScale;
	//�F
	CVector4 mColor;
	//����
	int mLife;
	//�R���X�g���N�^
	CEmitter(){}
	CEmitter(char* texture
		, int nums
		, float velocity = PARTICLE_VELOCITY
		, const CVector3& scale = CVector3(PARTICLE_SCALE)
		, const CVector4& color = CVector4(PARTICLE_COLOR)
		, int life = PARTICLE_LIFE);
	//�p�[�e�B�N���𔭐�������
	void Emit(const CVector3& position);
};

#endif
