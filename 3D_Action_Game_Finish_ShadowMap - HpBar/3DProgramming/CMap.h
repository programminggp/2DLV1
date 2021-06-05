#ifndef CMAP_H
#define CMAP_H

#include "CModelObj.h"

#define PATH_LANDSCAPE_OBJ "Data\\landscape\\landskapefarmlowpoly.obj"

/*
マップクラス
地形を定義します
*/
class CMap {
public:
	//マップのモデルデータ（OBJ形式）
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
