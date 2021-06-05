#ifndef CMAP_H
#define CMAP_H

#include "CModelObj.h"

#define PATH_LANDSCAPE_OBJ "Data\\landscape\\landskapefarmlowpoly.obj"

/*
�}�b�v�N���X
�n�`���`���܂�
*/
class CMap {
public:
	//�}�b�v�̃��f���f�[�^�iOBJ�`���j
	CModelObj mObj;

	CMap() {
		mObj.Load(PATH_LANDSCAPE_OBJ);
		mObj.AddCollisionManager();
	}

	void Render() {
		mObj.Render();
	}
};

#endif
