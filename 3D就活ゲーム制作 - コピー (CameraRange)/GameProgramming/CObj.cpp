#include "CObj.h"
#include "CPlayer.h"
#include "CTaskManager.h"

#define DOOR_RANGEOFMOTION 90 //ドアの可動域
#define DOOR_OPENSPEED 2 //ドアの開く速度
#define ROLLINGSPEED 1.0f //回転する足場の回転速度

#define G (9.8f / 120.0f)//重力加速度//60.0f

int CObj::mObjectNum = 0;//現在のオブジェの数
int CObj::mObject_Limit = GROUNDS_LIMIT;//出すことができるオブジェの数
CObj *CObj::mpGrounds[GROUNDS_LIMIT];

//コンストラクタ
//model:モデルのポインタ position:位置 rotation:回転 scale:拡縮 hascollider:コライダの生成の有無(設定がなければ有)
CObj::CObj(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale, bool hascollider, bool hasshadow)
:mpCollider(0)
{
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;

	if (hascollider == false){
		//当たり判定を生成しない
		//当たり判定の数を抑えるほど、処理を軽量化できる
	}
	else{
		CCharacter::Update();
		//モデルの三角形の数分、コライダの配列を作成します
		mpCollider = new CCollider[model->mTriangles.size()];
		for (unsigned int i = 0; i < model->mTriangles.size(); i++){
			//コライダを三角形コライダで設定していきます
			mpCollider[i].SetTriangle(this,
				model->mTriangles[i].mV[0],
				model->mTriangles[i].mV[1],
				model->mTriangles[i].mV[2]);
			mpCollider[i].ChangePriority();
		}
	}

	//影を持つor持たない物体の処理
	if (hasshadow){
		mpGrounds[mObjectNum] = this;
		mObjectNum++;
	}
	else{

	}
	
}
//デストラクタ
CObj::~CObj(){
	//コライダがあれば削除
	if (mpCollider){
		//delete[] 配列を削除
		delete[] mpCollider;
	}
}

void CObj::Update(){
	CCharacter::Update();
}