#ifndef CACTIONCAMERA_H
#define CACTIONCAMERA_H

#include "CVector.h"
#include "CTransform.h"
#include "CMatrix.h"
/*
カメラクラス
*/
class CActionCamera : public CTransform {
public:
	//インスタンスの取得
	static CActionCamera* Instance();
	//カメラのX軸取得
	CVector VectorX();
	//カメラのZ軸取得
	CVector VectorZ();
	//コンストラクタ(距離, X回転,Y回転)
	CActionCamera(float distance, float xaxis, float yaxis);
	//カメラ更新
	void Update();
	//カメラ適用
	void Render();
	const CMatrix& ModelView();
	const CMatrix& ModelViewInv();
private:
	//インスタンス
	static CActionCamera* spInstance;
	//視点
	CVector mEye;
	//注視点
	CVector mCenter;
	//上方向
	CVector mUp;
	//モデルビュー行列
	CMatrix mModelView;
	//CVector sScale; //拡大縮小倍率
	CMatrix mModelViewInv;
};

//extern CActionCamera ActionCamera;
#endif