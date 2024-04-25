#ifndef CTEXTURE_H
#define CTEXTURE_H
#include "glut.h"
#include "CRect.h"
#include <vector>
#include "CResource.h"

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

class CTexture : public CResource
{
	friend CResourceManager;

public:
	int Row();
	int Col();
	const STgamHeader& Header() const;
	const GLuint& Id() const;
	//�s���񐔂̐ݒ�
	//SetRowCol(�s��, ��)
	void SetRowCol(int row = 1, int col = 1);

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

	/// <summary>
	/// �s���Ɨ񐔂��w�肵��UV���v�Z
	/// </summary>
	/// <param name="row">�s��</param>
	/// <param name="col">��</param>
	/// <param name="num">�擾����UV�̔ԍ�</param>
	/// <returns></returns>
	CRect CalcUV(int row, int col, int num) const;
	/// <summary>
	/// ���W���w�肵��UV���v�Z
	/// </summary>
	/// <param name="left">�����̍��W</param>
	/// <param name="top">�㑤�̍��W</param>
	/// <param name="right">�E���̍��W</param>
	/// <param name="bottom">�����̍��W</param>
	/// <returns></returns>
	CRect CalcUV(float left, float top, float right, float bottom) const;
	/// <summary>
	/// �J�n�ʒu�ƃT�C�Y���w�肵��UV���v�Z
	/// </summary>
	/// <param name="pos">�J�n�ʒu</param>
	/// <param name="size">�T�C�Y</param>
	/// <returns></returns>
	CRect CalcUV(const CVector2& pos, const CVector2& size) const;

private:
	/*
	�f�t�H���g�R���X�g���N�^
	*/
	CTexture();
	CTexture(char* file);
	/*
	�f�X�g���N�^�i���̃C���X�^���X���j�������Ƃ��Ɏ��s�����j
	*/
	~CTexture();
	/*
	Load(�t�@�C����)
	�摜�t�@�C���̓ǂݍ��݁i�e�N�X�`���t�@�C���̓ǂݍ��݁j
	*/
	bool Load(std::string path, bool dontDelete) override;

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

// �e�N�X�`���̃A�j���[�V�����̃t���[�����
struct TexAnimFrameData
{
	int no;		// �摜�ԍ�
	float time;	// ���̉摜�܂ł̎���
};

// �e�N�X�`���̃A�j���[�V�����f�[�^
class TexAnimData
{
public:
	int row;	// �s��
	int col;	// ��
	bool loop;	// ���[�v���邩�ǂ���
	// �t���[����񃊃X�g
	std::vector<TexAnimFrameData> frames;

	TexAnimData(int r, int c, bool l, std::vector<TexAnimFrameData> f)
		: row(r)
		, col(c)
		, loop(l)
		, frames(f)
	{
	}

	TexAnimData(int r, int c, bool l, int fc, float fr)
		: row(r)
		, col(c)
		, loop(l)
	{
		for (int i = 0; i < fc; i++)
		{
			frames.push_back({ i, fr });
		}
	}
};

#endif
