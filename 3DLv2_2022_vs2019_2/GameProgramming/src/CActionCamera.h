#pragma once
#include "CVector.h"
#include "CCharacter.h"
/*
カメラクラス
*/
class CActionCamera : public CCharacter {
public:
	CActionCamera(float distance);
	void Center(CVector& center);
	static CActionCamera* Instance();

	//カメラ更新
	void CameraUpdate();
	//カメラ適用
	void CameraRender();
	//処理しない
	void Render() {}
private:
	static CActionCamera* spInstance;
	//視点
	CVector mEye;
	//注視点
	CVector mCenter;
	//上方向
	CVector mUp;
};
