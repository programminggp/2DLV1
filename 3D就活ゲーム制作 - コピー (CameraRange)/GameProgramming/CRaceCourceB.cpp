#include "CRaceCourceB.h"
#include "CObj.h"
#include "CObjWall.h"
#include "CObjFloor.h"
#include "CObjCheckPoint.h"
#include "CObjNonCol.h"
#include "CObjJumper.h"
#include "CSceneTitle.h"

void CRaceCourceB::Init(){
	//�V�[���̐ݒ�
	mScene = ERACE2;

	CSceneRace::Init();

	//�G�̃|�C���g(�ړI�n)�̐ݒ�
	if (CSceneTitle::mDifficulty == 1){//��Փx�FEASY
		CEnemy::mPointSize = 17;//�|�C���g���̐ݒ�
		CEnemy::mPoint = new CPoint(CVector(2377.0f, 30.0f, -753.0f), 100.0f * 2);
		CEnemy::mPoint2 = new CPoint(CVector(3068.0f, 30.0f, -355.0f), 100.0f * 2);
		CEnemy::mPoint3 = new CPoint(CVector(3763.0f, 30.0f, 510.0f), 100.0f * 2);
		CEnemy::mPoint4 = new CPoint(CVector(3240.0f, 30.0f, 2207.0f), 100.0f * 2);
		CEnemy::mPoint5 = new CPoint(CVector(1719.0f, 30.0f, 3250.0f), 100.0f * 2);
		CEnemy::mPoint6 = new CPoint(CVector(1212.0f, 30.0f, 4516.0f), 100.0f * 2);
		CEnemy::mPoint7 = new CPoint(CVector(463.0f, 30.0f, 5010.0f), 100.0f * 2);
		CEnemy::mPoint8 = new CPoint(CVector(-700.0f, 30.0f, 4935.0f), 100.0f * 2);
		CEnemy::mPoint9 = new CPoint(CVector(-1645.0f, 30.0f, 3612.0f), 100.0f * 2);
		CEnemy::mPoint10 = new CPoint(CVector(-2528.0f, 30.0f, 1832.0f), 100.0f * 2);
		CEnemy::mPoint11 = new CPoint(CVector(-3242.0f, 30.0f, 1253.0f), 100.0f * 2);
		CEnemy::mPoint12 = new CPoint(CVector(-2652.0f, 30.0f, 113.0f), 100.0f * 2);
		CEnemy::mPoint13 = new CPoint(CVector(-1500.0f, 30.0f, -80.0f), 100.0f * 2);
		CEnemy::mPoint14 = new CPoint(CVector(-721.0f, 30.0f, -1926.0f), 100.0f * 2);
		CEnemy::mPoint15 = new CPoint(CVector(529.0f, 30.0f, -3565.0f), 100.0f);
		CEnemy::mPoint16 = new CPoint(CVector(1317.0f, 30.0f, -3865.0f), 100.0f * 2);
		CEnemy::mPoint17 = new CPoint(CVector(2128.0f, 30.0f, -3026.0f), 100.0f * 2);
	}
	else if (CSceneTitle::mDifficulty == 2){//��Փx�FNORMAL
		CEnemy::mPointSize = 17;//�|�C���g���̐ݒ�
		CEnemy::mPoint = new CPoint(CVector(2377.0f, 30.0f, -753.0f), 100.0f * 2);
		CEnemy::mPoint2 = new CPoint(CVector(3068.0f, 30.0f, -355.0f), 100.0f * 2);
		CEnemy::mPoint3 = new CPoint(CVector(3763.0f, 30.0f, 510.0f), 100.0f * 2);
		CEnemy::mPoint4 = new CPoint(CVector(3240.0f, 30.0f, 2207.0f), 100.0f * 2);
		CEnemy::mPoint5 = new CPoint(CVector(1719.0f, 30.0f, 3250.0f), 100.0f * 2);
		CEnemy::mPoint6 = new CPoint(CVector(1212.0f, 30.0f, 4516.0f), 100.0f * 2);
		CEnemy::mPoint7 = new CPoint(CVector(463.0f, 30.0f, 5010.0f), 100.0f * 2);
		CEnemy::mPoint8 = new CPoint(CVector(-700.0f, 30.0f, 4935.0f), 100.0f * 2);
		CEnemy::mPoint9 = new CPoint(CVector(-1645.0f, 30.0f, 3612.0f), 100.0f * 2);
		CEnemy::mPoint10 = new CPoint(CVector(-2528.0f, 30.0f, 1832.0f), 100.0f * 2);
		CEnemy::mPoint11= new CPoint(CVector(-3242.0f, 30.0f, 1253.0f), 100.0f * 2);
		CEnemy::mPoint12 = new CPoint(CVector(-2652.0f, 30.0f, 113.0f), 100.0f * 2);
		CEnemy::mPoint13 = new CPoint(CVector(-1500.0f, 30.0f, -80.0f), 100.0f * 2);
		CEnemy::mPoint14 = new CPoint(CVector(-721.0f, 30.0f, -1926.0f), 100.0f * 2);
		CEnemy::mPoint15 = new CPoint(CVector(529.0f, 30.0f, -3565.0f), 100.0f);
		CEnemy::mPoint16 = new CPoint(CVector(1317.0f, 30.0f, -3865.0f), 100.0f * 2);
		CEnemy::mPoint17 = new CPoint(CVector(2128.0f, 30.0f, -3026.0f), 100.0f * 2);
	}
	else if (CSceneTitle::mDifficulty == 3){//��Փx�FHARD
		CEnemy::mPointSize = 17;//�|�C���g���̐ݒ�
		CEnemy::mPoint = new CPoint(CVector(2377.0f, 30.0f, -753.0f), 100.0f * 2);
		CEnemy::mPoint2 = new CPoint(CVector(3068.0f, 30.0f, -355.0f), 100.0f * 2);
		CEnemy::mPoint3 = new CPoint(CVector(3763.0f, 30.0f, 510.0f), 100.0f * 2);
		CEnemy::mPoint4 = new CPoint(CVector(3240.0f, 30.0f, 2207.0f), 100.0f * 2);
		CEnemy::mPoint5 = new CPoint(CVector(1719.0f, 30.0f, 3250.0f), 100.0f * 2);
		CEnemy::mPoint6 = new CPoint(CVector(1212.0f, 30.0f, 4516.0f), 100.0f * 2);
		CEnemy::mPoint7 = new CPoint(CVector(463.0f, 30.0f, 5010.0f), 100.0f * 2);
		CEnemy::mPoint8 = new CPoint(CVector(-700.0f, 30.0f, 4935.0f), 100.0f * 2);
		CEnemy::mPoint9 = new CPoint(CVector(-1645.0f, 30.0f, 3612.0f), 100.0f * 2);
		CEnemy::mPoint10 = new CPoint(CVector(-2528.0f, 30.0f, 1832.0f), 100.0f * 2);
		CEnemy::mPoint11 = new CPoint(CVector(-3242.0f, 30.0f, 1253.0f), 100.0f * 2);
		CEnemy::mPoint12 = new CPoint(CVector(-2652.0f, 30.0f, 113.0f), 100.0f * 2);
		CEnemy::mPoint13 = new CPoint(CVector(-1500.0f, 30.0f, -80.0f), 100.0f * 2);
		CEnemy::mPoint14 = new CPoint(CVector(-721.0f, 30.0f, -1926.0f), 100.0f * 2);
		CEnemy::mPoint15 = new CPoint(CVector(529.0f, 30.0f, -3565.0f), 100.0f);
		CEnemy::mPoint16 = new CPoint(CVector(1317.0f, 30.0f, -3865.0f), 100.0f * 2);
		CEnemy::mPoint17 = new CPoint(CVector(2128.0f, 30.0f, -3026.0f), 100.0f * 2);
	}
	else{
		//�B��HARD�̗\��
	}
	//�v���C���[�̐���
	mPlayer = new CPlayer();
	mPlayer->mpModel = &mCarWhite;
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
		/*mStartPoint[0] = 2222.0f;  mStartPoint[1] = -13.538f;  mStartPoint[2] = -2510.0f;
		mStartRotation = 0.0f;*/
		//�����̔z�u���W��ݒ肷��
		mEnemys[i]->mPosition = CVector(2222.0f, -13.538f, -2510.0f - 30.0f - 80.0f*i);
		if (i % 2 == 0){
			mEnemys[i]->mPosition.mX -= 80.0f;
		}
		mEnemys[i]->CCharacter::Update();
	}

	/* �������x�̍����������ɕ`�悷�� */
	//���Ԓn�_(���ɒʂ�Ȃ���1���������ƂɂȂ�Ȃ����A���Ԃ��΂��Ă������Ȃ�)
	new CObjCheckPoint(&mCheckPoint, CVector(2893.0f, -100.0f, 2473.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 200.0f, 220.0f), 1);
	new CObjCheckPoint(&mCheckPoint, CVector(-1020.0f, -100.0f, 4594.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 200.0f, 220.0f), 2);
	new CObjCheckPoint(&mCheckPoint, CVector(-1277.0f, -100.0f, -448.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 200.0f, 220.0f), 3);
	//�R�[�X�̐���
	new CObjFloor(&mCource02Road, CVector(0.0f, -220.0f, 0.0f), CVector(0.0f, -139.3f, 0.0f), CVector(42.0f, 13.5f, 42.0f));
	new CObjWall(&mCource02Wall, CVector(0.0f, -220.0f, 0.0f), CVector(0.0f, -139.3f, 0.0f), CVector(42.0f, 13.5f, 42.0f));
	new CObjJumper(&mCource02Jump, CVector(0.0f, -220.0f, 0.0f), CVector(0.0f, -139.3f, 0.0f), CVector(42.0f, 13.5f, 42.0f));
	//�S�[���n�_
	new CObjNonCol(&mMiniGoal, CVector(2315.0f, -1.0f, -2300.0f), CVector(0.0f, 0.0f, 0.0f), CVector(4.2f, 10.0f, 4.2f));
	new CObjNonCol(&mMiniGoal, CVector(2107.0f, -1.0f - 0.05f, -2300.0f), CVector(0.0f, 180.0f, 0.0f), CVector(4.2f, 10.0f, 4.2f));

	//�D��x�ύX
	CTaskManager::Get()->ChangePriority(mPlayer, 15);
	for (int i = 0; i < ENEMYS_AMOUNT; i++){
		CTaskManager::Get()->ChangePriority(mEnemys[i], 15);
	}
}
void CRaceCourceB::Update(){
	CSceneRace::Update();
}