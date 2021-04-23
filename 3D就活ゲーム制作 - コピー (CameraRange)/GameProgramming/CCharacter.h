#ifndef CCHARACTER_H
#define CCHARACTER_H
//ベクトルクラスのインクルード
#include "CVector.h"
//モデルクラスのインクルード
#include "CModel.h"
//マトリクスクラスのインクルード
#include "CMatrix.h"
//タスククラスのインクルード
#include "CTask.h"
//#include "CCollider.h"
//コライダクラスの宣言
class CCollider;
/*
キャラクタークラス
ゲームキャラクタの基本的な機能を定義する
*/
class CCharacter : public CTask {
public:
	//種類
	enum ETag {
		ENONE,	//初期値
		EPOINT,	//ポイント
		EPLAYER,//プレイヤー
		EAIRBASE,//空軍基地
		EMISSILE,//ミサイル
		EENEMY, //敵
		ESPRING,//ばね
		ESCREW, //スクリュー
		EBOAT, //ボート
		EGUN,   //銃
		EWATER, //水場
		EBULLET,//弾
		ECLEARWATER,//透き通った水
		EKEY, //鍵
		ECHECKPOINT,//中間地点1
		ECHECKPOINT2,//中間地点2
		ECHECKPOINT3,//中間地点3
		EGOALPOINT,//ゴール地点
		EDASHBOARD,//加速床
		EGRASS, //芝生
		EWALL, //壁
		EJUMPER, //ジャンプ台
	};
	ETag mTag;
//	CCharacter *mpParent;	//親
	CVector mPosition; //位置
	CVector mRotation; //回転
	CVector mScale; //拡大縮小
	CModel *mpModel; //モデルのポインタ
	CMatrix mMatrix; //合成行列
	CMatrix mMatrixTranslate; //平行移動行列
	CMatrix mMatrixRotate; //回転行列
	CMatrix mMatrixScale; //拡大縮小行列
	//22
	CCharacter();
	~CCharacter();
	//更新処理
	void Update();
	//描画処理
	void Render();
	//衝突処理
	virtual void Collision(CCollider *mycol, CCollider *youcol) {}
	//
	//void ChangePriority(int priority);
	//描画処理の有無
	bool isRender;
};

#endif
