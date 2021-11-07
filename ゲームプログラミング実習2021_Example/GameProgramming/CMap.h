#ifndef CMAP_H
#define CMAP_H

#include "CCharacter.h"
#include "CCameraControl.h"
#include "CColliderMesh.h"
#include "CXPlayer.h"

class CMap : public CCharacter
{
	CXPlayer mPlayer;
	CColliderMesh mColMesh;
	CModel mModel;
	CCameraControl mCameraControl;
public:
	CMap();
};

#endif

