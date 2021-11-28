//#include "CSceneTitle.h"
#include "CTaskManager.h"
#include "CKey.h"
#include <stdio.h>
#include <math.h>
#include "CCameraRange.h"
#include "CPlayer.h"

CCameraRange *CCameraRange::mpCameraRange = 0;

CCameraRange::CCameraRange()
:mColRange(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 40.0f)
{
	mpCameraRange = this;

	mTag = EPLAYER;

	mColRange.mTag = CCollider::ECAMERA_RANGE;

	mPosition = CVector(0.0f, 15.0f, -35.0f) * CPlayer::mpPlayer->mMatrixScale * CPlayer::mpPlayer->mMatrixRotate * CPlayer::mpPlayer->mMatrixTranslate;
	CCharacter::Update();	
}

void CCameraRange::Update(){	
	mPosition = CVector(0.0f, 15.0f, -35.0f) * CMatrix().RotateY(0)* CPlayer::mpPlayer->mMatrixScale   // * mPlayer->mMatrixScale
		* CMatrix().RotateY(CPlayer::mpPlayer->mRotation.mY)
		* CPlayer::mpPlayer->mMatrixTranslate
		+ CVector(0.0f, 0.0f, 0.0f);
	CCharacter::Update();
}

void CCameraRange::TaskCollision()
{
	mColRange.ChangePriority();
}