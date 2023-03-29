#pragma once
#include<string>
 
class CTaskManager;
class CCharacter;

enum class ETaskPriority
{
	EUI,                //UI
	ETITLE,             //タイトル画面
	ECharacter,         //キャラクター
	ECharacterManager,  //キャラクターマネージャー
	EBackGround = 1003, //背景
	EBackGround2 = 1003,
	EBackGround3 = 1003,
	EBackGround4 = 1003,
	EBLOCK = 0,
};

class CTask
{
	friend CTaskManager;
public:
	enum class ETag
	{
		EZERO,
		EPLAYER,    //プレイヤー
		EENEMY,     //敵
		EBULLET,    //プレイヤーの攻撃
		EATTACK,    //敵の攻撃(回避可能)
		EATTACK2,   //敵の攻撃(当たると確定ダメージ)
		EITEM,
		EBLOCK,
	};
private:
	CTask* mpprev;   //前のタスクへのポインタ
	CTask* mpnext;   //次のタスクへのポインタ
	int mpriority;   //優先度

protected:
	ETag mTag;

public:
	ETag Tag();
	//コンストラクタ
	CTask(int priority);
	//~デストラクタ
	~CTask();

	//優先度を設定
	void Setpriority(int priority);
	//優先度を取得
	int GetPriority() const;
	//タスクを削除
	void Delete();

	//描画処理
	virtual void Render() {};
	//更新処理
	virtual void Update() {};
	//衝突処理
	virtual void Collision(CCharacter* m, CCharacter* o) {}
};