#ifndef CMODELX_H	//�C���N���[�h�K�[�h
#define CMODELX_H

#define MODEL_FILE "res\\sample.blend.x"	//���̓t�@�C���� \�́�

//�̈������}�N����
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = nullptr;}
/*
 CModelX
 X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/
class CModelX {
public:
	//�P��̎��o��
	char* GetToken();

	CModelX();
	//�t�@�C���ǂݍ���
	void Load(char* file);
private:
	//c����؂蕶���Ȃ�true��Ԃ�
	bool IsDelimiter(char c);

	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];	//���o�����P��̗̈�
};

#endif
