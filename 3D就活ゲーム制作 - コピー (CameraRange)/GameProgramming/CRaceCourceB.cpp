#include "CRaceCourceB.h"
#include "CObj.h"
#include "CObjWall.h"
#include "CObjFloor.h"
#include "CRoadManager.h"
#include "CObjCheckPoint.h"
#include "CObjNonCol.h"
#include "CObjJumper.h"
#include "CSceneTitle.h"

void CRaceCourceB::Init(){
	//�V�[���̐ݒ�
	mScene = ERACE2;

	CSceneRace::Init();

	CVector StartPosVec = CVector(2436.0f, -10.0f, -2570.0f);//�X�^�[�g�ʒu�̊�_
	CVector StartPosVecs[ENEMYS_AMOUNT + 1];//�X�^�[�g�ʒu(�z��)
	for (int i = 0; i < LIST_SIZE; i++) {
		StartPosVecs[i] = StartPosVec + CVector(-0.1f*list[i], 0.0f, -80.0f*list[i]);
		if (list[i] % 2 == 1){
			StartPosVecs[i].mX -= 80.0f;
		}
	}
	
	//�v���C���[�̐���
	mPlayer = new CPlayer();
	mPlayer->mpModel = &mCarWhite;
	//�v���C���[�̃��X�|�[������CheckPoint�̐ݒ�
	mPlayer->SetRespawnPoint(0, StartPosVecs[0], CVector());
	mPlayer->SetRespawnPoint(1, CVector(3175.0f, -10.0f, 2713.0f), CVector(0.0f, -55.0f, 0.0f));
	mPlayer->SetRespawnPoint(2, CVector(-1120.0f, -10.0f, 5000.0f), CVector(0.0f, -175.0f, 0.0f));
	mPlayer->SetRespawnPoint(3, CVector(-1400.0f, -10.0f, -492.0f), CVector(0.0f, 120.0f, 0.0f));
	mPlayer->GetReady();
	//�J�����̐���
	mCamRange = new CCameraRange();
	mCam = new CCameraPos();

	//�R�[�X�S�̂̃T�C�Y����ݒ�
	float mtsize = 42.0f*1.1f;
	float height = 13.5f;
	new CRoadManager(&mCource02Road, CVector(0.0f, -220.0f, 0.0f), CVector(0.0f, -139.3f, 0.0f), CVector(mtsize, height, mtsize), mPlayer->mPosition, CVector(0.0f, 0.0f, 1.0f), 120.0f, 0.0f);
	
	//GP���[�h�̂ݓG�����������
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
			mEnemys[i]->mPosition = CVector(2444.0f, -13.538f, -2650.0f - 80.0f*i);
			if (i % 2 == 0){
				mEnemys[i]->mPosition.mX -= 80.0f;
			}
			mEnemys[i]->mPosition = CVector(StartPosVecs[i + 1]);
			mEnemys[i]->CCharacter::Update();
		}
	}
	

	/* �������x�̍����������ɕ`�悷�� */
	//���Ԓn�_(���Ԃɒʂ�Ȃ���1���ƃJ�E���g����Ȃ�)
	new CObjCheckPoint(&mCheckPoint, CVector(3175.0f, -100.0f, 2713.0f), CVector(0.0f, 0.0f, 0.0f), CVector(240.0f, 200.0f, 240.0f), 1);
	new CObjCheckPoint(&mCheckPoint, CVector(-1120.0f, -100.0f, 5000.0f), CVector(0.0f, 0.0f, 0.0f), CVector(240.0f, 200.0f, 240.0f), 2);
	new CObjCheckPoint(&mCheckPoint, CVector(-1400.0f, -100.0f, -492.0f), CVector(0.0f, 0.0f, 0.0f), CVector(240.0f, 200.0f, 240.0f), 3);
	//�S�[���n�_
	new CObjCheckPoint(&mCheckPoint, CVector(2436.0f, -100.0f, -2530.0f), CVector(), CVector(350.0f, 150.0f, 30.0f), 9);

	//�R�[�X�̐���	
	new CObjWall(&mCource02Wall, CVector(0.0f, -220.0f, 0.0f), CVector(0.0f, -139.3f, 0.0f), CVector(mtsize, height, mtsize));
	new CObjJumper(&mCource02Jump, CVector(0.0f, -220.0f, 0.0f), CVector(0.0f, -139.3f, 0.0f), CVector(mtsize, height, mtsize));
	//�S�[���n�_�̃^�C��
	new CObjNonCol(&mMiniGoal, CVector(2546.5f, -1.0f, -2530.0f), CVector(0.0f, 0.0f, 0.0f), CVector(4.6f, 10.0f, 4.6f));
	new CObjNonCol(&mMiniGoal, CVector(2317.7f, -1.0f - 0.05f, -2530.0f), CVector(0.0f, 180.0f, 0.0f), CVector(4.6f, 10.0f, 4.6f));

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
void CRaceCourceB::Update(){
	CSceneRace::Update();
}