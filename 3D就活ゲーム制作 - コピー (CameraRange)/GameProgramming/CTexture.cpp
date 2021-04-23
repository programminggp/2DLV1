#include "CTexture.h"
#include <stdio.h>	//�t�@�C���̓��͂Ɏg�p
#include <string.h>

//std::map<std::string, CTexture>CTexture::mTexFile;

CTexture::CTexture()
	: mId(0)
	, mpName(0)
	, mRow(1)
	, mCol(1)
{
}

CTexture::CTexture(char *file)
	: CTexture()
{
	Load(file);
}

CTexture::~CTexture() {
	Destory();
}

void CTexture::Destory() {
	//�e�N�X�`���f�[�^������΍폜����
	if (mId != 0) {
		//�e�N�X�`���f�[�^�̍폜
		glDeleteTextures(1, &mId);
		mId = 0;
	}
	if (mpName) {
		delete[] mpName;
		mpName = 0;
	}
}

void CTexture::Load(const char* filename) {
	//if (mTexFile.count(filename)) {
	//	*this = mTexFile[filename];
	//	return;
	//}
	//�摜�f�[�^
	unsigned char *data, *data2;
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
	fread(&mHeader, sizeof(mHeader), 1, fp);
	//�摜�f�[�^�̃o�C�g�����v�Z����
	int length = mHeader.width * mHeader.height * mHeader.depth / 8;
	//�摜�f�[�^�̊i�[�̈���m��
	data2 = new unsigned char[length];
	data = new unsigned char[length];
	//�摜�f�[�^���w�b�_�̑�������ǂݍ���
	fread(data2, length, 1, fp);
	//�摜�t�@�C���̃N���[�Y
	fclose(fp);
	
	for (int i = 0; i < mHeader.width * mHeader.height; i++) {
		int x, y;
//		if (mHeader.discripter >> 4 & 0x01) {
		if (mHeader.discripter & 0x10) {
			x = mHeader.width - i % mHeader.width - 1;
		}
		else {
			x = i % mHeader.width;
		}
//		if (mHeader.discripter >> 5 & 0x01) {
		if (mHeader.discripter & 0x20) {
			y = mHeader.height - i / mHeader.width - 1;
		}
		else {
			y = i / mHeader.width;
		}
		x = x * mHeader.depth / 8;
		y = y * mHeader.width * mHeader.depth / 8;
		for (int j = 0; j < mHeader.depth / 8; j++) {
			data[x + y + j] = data2[i * mHeader.depth / 8 + j];
		}
	}

	//�e�N�X�`���f�[�^�̍쐬
	glGenTextures(1, &mId);
	//mTexFile[filename] = *this;

	/* �e�N�X�`�����j�b�g�P�ɐ؂�ւ��� */
//	glActiveTexture(GL_TEXTURE1);

	glBindTexture(GL_TEXTURE_2D, mId);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if (mHeader.depth == 32)
		//�A���t�@�L��̃e�N�X�`���쐬
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, mHeader.width,
		mHeader.height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
	else
		//�A���t�@�����̃e�N�X�`���쐬
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, mHeader.width,
		mHeader.height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	/* �e�N�X�`�����j�b�g�O�ɖ߂� */
//	glActiveTexture(GL_TEXTURE0);
	//�i�[�̈�����
	delete[] data;
	delete[] data2;
}

void CTexture::Draw(float left, float right, float bottom, float top, float tleft, float tright, float tbottom, float ttop) {
	DrawImage(left, right, bottom, top, tleft, tright, tbottom, ttop);
}

void CTexture::DrawImage(float left, float right, float bottom, float top, float tleft, float tright, float tbottom, float ttop) {
	//�e�N�X�`����L���ɂ���
	glEnable(GL_TEXTURE_2D);
	//�A���t�@�u�����h��L���ɂ���
	glEnable(GL_BLEND);
	//�u�����h���@���w��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//�e�N�X�`�����w��
	glBindTexture(GL_TEXTURE_2D, mId);

	float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//�F�̐ݒ�
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
//	glColor4fv(diffuse);

	glBegin(GL_TRIANGLES);
	glTexCoord2f(tleft,  ttop);
	glVertex2d(left, top);
	glTexCoord2f(tleft, tbottom);
	glVertex2d(left, bottom);
	glTexCoord2f(tright, tbottom);
	glVertex2d(right, bottom);
	glTexCoord2f(tleft, ttop);
	glVertex2d(left, top);
	glTexCoord2f(tright, tbottom);
	glVertex2d(right, bottom);
	glTexCoord2f(tright, ttop);
	glVertex2d(right, top);
	glEnd();

	//�e�N�X�`�������
	glBindTexture(GL_TEXTURE_2D, 0);
	//�A���t�@�u�����h�𖳌�
	glDisable(GL_BLEND);
	//�e�N�X�`���𖳌�
	glDisable(GL_TEXTURE_2D);
}

void CTexture::Draw(float left, float right, float bottom, float top, int tleft, int tright, int tbottom, int ttop) {
	DrawImage(left, right, bottom, top, tleft, tright, tbottom, ttop);
}

void CTexture::DrawImage(float left, float right, float bottom, float top, int tleft, int tright, int tbottom, int ttop) {
	DrawImage(left, right, bottom, top,
		(float)tleft / mHeader.width,
		(float)tright / mHeader.width,
		(float)(mHeader.height - tbottom) / mHeader.height,
		(float)(mHeader.height - ttop) / mHeader.height);

	return;
/*
	//�e�N�X�`����L���ɂ���
	glEnable(GL_TEXTURE_2D);
	//�A���t�@�u�����h��L���ɂ���
	glEnable(GL_BLEND);
	//�u�����h���@���w��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//�e�N�X�`�����w��
	glBindTexture(GL_TEXTURE_2D, mId);

	float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//�F�̐ݒ�
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glColor4fv(diffuse);

	glBegin(GL_TRIANGLES);
	glTexCoord2f(tleft / mHeader.width, (mHeader.height - ttop) / mHeader.height);
	glVertex2d(left, top);
	glTexCoord2f(tleft / mHeader.width, (mHeader.height - tbottom) / mHeader.height);
	glVertex2d(left, bottom);
	glTexCoord2f(tright / mHeader.width, (mHeader.height - tbottom) / mHeader.height);
	glVertex2d(right, bottom);
	glTexCoord2f(tleft / mHeader.width, (mHeader.height - ttop) / mHeader.height);
	glVertex2d(left, top);
	glTexCoord2f(tright / mHeader.width, (mHeader.height - tbottom) / mHeader.height);
	glVertex2d(right, bottom);
	glTexCoord2f(tright / mHeader.width, (mHeader.height - ttop) / mHeader.height);
	glVertex2d(right, top);
	glEnd();

	//�e�N�X�`�������
	glBindTexture(GL_TEXTURE_2D, 0);
	//�A���t�@�u�����h�𖳌�
	glDisable(GL_BLEND);
	//�e�N�X�`���𖳌�
	glDisable(GL_TEXTURE_2D);
*/
}

void CTexture::SetParts(int row, int col) {
	mRow = row;
	mCol = col;
}

void CTexture::DrawImage(float left, float right, float bottom, float top, int index) {
	int row = index / mCol + 1;
	int col = index % mCol;
	DrawImage(left, right, bottom, top,
		mHeader.width * col++ / mCol,
		mHeader.width * col / mCol,
		mHeader.height * row-- / mRow,
		mHeader.height * row / mRow);
}

//�s���񐔂̐ݒ�
//SetRowCol(�s��, ��)
void CTexture::SetRowCol(int row , int col) {
	mRow = row;
	mCol = col;
}
