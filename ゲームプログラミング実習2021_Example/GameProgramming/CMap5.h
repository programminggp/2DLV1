#ifndef CMAP5_H
#define CMAP5_H

#include "CCharacter.h"
#include "CCameraControl.h"
#include "CColliderMesh.h"
#include "CXPlayer.h"

class CMap5 : public CCharacter
{
	CXPlayer mPlayer;
	CColliderMesh mColMesh;
	CModel mModel;
	CCameraControl mCameraControl;
public:
	CMap5();
	//void Render() {}
};

#endif

