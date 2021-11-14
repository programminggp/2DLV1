#include "CRaceCourceA.h"
#include "CObj.h"
#include "CObjWall.h"
#include "CObjFloor.h"
#include "CRoadManager.h"
#include "CObjCheckPoint.h"
#include "CObjNonCol.h"
#include "CObjBoost.h"
#include "CObjGrass.h"
#include "CObjJumper.h"
#include "CSceneTitle.h"

void CRaceCourceA::Init(){
	//�V�[���̐ݒ�
	mScene = ERACE1;

	CSceneRace::Init();
	
	CVector StartPosVec = CVector(350.0f, -13.538f, -130.0f);//�X�^�[�g�ʒu�̊�_
	CVector StartPosVecs[ENEMYS_AMOUNT + 1];//�X�^�[�g�ʒu(�z��)
	for (int i = 0; i < LIST_SIZE; i++) {
		StartPosVecs[i] = StartPosVec + CVector(-0.1f*list[i], 0.0f, -80.0f*list[i]);
		if (list[i] % 2 == 1){
			StartPosVecs[i].mX -= 80.0f;
		}
		printf("%d, ",list[i]);
	}
	printf("\n");

	//�v���C���[�̐���
	mPlayer = new CPlayer();
	mPlayer->mpModel = &mCarWhite;

	//�v���C���[�̃��X�|�[������CheckPoint�̐ݒ�
	mPlayer->SetRespawnPoint(0, StartPosVecs[0], CVector(0.0f, 0.0f, 0.0f));
	//mPlayer->SetRespawnPoint(0, CVector(350.0f, -13.538f, -130.0f), CVector(0.0f, 0.0f, 0.0f));
	mPlayer->SetRespawnPoint(1, CVector(-80.0f, -13.538f, 2175.0f), CVector(0.0f, -55.0f, 0.0f));
	mPlayer->SetRespawnPoint(2, CVector(-1620.0f, -13.538f, 450.0f), CVector(0.0f, -175.0f, 0.0f));
	mPlayer->SetRespawnPoint(3, CVector(-1212.0f, -13.538f, -1616.0f), CVector(0.0f, 120.0f, 0.0f));
	mPlayer->GetReady();
	//�J�����̐���
	mCamRange = new CCameraRange();
	mCam = new CCameraPos();
	//�R�[�X�̐���//���ƕǂŕ������ď�������ʂ���
	//�R�[�X�S�̂̃T�C�Y����ݒ�
	float mtsize = 50.0f;
	float height = 2.0f;
	new CRoadManager(&mCource01, CVector(-360.0f, 5.0f - 33.0f, 230.0f), CVector(), CVector(mtsize, height, mtsize), mPlayer->mPosition, CVector(0.0f, 0.0f, 1.0f), 500.0f, 0.0f);
	//GP���[�h����œG����
	if (CSceneTitle::mMode == CSceneTitle::EMODE_GRANDPRIX){
		//�G�Ԃ̐���
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			mEnemys[i] = new CEnemy();
			if (i % 8 == 0){
				mEnemys[i]->mpModel = &mCarBlue;
			}
			else if (i % 8 == 1){
				mEnemys[i]->mpModel = &mCarPink;
			}
			else if (i % 8 == 2){
				mEnemys[i]->mpModel = &mCarRed;
			}
			else if (i % 8 == 3){
				mEnemys[i]->mpModel = &mCarGreen;
			}
			else if (i % 8 == 4){
				mEnemys[i]->mpModel = &mCarYellow;
			}
			else if (i % 8 == 5){
				mEnemys[i]->mpModel = &mCarBlack;
			}
			else if (i % 8 == 6){
				mEnemys[i]->mpModel = &mCarGray;
			}
			else if (i % 8 == 7){
				mEnemys[i]->mpModel = &mCarCyan;
			}
			//�����̔z�u���W��ݒ肷��
			mEnemys[i]->mPosition = CVector(StartPosVecs[i + 1]);
			mEnemys[i]->CCharacter::Update();
			if (i == 0){
				mEnemys[i]->mEnemyAI = CEnemy::ENEWBIE;
			}
		}
	}
	
	/*�����x�̍����������ɕ`�悷��*/
	//���Ԓn�_(1���Ɣ��肳���ɂ͏��Ԓʂ�ɒʉ߂���K�v������)
	new CObjCheckPoint(&mCheckPoint, CVector(50.0f, 15.0f, 2500.0f), CVector(-90.0f, 0.0f, -50.0f), CVector(2000.0f, 31.0f, 255.0f), 1);
	new CObjCheckPoint(&mCheckPoint, CVector(-1800.0f, 15.0f, 20.0f), CVector(-90.0f, 180.0f, 0.0f), CVector(750.0f, 31.0f, 255.0f), 2);
	new CObjCheckPoint(&mCheckPoint, CVector(-1100.0f, 15.0f, -2000.0f), CVector(-90.0f, 0.0f, 110.0f), CVector(750.0f, 31.0f, 255.0f), 3);
	//�S�[���n�_
	new CObjCheckPoint(&mCheckPoint, CVector(600.0f, -30.0f, 1.9f), CVector(), CVector(800.0f, 100.0f, 10.0f), 9);

	//�R�[�X�̐���
	//�Ő��̐���(�ʍs�����x�ቺ)
	new CObjGrass(&mGrass01, CVector(-360.0f, 5.0f - 33.0f, 230.0f), CVector(), CVector(50.0f, 2.0f, 50.0f));
	//�R�[�X�ɍ�̔z�u(�ǈ���)
	new CObjFloor(&mFenceTop, CVector(-360.0f, -70.0f - 35.0f, 230.0f), CVector(), CVector(50.0f, 5.5f + 1.5f, 50.0f));
	new CObjWall(&mFenceSide, CVector(-360.0f, -70.0f - 35.0f, 230.0f), CVector(), CVector(50.0f, 5.5f + 1.5f, 50.0f));
	//���H�ƎŐ��̋��ڂ̃^�C���𐶐�(�����蔻�薳��)
	new CObjNonCol(&mCurb01, CVector(-360.0f, 5.0f - 33.0f + 0.05f, 230.0f), CVector(), CVector(50.0f, 2.0f, 50.0f));
	
	//���E���^�C���ŃS�[������
	new CObjNonCol(&mGoalTile01, CVector(170.0f + 590.0f + 0.0f, -13.1f + 5.5f, -10.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.0f, 10.0f));
	new CObjNonCol(&mGoalTile01, CVector(170.0f + 190.0f + 0.0f, -13.1f + 5.5f, -10.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 1.0f, 10.0f));
	//�S�[��(�Q�[�g��)
	new CObjNonCol(&mGoalGate, CVector(170.0f - 15.0f + 410.0f, 110.0f + 200.0f - 20.0f - 10.0f, -14.0f), CVector(90.0f, 0.0f, 0.0f), CVector(20.0f, 4.9f, 20.0f), false);//���^�C��
	
	//�Q�[�g�̒�����
	new CObjWall(&mPole, CVector(170.0f + 20.0f * -1 + 5.0f + 5.0f, -13.1f - 10.0f, -10.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 174.0f, 10.0f));
	new CObjWall(&mPole, CVector(170.0f + 20.0f * 40 + 5.0f - 5.0f, -13.1f - 10.0f, -10.0f), CVector(0.0f, 0.0f, 0.0f), CVector(10.0f, 174.0, 10.0f));
	//������
	new CObjBoost(&mDashBoard, CVector(234.0f, -13.1f + 3.0f, -980.0f), CVector(0.0f, 180.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));
	new CObjBoost(&mDashBoard, CVector(-1500.0f, -13.1f + 3.0f, -50.0f), CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));
	//�W�����v��
	new CObjJumper(&mJumper01, CVector(240.0f, -13.1f + 3.0f, 1110.0f), CVector(-30.0f, 0.0f, 0.0f), CVector(77.0f, 5.0f, 50.0f));

	//�D��x�ύX
	CTaskManager::Get()->ChangePriority(mPlayer, 15);
	if (CSceneTitle::mMode == CSceneTitle::EMODE_GRANDPRIX){
		for (int i = 0; i < ENEMYS_AMOUNT; i++){
			CTaskManager::Get()->ChangePriority(mEnemys[i], 15);
		}		
	}
	//�G�Ԃ̃J���[���̏o��
	PutCPUColor();
}
void CRaceCourceA::Update(){
	CSceneRace::Update();
}