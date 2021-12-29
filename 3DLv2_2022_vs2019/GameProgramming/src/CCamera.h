#ifndef CCAMERA_H
#define CCAMERA_H
#include "CVector.h"
#include "CCharacter.h"
/*
カメラクラス
*/
class CCamera : public CCharacter {
	static CCamera* spInstance;
public:
	static CCamera* Get();
	CCamera(const CVector& pos, const CVector& rot, float distance);
	
	//視点座標の取得
	const CVector& Eye() const;
	//カメラの設定
	//Set(視点, 注視点, 上方向)
	void Set(const CVector &eye, const CVector &center,
		const CVector &up);
	void Update();
	//カメラ適用
	void Render();
private:
	//視点
	CVector mEye;
	//注視点
	CVector mCenter;
	//上方向
	CVector mUp;
};

//カメラの外部参照
//extern CCamera Camera;
#endif
