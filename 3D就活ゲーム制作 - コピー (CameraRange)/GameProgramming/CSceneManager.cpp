#include "CSceneManager.h"
#include "CSceneRace.h"
#include "CRaceCourceA.h"
#include "CRaceCourceB.h"
#include "CRaceCourceC.h"
#include "CRaceCourceD.h"
#include "CRaceCourceE.h"
#include "CSceneEditor.h"
#include "CSceneTitle.h"
#include "CTaskManager.h"

CSceneManager SceneManager;

CScene::EScene mScene;

//�R���X�g���N�^
CSceneManager::CSceneManager()
: mpScene(0)
{}
//�f�X�g���N�^�i�폜�����Ƃ��Ɏ��s����܂��j
CSceneManager::~CSceneManager() {
	//�V�[��������΍폜
	if (mpScene)
		//�V�[���̍폜
		delete mpScene;
	mpScene = 0;
	CTaskManager::Get()->Destroy();
}
//����������
void CSceneManager::Init() {
	//�V�[���̎��ʂ�ݒ肷��
	mScene = CScene::ETITLE;
	//�V�[���𐶐����A�|�C���^��ݒ肷��
	mpScene = new CSceneTitle();

	//���������N���X�̃��\�b�h���Ă΂��
	mpScene->Init();
}
//�X�V����
void CSceneManager::Update() {
	//�|�C���^��Update���Ă�
	mpScene->Update();

	//���̃V�[�����擾���قȂ邩����
	if (mScene != mpScene->GetNextScene()){
		mScene = mpScene->GetNextScene();
		delete mpScene;//���̃V�[���폜
		//�Y������V�[���𐶐�
		switch (mScene){
		case CScene::ETITLE:
			mpScene = new CSceneTitle();
			mpScene->Init();
			break;
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
			mpScene = new CRaceCourceE();
			mpScene->Init();
			break;		
		case CScene::EEDIT:
			mpScene = new CSceneEditor();
			mpScene->Init();
			break;		
		}
	}
}
