#include "CRaceCourceD.h"
#include "CObj.h"
#include "CObjWall.h"
#include "CObjFloor.h"
//
#include "CObjGrass.h"
#include "CObjBoost.h"
#include "CObjNonCol.h"
#include "CSceneTitle.h"

void CRaceCourceD::Init(){
	//�V�[���̐ݒ�
	mScene = ERACE4;

	CSceneRace::Init();
	
	//�v���C���[�̐���
	mPlayer = new CPlayer();
	mPlayer->mpModel = &mCarWhite;
	//�J�����̐���
	mCamRange = new CCameraRange();
	mCam = new CCameraPos();
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
		mEnemys[i]->mPosition = CVector(350.0f, -13.538f, -130.0f - 80.0f*i);
		if (i % 2 == 0){
			mEnemys[i]->mPosition.mX -= 80.0f;
		}
		mEnemys[i]->CCharacter::Update();
	}

	int ess[3][4][5] = {
		{
			{ 00, 00, 00, 00, 21 },
			{ 00, 24, 00, 00, 00 },
			{ 00, 00, 00, 00, 00 },
			{ 00, 00, 00, 00, 00 },
		},
		{
			{ 00, 00, 00, 32, 00 },
			{ 00, 00, 34, 21, 33 },
			{ 00, 33, 00, 00, 00 },
			{ 00, 23, 22, 00, 00 },
		},
		{
			{ 24, 12, 32, 00, 00 },
			{ 31, 24, 21, 00, 00 },
			{ 33, 11, 31, 33, 33 },
			{ 23, 22, 00, 23, 22 },
		}
	};
	int size = 10;//�R�[�X�̏k��
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 4; j++){
			for (int k = 0; k < 5; k++){
				if (ess[i][j][k] == 11){//����:I��
					new CObjFloor(&mTile_Straight01_Floor, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Straight01_Wall, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 12){//����:�ꎚ
					new CObjFloor(&mTile_Straight02_Floor, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Straight02_Wall, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 21){//�J�[�u:0���`3��
					new CObjFloor(&mTile_Curve03_Floor, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Curve03_Wall, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 22){//�J�[�u:3���`6��
					new CObjFloor(&mTile_Curve04_Floor, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Curve04_Wall, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 23){//�J�[�u:6���`9��
					new CObjFloor(&mTile_Curve01_Floor, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Curve01_Wall, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 24){//�J�[�u:9���`12��
					new CObjFloor(&mTile_Curve02_Floor, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Curve02_Wall, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 31){//��:
					new CObjFloor(&mTile_Slope01_Floor, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Slope01_Wall, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 32){//��:
					new CObjFloor(&mTile_Slope02_Floor, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Slope02_Wall, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 33){//��:
					new CObjFloor(&mTile_Slope03_Floor, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Slope03_Wall, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 34){//��:
					new CObjFloor(&mTile_Slope04_Floor, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Slope04_Wall, CVector(-100.0f * size * k, 45.0f * size * (3-1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 91){//�L����
					new CObjFloor(&mTile_Wide_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mTile_Wide_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
				else if (ess[i][j][k] == 99){//�ł����u���b�N
					new CObjFloor(&mBlock_Floor, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
					new CObjWall(&mBlock_Wall, CVector(-100.0f * size * k, 45.0f * size * (3 - 1 - i), -100.0f * size * j), CVector(), CVector(1.0f * size, 1.0f* size, 1.0f* size));
				}
			}
		}
	}

	//�D��x�ύX
	CTaskManager::Get()->ChangePriority(mPlayer, 15);
	for (int i = 0; i < ENEMYS_AMOUNT; i++){
		CTaskManager::Get()->ChangePriority(mEnemys[i], 15);
	}
}
void CRaceCourceD::Update(){
	CSceneRace::Update();

}