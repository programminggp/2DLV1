#ifndef CSCENECHECK_H
#define CSCENECHECK_H
#include "CScene.h"
#include "CModel.h"
#include "CCameraRange.h"
#include "CCameraPos.h"

#include "CObjFloor.h"


/*
�Q�[���̃V�[��
*/
class CSceneCheck : public CScene {
private:
	CVector mEye;
	CVector mCameraRotation;

protected:

	CModel mCource01;//�R�[�X01

	CCameraRange *mCamRange;
	CCameraPos *mCam;

public:
	//���̃V�[���̎擾
	EScene GetNextScene();

	~CSceneCheck();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();

};
#endif
