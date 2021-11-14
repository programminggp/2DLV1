#ifndef COBJ_H
#define COBJ_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"

#define GROUNDS_LIMIT 128//�����ł���I�u�W�F���̌��E�l

class CObj :public CCharacter{
public:
	//�R���C�_�̒ǉ�
	CCollider *mpCollider;
	//�R���X�g���N�^�ŏ����ݒ�
	CObj(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale, bool hascollider = true, bool hasshadow = true);
	~CObj();

	void Update();

	static int mObjectNum;//�I�u�W�F�̔ԍ�(���������I�u�W�F�̑����ɂ��Ȃ�)
	static int mObject_Limit;//�����ł���I�u�W�F���̌��E�l
	static CObj *mpGrounds[GROUNDS_LIMIT];
};

#endif