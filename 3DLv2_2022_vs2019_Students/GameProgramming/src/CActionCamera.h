#pragma once
#include "CVector.h"
#include "CTransform.h"
#include "CMatrix.h"
/*
カメラクラス
*/
class CActionCamera : public CTransform {
public:
	//ワールド座標をスクリーン座標へ変換する
	//WorldToScreen(スクリーン座標, ワールド座標)
	bool WorldToScreen(CVector* screen, const CVector& world);
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
private:
	int mScreenWidth; //幅
	int mScreenHeight; //高さ
	CMatrix mProjection; //プロジェクション行列
	CMatrix mModelView; //モデルビュー行列
	//インスタンス
	static CActionCamera* spInstance;
	//視点
	CVector mEye;
	//注視点
	CVector mCenter;
	//上方向
	CVector mUp;
};
