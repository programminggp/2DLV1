#ifndef CMAP2_H
#define CMAP2_H

#include "CCharacter.h"
#include "CColliderMesh.h"
#include "CXPlayer.h"
#include "CCameraControl.h"

class CMap2 : public CCharacter
{
	CXPlayer mPlayer;
	CColliderMesh mColMesh;
	CModel mModel;
	CCameraControl mCameraControl;
public:
	CMap2();
};

#endif

