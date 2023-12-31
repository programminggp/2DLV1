#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//キャラクタクラスのインクルード
#include "CCharacter3.h"

#define COLLIDERTASK_SIZE 27

/*
コライダクラス
衝突判定データ
*/
class CCollisionManager;
class CCollisionManager2;
class CColliderTask;

class CCollider : public CTransform,public CTask {
	friend CCollisionManager;
	friend CCollisionManager2;
public:
	//優先度の変更
	virtual void ChangePriority();
	//優先度の変更
	void ChangePriority(int priority);
	//ColliderTriangleSphere(三角コライダ、球コライダ、調整値)
	//return:true(衝突している)false(衝突していない)
	// 調整値:衝突いない位置まで戻す値
	static bool CCollider::CollisionTriangleSphere(CCollider* triangle, CCollider* sphere,
		CVector* adjust);
	//CollisionTriangleLine(三角コライダ、線分コライダ、調整値)
	// return:true(衝突している)false(衝突していない)
	// 調整値:衝突市内位置まで戻す値
	static bool CollisionTriangleLine(CCollider* triangle, CCollider* line, CVector* adjust);
	//CollisionTriangleBotan(三角コライダ、ボタンコライダ、調整値)
	// return:true(衝突している)false(衝突していない)
	// 調整値:衝突市内位置まで戻す値
	static bool CollisionTriangleBotan(CCollider* triangle, CCollider* botan, CVector* adjust);
	//コライダタイプ
	enum EType {
		ESPHERE,//球コライダ
		ETRIANGLE,//三角コライダ
		ELINE,//線分コライダ
		EBOTAN,//ボタン
	};
	//デフォルトコンストラクタ
	CCollider();
	//衝突判定
	//Collision(コライダ１、コライダ２)
	//return:ture(衝突している)false(衝突していない)
	static bool Collision(CCollider* m, CCollider* o);
	~CCollider();
	//コンストラクタ
	//CCollider(親、親行列、位置、半径)
	CCollider(CCharacter3* parent, CMatrix* matrix,
		const CVector& position, float radius);
	//親ポインタの取得
	CCharacter3* Parent();
	//描画
	void Render();
protected:
	CVector mCenter;
	CColliderTask* mpColliderTask[COLLIDERTASK_SIZE];
	EType mType;//コライダタイプ
	//頂点
	CVector mV[4];
	CCharacter3* mpParent; //親
	CMatrix* mpMatrix; //親行列
	float mRadius; //半径
public:
	EType Type();
};
#endif
