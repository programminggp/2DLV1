#include "CSceneTitle.h"

int CSceneTitle::mMode = 1; //�R�[�X��Lap���̏����ݒ�
int CSceneTitle::mDifficulty = 2; //�GAI�̋����̏����ݒ�@�@1:EASY�@2:NORMAL�@3:HARD

////�O���Q�Ƃ����������悤�Ƃ��Ă���Ƃ���
//enum ECource CSceneTitle::mCource = ECOURCE1;
//ECource CSceneTitle::mCource = ECOURCE1;
//enum EMode CSceneTitle::mMode = E1LAP;

//���̃V�[���̎擾
CScene::EScene CSceneTitle::GetNextScene(){
	return mScene;
}

void CSceneTitle::Render(){

}