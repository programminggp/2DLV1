#ifndef CXPLAYER_H
#define CXPLAYER_H

#include"CXCharacter.h"
#include"CCollider.h"
#include"CModelX.h"
#include"CColliderCapsule.h"

class CXPlayer :public CXCharacter {
public:
	//更新処理
	void Update();
	CXPlayer();
	void Init(CModelX* model);
	void TaskCollision();
	void Collision(CCollider* m, CCollider* o);
	static CXPlayer* Get();
	static bool BattleSwitch;  //攻撃切り替え
	void Render();
private:
	//コライダ宣言
	CCollider mColSphereShield; //盾
	CCollider mColSphereSword; //剣
	CColliderCapsule mColCapBody; //胴体
	CCollider mCore; //コア
	CModel mMagicRingRed; //魔法陣
	CMatrix MagicRingRotation;
	int StandCount; //待機状態カウント
	/*int SlashCount1;
	int SlashCount2;
	int SlashCount3;*/
    int PlayerHp;  //体力
	int SMagicCount;  //単体魔法間隔
	int AMagicCount;  //範囲魔法間隔
	int MagicWait;  //待機時間
	int MagicRingTime;
	static CXPlayer* spInstance;
	

	CVector mScale; //拡大縮小倍率
	bool mPushFlg;
	float mOldMousePosX;
	
};

#endif // !CXPLAYER_H

