#ifndef CSCENE_H
#define CSCENE_H

/*
�V�[���̊��N���X
*/
class CScene {
public:
	static CScene *mpInstance;
	//��ʓ��e�͈͂̕ϐ�
	int mLeft, mRight, mBottom, mTop;

	//virtual ���z�֐�
	//�|�����[�t�B�Y���̎���
	//=0 �������z�֐��̐ݒ�
	virtual void Init() = 0;	//�������z�֐� ����������
	virtual void Update() = 0; //�������z�֐� �X�V����

	//�V�[���̎��ʎq
	enum EScene {
		EGAME,
	};
	//���̃V�[���̎擾
	EScene mScene;


	virtual EScene GetNextScene() = 0;
	virtual ~CScene() {}	//�f�X�g���N�^�̒�`
};


#endif
