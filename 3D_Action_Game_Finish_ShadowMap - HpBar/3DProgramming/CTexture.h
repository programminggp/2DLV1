#pragma once
#include "glew.h"
#include "glut.h"
#include <stdio.h>	//�t�@�C���̓��͂Ɏg�p
#include <string.h>
/*
TGA�t�@�C���̃w�b�_�t�H�[�}�b�g
*/
struct STgaheader {
	unsigned char	dummy1[12];
	unsigned short	width;		//��
	unsigned short	height;	//����
	unsigned char	depth;	//�r�b�g�̐[��
	unsigned char	dummy2;
};
/*
�e�N�X�`���[�N���X
*/
class CTexture {
public:
	//�e�N�X�`��ID
	GLuint id;
	//TGA�t�@�C���̃w�b�_���
	STgaheader header;
	//�t�@�C����
	char* mpName;
	/*
	�f�t�H���g�R���X�g���N�^
	*/
	CTexture()
		: id(0)
		, mpName(0) {}
	CTexture(char *file)
		: id(0)
		, mpName(0) {
		load(file);
	}
	/*
	�f�X�g���N�^�i���̃C���X�^���X���j�������Ƃ��Ɏ��s�����j
	*/
	~CTexture() {
		//�e�N�X�`���f�[�^������΍폜����
		if (id != 0) {
			//�e�N�X�`���f�[�^�̍폜
			glDeleteTextures(1, &id);
			id = 0;
		}
		if (mpName) {
			delete[] mpName;
			mpName = 0;
		}
	}

	/*
	�摜�t�@�C���̓ǂݍ��݁i�e�N�X�`���t�@�C���̓ǂݍ��݁j
	*/
	void load(const char* filename) {
		//�摜�f�[�^
		unsigned char* data;
		//�t�@�C���|�C���^�̍쐬
		FILE *fp;
		//�t�@�C���I�[�v��
		fp = fopen(filename, "rb");
		//�G���[�̂Ƃ��̓��^�[��
		if (!fp) {
			printf("file not found:%s\n", filename);
			return;
		}
		mpName = new char[strlen(filename) + 1];
		strcpy(mpName, filename);
		//�w�b�_����ǂݍ���
		fread(&header, sizeof(header), 1, fp);
		//�摜�f�[�^�̃o�C�g�����v�Z����
		int length = header.width * header.height * header.depth / 8;
		//�摜�f�[�^�̊i�[�̈���m��
		data = new unsigned char[length];
		//�摜�f�[�^���w�b�_�̑�������ǂݍ���
		fread(data, length, 1, fp);
		//�摜�t�@�C���̃N���[�Y
		fclose(fp);

		//�e�N�X�`���f�[�^�̍쐬
		glGenTextures(1, &id);

		/* �e�N�X�`�����j�b�g�P�ɐ؂�ւ��� */
//		glActiveTexture(GL_TEXTURE1);

		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		if (header.depth == 32)
			//�A���t�@�L��̃e�N�X�`���쐬
			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, header.width,
			header.height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
		else
			//�A���t�@�����̃e�N�X�`���쐬
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, header.width,
			header.height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, 0);
		/* �e�N�X�`�����j�b�g�O�ɖ߂� */
//		glActiveTexture(GL_TEXTURE0);
		//�i�[�̈�����
		delete[] data;
	}
	/*
	DrawImage
	left:�l�p�`�����W
	right:�l�p�`�E���W
	bottom:�l�p�`�����W
	top:�l�p�`����W
	tleft:�摜�����W
	tright:�摜�E���W
	tbottom:�摜�����W
	ttop:�摜����W
	*/
	void DrawImage(int left, int right, int bottom, int top, float tleft, float tright, float tbottom, float ttop) {
		//�e�N�X�`����L���ɂ���
		glEnable(GL_TEXTURE_2D);
		//�A���t�@�u�����h��L���ɂ���
		glEnable(GL_BLEND);
		//�u�����h���@���w��
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//�e�N�X�`�����w��
		glBindTexture(GL_TEXTURE_2D, id);

		float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		//�F�̐ݒ�
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

		glBegin(GL_TRIANGLES);
		glTexCoord2f(tleft / header.width, (header.height - ttop) / header.height);
		glVertex2d(left, top);
		glTexCoord2f(tleft / header.width, (header.height - tbottom) / header.height);
		glVertex2d(left, bottom);
		glTexCoord2f(tright / header.width, (header.height - tbottom) / header.height);
		glVertex2d(right, bottom);
		glTexCoord2f(tleft / header.width, (header.height - ttop) / header.height);
		glVertex2d(left, top);
		glTexCoord2f(tright / header.width, (header.height - tbottom) / header.height);
		glVertex2d(right, bottom);
		glTexCoord2f(tright / header.width, (header.height - ttop) / header.height);
		glVertex2d(right, top);
		glEnd();

		//�e�N�X�`�������
		glBindTexture(GL_TEXTURE_2D, 0);
		//�A���t�@�u�����h�𖳌�
		glDisable(GL_BLEND);
		//�e�N�X�`���𖳌�
		glDisable(GL_TEXTURE_2D);
	}

};
