#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
//
#include "CText.h"

#include "CTransform.h"
#include "CCollider.h"
#include "CTaskManager.h"
#include "CModel.h"

#define TASK_LINE 10

class CField : public CTransform
{
public:
	void Load(char* obj, char* mtl);
	void Render();
	void Collision(CCollider*);
private:
	CModel mModelField;
//	CCollisionManager2 mCollision;
};




/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {

	static CField sField;

	CText mFont;

public:
	static CField& Field();

	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
};

#endif
