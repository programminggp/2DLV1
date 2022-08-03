#ifndef CCAMERA_H
#define CCAMERA_H
#include "CVector.h"
#include "CCharacter.h"
/*
カメラクラス
*/
class CCamera : public CCharacter {
public:
	CCamera(float distance);
	void Center(CVector& center);
	//回転
//	CVector mRotation;
	//視点座標の取得
	const CVector& Eye() const;
	//カメラの設定
	//Set(視点, 注視点, 上方向)
	void Set(const CVector &eye, const CVector &center,
		const CVector &up);
	//カメラ適用
	void Render();
	static CCamera* Instance();
private:
	static CCamera* spInstance;
	//視点
	CVector mEye;
	//注視点
	CVector mCenter;
	//上方向
	CVector mUp;
	//
	//float mDistance;
};

//カメラの外部参照
//extern CCamera Camera;
#endif
