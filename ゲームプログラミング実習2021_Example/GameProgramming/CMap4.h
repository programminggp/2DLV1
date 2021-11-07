#ifndef CMAP4_H
#define CMAP4_H

#include "CCharacter.h"
#include "CCameraControl.h"
#include "CColliderMesh.h"
#include "CXPlayer.h"

class CMap4 : public CCharacter
{
	CXPlayer mPlayer;
	CColliderMesh mColMesh;
	CModel mModel;
	CCameraControl mCameraControl;
public:
	CMap4();
};

#endif

