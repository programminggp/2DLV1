#ifndef CMAP2_H
#define CMAP2_H

#include "CCharacter.h"
#include "CColliderMesh.h"
#include "CXPlayer.h"
#include "CCameraControl.h"

class CMap2 : public CCharacter
{
	CXPlayer mPlayer;
	CModel mModel;
	CColliderMesh mColMesh;
	CCameraControl mCameraControl;
public:
	CMap2();
};

#endif

