#ifndef CTEXTURE_H
#define CTEXTURE_H
#include "glut.h"

//���\�[�X�t�@�C���t�H���_
#define RES_DIR "res\\"

/*
TGA�t�@�C���̃w�b�_�t�H�[�}�b�g
*/
struct STgamHeader {
	unsigned char dummy1[12];
	int	width;	//��
	int	height;	//����
	int	depth;	//�r�b�g�̐[��
	unsigned char	discripter;
};

/*
�e�N�X�`���[�N���X
*/
//#include <map>

class CTexture {
public:
	int Row();
	int Col();
	const STgamHeader& Header() const;
	const GLuint& Id() const;
	//�s���񐔂̐ݒ�
	//SetRowCol(�s��, ��)
	void SetRowCol(int row = 1, int col = 1);

	/*
	�f�t�H���g�R���X�g���N�^
	*/
	CTexture();
	CTexture(char *file);
	/*
	�f�X�g���N�^�i���̃C���X�^���X���j�������Ƃ��Ɏ��s�����j
	*/
	~CTexture();
	/*
	Load(�t�@�C����)
	�摜�t�@�C���̓ǂݍ��݁i�e�N�X�`���t�@�C���̓ǂݍ��݁j
	*/
	void Load(const char* file);
	/*
	DrawImage(�l�p�`�����W, �l�p�`�E���W, �l�p�`�����W, �l�p�`����W,
	    �摜�����W, �摜�E���W, �摜�����W, �摜����W)
	�摜�̕`��
	*/
	void DrawImage(float left, float right, float bottom, float top, int tleft, int tright, int tbottom, int ttop) const;
	void DrawImage(float left, float right, float bottom, float top, float tleft, float tright, float tbottom, float ttop) const;
	void DrawImage(float left, float right, float bottom, float top, int index);
	void Destory();
	void SetParts(int row, int col);
	void Draw(float left, float right, float bottom, float top, float tleft, float tright, float tbottom, float ttop);
	void Draw(float left, float right, float bottom, float top, int tleft, int tright, int tbottom, int ttop) const ;
private:
	//	static std::map<std::string, CTexture>mTexFile;
		//�t�@�C����
	char* mpName;
	//TGA�t�@�C���̃w�b�_���
	STgamHeader mHeader;
	//�e�N�X�`��ID
	GLuint mId;
	//
	int mRow;//�s��
	int mCol;//��
};

#endif
