#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//トランスフォームクラスのインクルード
#include "CTransform.h"
//
//#include "CXCharacter.h"
/*
コライダクラス
衝突判定データ
*/
class CCollider : public CTransform, public CTask {
public:
	//コライダの種類
	enum ETag {
		ENONE,
		EBODY,//機体
		ESEARCH,//サーチ
		ESWORD,	//剣
	};
	ETag mTag;
	//コライダタイプ
	enum EType {
		ESPHERE,
		ETRIANGLE,
		ELINE, //線分コライダ
	};
	EType mType;
	//頂点
	CVector mV[3];
	CCharacter *mpParent;//親
	float mRadius;	//半径
	//25
	//ボーンの合成行列のポインタ
	CMatrix *mpCombinedMatrix;
	//?
	//デフォルトコンストラクタ
	CCollider();
	//コンストラクタ
	//CCollider(親, 位置, 回転, 拡縮, 半径)
	CCollider(CCharacter *parent, CVector position, CVector rotation, CVector scale, float radius);
	////25
	////CCollider(親, 位置, 回転, 拡縮, 半径, 合成行列)
	//CCollider(CCharacter *parent, CVector position, CVector rotation, CVector scale, float radius, CMatrix *combined);
	//コンストラクタ（三角コライダ）
	//CCollider(親, 頂点1, 頂点2, 頂点3)
	CCollider(CCharacter *parent, const CVector &v0, const CVector &v1, const CVector &v2);
	//三角コライダの設定
	//SetTriangle(親, 頂点1, 頂点2, 頂点3)
	void SetTriangle(CCharacter *parent, const CVector &v0, const CVector &v1, const CVector &v2);
	//コンストラクタ（線分コライダ）
	//CCollider(親, 頂点1, 頂点2)
	CCollider(CCharacter *parent, const CVector &v0, const CVector &v1);
	//線分コライダの設定
	//SetLine(親, 頂点1, 頂点2)
	void SetLine(CCharacter *parent, const CVector &v0, const CVector &v1);
	~CCollider();
	//描画
	void Render();
	//衝突判定
	//Collision(コライダ1, コライダ2)
	//retrun:true（衝突している）false(衝突していない)
	static bool Collision(CCollider *m, CCollider *y);
	//CollisionTriangleLine(三角コライダ, 線分コライダ, 調整値)
	//retrun:true（衝突している）false(衝突していない)
	//調整値:衝突しない位置まで戻す値
	static bool CollisionTriangleLine(CCollider *triangle, CCollider *line, CVector *adjust);
	//CollisionTriangleSphere(三角コライダ, 球コライダ, 調整値)
	//retrun:true（衝突している）false(衝突していない)
	//調整値:衝突しない位置まで戻す値
	static bool CollisionTriangleSphere(CCollider *triangle, CCollider *sphere, CVector *adjust);
};

#endif
