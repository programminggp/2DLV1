#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include "CModelX.h"
#include "CMatrix.h"
#include "CCharacter.h"

class CXCharacter : public CCharacter {
public:
	CModelX* mpModel;	//���f���f�[�^
	int mAnimationIndex;	//�A�j���[�V�����ԍ�
	bool mAnimationLoopFlg;	//true:�A�j���[�V�������J��Ԃ�
	float mAnimationFrame; //�A�j���[�V�����̍Đ��t���[��
	float mAnimationFrameSize;//�A�j���[�V�����̍Đ��t���[����
	CMatrix* mpCombinedMatrix;	//�����s��ޔ�
	CXCharacter();
	~CXCharacter()
	{
		SAFE_DELETE_ARRAY(mpCombinedMatrix);
	}
	//����������
	void Init(CModelX* model);
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(int index, bool loop, float framesize);
	//�X�V����
	void Update(CMatrix& m);
	void Update();
	//�`�揈��
	void Render();
};

#endif
