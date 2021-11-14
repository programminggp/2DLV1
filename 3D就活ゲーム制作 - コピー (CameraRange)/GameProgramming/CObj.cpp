#include "CObj.h"
#include "CPlayer.h"
#include "CTaskManager.h"

#define DOOR_RANGEOFMOTION 90 //�h�A�̉���
#define DOOR_OPENSPEED 2 //�h�A�̊J�����x
#define ROLLINGSPEED 1.0f //��]���鑫��̉�]���x

#define G (9.8f / 120.0f)//�d�͉����x//60.0f

int CObj::mObjectNum = 0;//���݂̃I�u�W�F�̐�
int CObj::mObject_Limit = GROUNDS_LIMIT;//�o�����Ƃ��ł���I�u�W�F�̐�
CObj *CObj::mpGrounds[GROUNDS_LIMIT];

//�R���X�g���N�^
//model:���f���̃|�C���^ position:�ʒu rotation:��] scale:�g�k hascollider:�R���C�_�̐����̗L��(�ݒ肪�Ȃ���ΗL)
CObj::CObj(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale, bool hascollider, bool hasshadow)
:mpCollider(0)
{
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;

	if (hascollider == false){
		//�����蔻��𐶐����Ȃ�
		//�����蔻��̐���}����قǁA�������y�ʉ��ł���
	}
	else{
		CCharacter::Update();
		//���f���̎O�p�`�̐����A�R���C�_�̔z����쐬���܂�
		mpCollider = new CCollider[model->mTriangles.size()];
		for (unsigned int i = 0; i < model->mTriangles.size(); i++){
			//�R���C�_���O�p�`�R���C�_�Őݒ肵�Ă����܂�
			mpCollider[i].SetTriangle(this,
				model->mTriangles[i].mV[0],
				model->mTriangles[i].mV[1],
				model->mTriangles[i].mV[2]);
			mpCollider[i].ChangePriority();
		}
	}

	//�e������or�����Ȃ����̂̏���
	if (hasshadow){
		mpGrounds[mObjectNum] = this;
		mObjectNum++;
	}
	else{

	}
	
}
//�f�X�g���N�^
CObj::~CObj(){
	//�R���C�_������΍폜
	if (mpCollider){
		//delete[] �z����폜
		delete[] mpCollider;
	}
}

void CObj::Update(){
	CCharacter::Update();
}