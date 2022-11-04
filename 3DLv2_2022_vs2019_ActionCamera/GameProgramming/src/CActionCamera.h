#pragma once
#include "CVector.h"
#include "CCharacter.h"
#include "CMatrix.h"

/*
カメラクラス
*/
class CActionCamera : public CCharacter {
public:
	static CVector VectorX();
	static CVector VectorZ();
	CActionCamera(float distance);
	CActionCamera(float distance, float xaxis, float yaxis);
	static CActionCamera* Instance();

	//カメラ更新
	void CameraUpdate();
	//カメラ適用
	void CameraRender();
	//処理しない
	void Render() {}
private:
	static CMatrix mModelView;
	static CActionCamera* spInstance;
	//視点
	CVector mEye;
	//注視点
	CVector mCenter;
	//上方向
	CVector mUp;
};
