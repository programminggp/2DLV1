#include "CScene.h"
#include "CTask.h"

CScene::~CScene() {
	CTaskManager::Get()->Destroy();
}
void CScene::Init() {}
void CScene::Update() {}
void CScene::Render() {}
