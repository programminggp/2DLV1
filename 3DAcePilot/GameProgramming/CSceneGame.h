#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
//22
#include "CPlayer.h"
//?
#include "CMap.h"
//
#include "CAirBase.h"
//
#include "CPoint.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
public:
	//
	CAirBase *mpAirBase;
	//�L�����N�^�̍쐬
//	CCharacter Character;
	CPlayer Player;
//	CMap mMap;//�}�b�v�̃C���X�^���X
	CPoint *mpEnemyPoint;

	~CSceneGame();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();

	//2D�`��X�^�[�g
	//Start2D(�����W, �E���W, �����W, ����W)
	void Start2D(float left, float right, float bottom, float top);
	//2D�`��I��
	void End2D();
	//�~�j�}�b�v�`��
	void RenderMiniMap();
};

#endif
