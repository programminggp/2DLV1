#ifndef CXPLAYER_H
#define CXPLAYER_H

#include"CXCharacter.h"
#include"CCollider.h"
#include"CModelX.h"
#include"CColliderCapsule.h"

class CXPlayer :public CXCharacter {
public:
	//�X�V����
	void Update();
	CXPlayer();
	void Init(CModelX* model);
	void TaskCollision();
	void Collision(CCollider* m, CCollider* o);
	static CXPlayer* Get();
	static bool BattleSwitch;  //�U���؂�ւ�
	void Render();
private:
	//�R���C�_�錾
	CCollider mColSphereShield; //��
	CCollider mColSphereSword; //��
	CColliderCapsule mColCapBody; //����
	CCollider mCore; //�R�A
	CModel mMagicRingRed; //���@�w
	CMatrix MagicRingRotation;
	int StandCount; //�ҋ@��ԃJ�E���g
	/*int SlashCount1;
	int SlashCount2;
	int SlashCount3;*/
    int PlayerHp;  //�̗�
	int SMagicCount;  //�P�̖��@�Ԋu
	int AMagicCount;  //�͈͖��@�Ԋu
	int MagicWait;  //�ҋ@����
	int MagicRingTime;
	static CXPlayer* spInstance;
	

	CVector mScale; //�g��k���{��
	bool mPushFlg;
	float mOldMousePosX;
	
};

#endif // !CXPLAYER_H

