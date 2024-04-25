#include "CResource.h"
#include "CSceneManager.h"

CResource::CResource()
	: mSceneType(EScene::eNone)
	, mReferenceCount(0)
{
	SetDontDelete(false);
}

CResource::~CResource()
{
}

void CResource::SetDontDelete(bool del)
{
	mSceneType = del ?
		EScene::eNone :
		CSceneManager::Instance()->GetCurrentScene();
}

//bool CResource::Load(std::string path)
//{
//	return false;
//}

void CResource::Referenced()
{
	mReferenceCount++;
}

void CResource::Release()
{
	mReferenceCount--;
}
