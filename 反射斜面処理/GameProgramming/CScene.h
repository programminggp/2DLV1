#ifndef CSCENE_H
#define CSCENE_H

/*
�V�[���̊��N���X
*/
class CScene {
public:
	//virtual ���z�֐�
	//�|�����[�t�B�Y���̎���
	//=0 �������z�֐��̐ݒ�
	virtual void Init() = 0;	//�������z�֐� ����������
	virtual void Update() = 0; //�������z�֐� �X�V����
	//���̃V�[���̎擾
	//virtual EScene GetNextScene() = 0;
	virtual ~CScene() {}	//�f�X�g���N�^�̒�`

	//2D�`��X�^�[�g
	//Start2D(�����W, �E���W, �����W, ����W)
	void Start2D(float left, float right, float bottom, float top);
	//2D�`��I��
	void End2D();
	//�J�����̐ݒ�
	//Camera3D(���_X���W, ���_Y���W, ���_Z���W, �����_X���W, �����_Y���W, �����_Z���W, �����X, �����Y, �����Z)
	void Camera3D(float ex, float ey, float ez, float cx, float cy, float cz, float ux, float uy, float uz);
};


#endif
