#include "CSceneManager.h"
#include "CSceneGame.h"

CSceneManager::CSceneManager()
: mpScene(0)
{

}

CSceneManager::~CSceneManager() {
	if (mpScene) {
		delete mpScene;
		mpScene = 0;
	}
}

void CSceneManager::Init() {
	mpScene = new CSceneGame();
	mpScene->Init();
}

void CSceneManager::Update() {
	mpScene->Update();
	if (mInput.Key(VK_RETURN)) {
		delete mpScene;
		mpScene = new CSceneGame();
		mpScene->Init();
	}
}

void CSceneManager::Render() {
	mpScene->Render();
}
