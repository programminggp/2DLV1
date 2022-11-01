#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include "CModelX.h"
#include "CMatrix.h"
#include "CCharacter.h"

class CXCharacter : public CCharacter {
public:
	virtual ~CXCharacter() {
		SAFE_DELETE_ARRAY(mpCombinedMatrix);
	}
	void Update();
	CXCharacter();
	//����������
	void Init(CModelX* model);
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(int index, bool loop, float framesize);
	//�X�V����
	void Update(CMatrix& m);
	//�`�揈��
	void Render();
	//�A�j���[�V�����̍Đ��I������
	//true:�I���@false:�Đ���
	bool IsAnimationFinished();
	int AnimationIndex(); //�A�j���[�V�����ԍ��̎擾
protected:
	CMatrix* mpCombinedMatrix;	//�����s��ޔ�
	CModelX* mpModel;	//���f���f�[�^
	int mAnimationIndex;	//�A�j���[�V�����ԍ�
	bool mAnimationLoopFlg;	//true:�A�j���[�V�������J��Ԃ�
	float mAnimationFrame; //�A�j���[�V�����̍Đ��t���[��
	float mAnimationFrameSize;//�A�j���[�V�����̍Đ��t���[����
};

#endif
