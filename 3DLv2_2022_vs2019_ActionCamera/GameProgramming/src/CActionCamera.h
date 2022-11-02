#pragma once
#include "CVector.h"
#include "CCharacter.h"
#include "CMatrix.h"

/*
カメラクラス
*/
class CActionCamera : public CCharacter {
public:
	static const CMatrix& ModelViewInverse();
	static const CMatrix& ModelView();
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
	static CMatrix mModelViewInverse;
	static CMatrix mModelView;
	static CActionCamera* spInstance;
	//視点
	CVector mEye;
	//注視点
	CVector mCenter;
	//上方向
	CVector mUp;
};
