#ifndef CMAPTEST_H
#define CMAPTEST_H

#include "CCharacter.h"
#include "CCameraControl.h"
#include "CColliderMesh.h"
#include "CXPlayer.h"
#include "CScorpid.h"

class CMapTest : public CCharacter
{
	CXPlayer mPlayer;
	CColliderMesh mColMesh;
	CModel mModel;
	CCameraControl mCameraControl;
	CScorpid mScorpid;
public:
	CMapTest();
	//void Render() {}
};

#endif

