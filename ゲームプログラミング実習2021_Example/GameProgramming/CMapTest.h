#ifndef CMAPTEST_H
#define CMAPTEST_H

#include "CCharacter.h"
#include "CCameraControl.h"
#include "CColliderMesh.h"
#include "CXPlayer.h"
#include "CScorpid.h"
#include "CFreeMonster.h"
#include "CGoblin.h"
#include "CFelguard.h"
#include "CKnight.h"

class CMapTest : public CCharacter
{
	CXPlayer mPlayer;
	CColliderMesh mColMesh;
	CModel mModel;
	CCameraControl mCameraControl;
	CGoblin mMonster;
public:
	CMapTest();
	//void Render() {}
};

#endif

