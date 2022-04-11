#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CModel.h"
//プレイヤークラスのインクルード
#include"CPlayer.h"
#include "CColliderMesh.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//モデルクラスのインスタンス作成
	CModel mModel; //プレイヤーモデル
	CModel mBackGround; //背景モデル
	CModel mModelC5; //敵モデル
	//プレイヤーの変数
	CPlayer mPlayer;
	//モデルからコライダを生成
	CColliderMesh mColliderMesh;

};

#endif
