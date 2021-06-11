#include "CSceneManager.h"
#include "CSceneRace.h"
#include "CRaceCourceA.h"
#include "CRaceCourceB.h"
#include "CRaceCourceC.h"
#include "CRaceCourceD.h"
#include "CRaceCourceE.h"
#include "CRaceCourceETest.h"
#include "CRaceCourceF.h"
#include "CSceneTitle.h"
#include "CTaskManager.h"

#include "CShadowMap.h"

CSceneManager SceneManager;

CScene::EScene mScene;


//コンストラクタ
CSceneManager::CSceneManager()
: mpScene(0)
{}
//デストラクタ（削除されるときに実行されます）
CSceneManager::~CSceneManager() {
	//シーンがあれば削除
	if (mpScene)
		//シーンの削除
		delete mpScene;
	mpScene = 0;
	CTaskManager::Get()->Destroy();
}
//初期化処理
void CSceneManager::Init() {
	//シーンの識別を設定する
	mScene = CScene::ETITLE;
	//シーンを生成し、ポインタを設定する
	mpScene = new CSceneTitle();
//	mpScene = new CShadowMap();

	//生成したクラスのメソッドが呼ばれる
	mpScene->Init();
}
//更新処理
void CSceneManager::Update() {
	//ポインタのUpdateを呼ぶ
	mpScene->Update();

//	return;

	//次のシーンを取得し異なるか判定
	if (mScene != mpScene->GetNextScene()){
		mScene = mpScene->GetNextScene();
		delete mpScene;//今のシーン削除
		//該当するシーンを生成
		switch (mScene){
		case CScene::ERACE1:
			mpScene = new CRaceCourceA();
			mpScene->Init();
			break;
		case CScene::ERACE2:
			mpScene = new CRaceCourceB();
			mpScene->Init();
			break;
		case CScene::ERACE3:
			mpScene = new CRaceCourceC();
			mpScene->Init();
			break;
		case CScene::ERACE4:
			mpScene = new CRaceCourceD();
			mpScene->Init();
			break;
		case CScene::ERACE5:
//			mpScene = new CRaceCourceE();
			mpScene = new CRaceCourceETest();
			mpScene->Init();
			break;
		case CScene::ERACE6:
			mpScene = new CRaceCourceF();
			mpScene->Init();
			break;
		case CScene::ETITLE:
			mpScene = new CSceneTitle();
			mpScene->Init();
			break;
		}
	}
}
