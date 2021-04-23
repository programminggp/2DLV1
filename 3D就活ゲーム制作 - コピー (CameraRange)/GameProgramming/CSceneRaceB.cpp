#include "CSceneRaceB.h"
#include "CSceneTitle.h"
#include "CObj.h"

void CSceneRaceB::Init() {
	//�e�N���X�̏������������Ă�
	CSceneRace::Init();

	/* �G�Ԃ̏��� */
	if (CSceneTitle::mDifficulty == 1){//��Փx�FEASY
		CEnemy::mPointSize = 6;//�|�C���g���̐ݒ�
		CEnemy::mPoint = new CPoint(CVector(413.0f, 30.0f, 1300.0f), 100.0f * 2 * 4);
		CEnemy::mPoint2 = new CPoint(CVector(258.0f, 30.0f, 2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint3 = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), 100.0f * 2 * 4);
		CEnemy::mPoint4 = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), 100.0f * 2 * 4);
		CEnemy::mPoint5 = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint6 = new CPoint(CVector(340.0f, 30.0f, -1182.0f), 100.0f * 2 * 4);
	}
	else if (CSceneTitle::mDifficulty == 2){//��Փx�FNORMAL
		//���݁A���̐ݒ�
		CEnemy::mPointSize = 12;//�|�C���g���̐ݒ�
		CEnemy::mPoint = new CPoint(CVector(413.0f, 30.0f, 1300.0f), 100.0f * 2 * 4);
		CEnemy::mPoint2 = new CPoint(CVector(258.0f, 30.0f, 2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint3 = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), 100.0f * 2 * 4);
		CEnemy::mPoint4 = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), 100.0f * 2 * 4);
		CEnemy::mPoint5 = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint6 = new CPoint(CVector(340.0f, 30.0f, -1182.0f), 100.0f * 2 * 4);
		CEnemy::mPoint7 = new CPoint(CVector(413.0f, 30.0f, 1300.0f), 100.0f * 2 * 4);
		CEnemy::mPoint8 = new CPoint(CVector(258.0f, 30.0f, 2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint9 = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), 100.0f * 2 * 4);
		CEnemy::mPoint10 = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), 100.0f * 2 * 4);
		CEnemy::mPoint11 = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint12 = new CPoint(CVector(340.0f, 30.0f, -1182.0f), 100.0f * 2 * 4);
	}
	else if (CSceneTitle::mDifficulty == 3){//��Փx�FHARD
		//���݁A���̐ݒ�
		CEnemy::mPointSize = 12;//�|�C���g���̐ݒ�
		CEnemy::mPoint = new CPoint(CVector(413.0f, 30.0f, 1300.0f), 100.0f * 2 * 4);
		CEnemy::mPoint2 = new CPoint(CVector(258.0f, 30.0f, 2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint3 = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), 100.0f * 2 * 4);
		CEnemy::mPoint4 = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), 100.0f * 2 * 4);
		CEnemy::mPoint5 = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint6 = new CPoint(CVector(340.0f, 30.0f, -1182.0f), 100.0f * 2 * 4);
		CEnemy::mPoint7 = new CPoint(CVector(413.0f, 30.0f, 1300.0f), 100.0f * 2 * 4);
		CEnemy::mPoint8 = new CPoint(CVector(258.0f, 30.0f, 2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint9 = new CPoint(CVector(-1350.0f, 30.0f, 2150.0f), 100.0f * 2 * 4);
		CEnemy::mPoint10 = new CPoint(CVector(-1601.0f, 30.0f, -1702.0f), 100.0f * 2 * 4);
		CEnemy::mPoint11 = new CPoint(CVector(-500.0f, 30.0f, -2000.0f), 100.0f * 2 * 4);
		CEnemy::mPoint12 = new CPoint(CVector(340.0f, 30.0f, -1182.0f), 100.0f * 2 * 4);
	}
	else{
		//�B��HARD�̗\��
	}
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
			mEnemys[i]->mpModel = &mCarWhite;
		}
		else if (i % 8 == 7){
			mEnemys[i]->mpModel = &mCarCyan;
		}

		//�����̔z�u���W��ݒ肷��
		mEnemys[i]->mPosition = CVector(CPlayer::mpPlayer->mPosition.mX, CPlayer::mpPlayer->mPosition.mY,
			CPlayer::mpPlayer->mPosition.mZ - 80.0f*i);
		if (i % 2 == 0){
			mEnemys[i]->mPosition.mX -= 80.0f;
		}
		mEnemys[i]->CCharacter::Update();
	}
	for (int i = 0; i < ENEMYS_AMOUNT; i++){
		CTaskManager::Get()->ChangePriority(mEnemys[i], 15);
	}

	/* �������x�̍����������ɕ`�悷�� */
	//���Ԓn�_(���ɒʂ�Ȃ���1���������ƂɂȂ�Ȃ����A���Ԃ��΂��Ă������Ȃ�)
	new CObj(&mCheckPoint, CVector(2893.0f, -100.0f, 2473.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 200.0f, 220.0f), 101);
	new CObj(&mCheckPoint, CVector(-1020.0f, -100.0f, 4594.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 200.0f, 220.0f), 102);
	new CObj(&mCheckPoint, CVector(-1277.0f, -100.0f, -448.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 200.0f, 220.0f), 103);
	//new CObj(&msumple2, CVector(320.0f, -58.0f, 450.0f), CVector(0.0f, 180.0f, 0.0f), CVector(4.0f, 3.0f, 3.0f), 1);
	new CObj(&mCource02Road, CVector(0.0f, -220.0f, 0.0f), CVector(0.0f, -139.3f, 0.0f), CVector(42.0f, 13.5f, 42.0f), 1);
	new CObj(&mCource02Wall, CVector(0.0f, -220.0f, 0.0f), CVector(0.0f, -139.3f, 0.0f), CVector(42.0f, 13.5f, 42.0f), 200);
	new CObj(&mCource02Jump, CVector(0.0f, -220.0f, 0.0f), CVector(0.0f, -139.3f, 0.0f), CVector(42.0f, 13.5f, 42.0f), 202);
	//�S�[���n�_
	//new CObj(&mMiniGoal, CVector(2222.0f, -1.0f, -2300.0f), CVector(0.0f, 0.0f, 0.0f), CVector(4.2f, 10.0f, 4.2f), 99);
	new CObj(&mMiniGoal, CVector(2315.0f, -1.0f, -2300.0f), CVector(0.0f, 0.0f, 0.0f), CVector(4.2f, 10.0f, 4.2f), 99);
	new CObj(&mMiniGoal, CVector(2107.0f, -1.0f - 0.05f, -2300.0f), CVector(0.0f, 180.0f, 0.0f), CVector(4.2f, 10.0f, 4.2f), 99);
	//new CObj(&mCube, CVector(2216.0f, -1.0f, -2300.0f), CVector(0.0f, 0.0f, 0.0f), CVector(220.0f, 300.0f, 40.0f), 1);

	//�V�[���̐ݒ�
	mScene = ERACEB;

	return;
}

void CSceneRaceB::Update()
{
	CSceneRace::Update();

	//�S�[���n�_�ʉߎ��̏���
	if ((CPlayer::mpPlayer->mPosition.mX > 2216.0f - 222.0f && CPlayer::mpPlayer->mPosition.mX < 2216.0f + 222.0f)
		&& (CPlayer::mpPlayer->mPosition.mZ > -2300.0f - 30.0f && CPlayer::mpPlayer->mPosition.mZ < -2300.0f + 30.0f)
		&& (CPlayer::mpPlayer->mChecks == 3)
		&& (isStartRace)){
		if (mLap == mMaxLap){
			//�x�X�g�^�C���X�V��
			if (mTime < mBestTime){
				mBestTime = mTime;
				isNewRecord = true;
				//�R�[�X�ɂ���ĐV�����L�^����
				if (CSceneTitle::mMode == 1){
					mRecord_A = mBestTime;
				}
				else if (CSceneTitle::mMode == 2){
					mRecord_B = mBestTime;
				}
				else if (CSceneTitle::mMode == 3){
					mRecord_C = mBestTime;
				}
				else if (CSceneTitle::mMode == 4){
					mRecord_D = mBestTime;
				}
			}
			isStartRace = false;
			isGoal = true;
			BGM.Stop();
			SoundGoal.Play();
			//CPlayer::mpPlayer->CanMove = false;//�����X�g�b�v
			CPlayer::mpPlayer->mChecks = 0;
		}
		else{
			mLap++;
			CPlayer::mpPlayer->mChecks = 0;
		}
	}
	//CPU�̎Ԃ��S�[���n�_��ʉ߂������̏���
	for (int i = 0; i < ENEMYS_AMOUNT; i++){
		if (mEnemys[i]->mPosition.mX>2216.0f - 222.0f && mEnemys[i]->mPosition.mX < 2216.0f + 222.0f
			&& (mEnemys[i]->mPosition.mZ > -2300.0f - 30.0f && mEnemys[i]->mPosition.mZ < -2300.0f + 30.0f)
			&& (mEnemys[i]->mChecks == 3)
			&& (mEnemys[i]->isEnemyGoaled == false)){
			//���̓G���ŏI���b�v�������ꍇ
			if (mEnemys[i]->mEnemyLap == mMaxLap){
				//�v���C���[�̖��S�[�����̓v���C���[�̍ŏI���ʂ�������
				if (isGoal == false){
					mRanking++;
				}
				mEnemys[i]->isEnemyGoaled = true;
			}
			//�܂��ŏI���b�v�łȂ��ꍇ
			else{
				//�`�F�b�N�|�C���g�����Z�b�g���A���̎��X�^�[�g
				mEnemys[i]->mChecks = 0;
				mEnemys[i]->mEnemyLap++;
			}
		}
	}
}