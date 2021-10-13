#include "Library.h"

#include <stdio.h>	//�t�@�C���̓��͂Ɏg�p
#include <string.h>
#include "SOIL.h"

CTexture::CTexture()
	: mId(0)
	, mpName(nullptr)
	, mRow(1)
	, mCol(1)
{
	memset(&mHeader, 0, sizeof(mHeader));
}

CTexture::CTexture(char* file)
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
	if (mpName != nullptr) {
		delete[] mpName;
		mpName = nullptr;
	}
}

#include <assert.h>

void CTexture::Load(const char* filename) {

	//null �ȊO�̓G���[
	assert(mpName == nullptr);

	mpName = new char[strlen(filename) + 1];
	strcpy(mpName, filename);

	//�摜�f�[�^
	unsigned char* data;

	data = SOIL_load_image(filename, &mHeader.width, &mHeader.height, &mHeader.depth, SOIL_LOAD_AUTO);

	if (data == 0)
	{
		printf("SOIL_load_image Error:filename %s\n", filename);
		return;
	}

	mId = SOIL_create_OGL_texture(data, mHeader.width, mHeader.height, mHeader.depth,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_POWER_OF_TWO
		| SOIL_FLAG_MIPMAPS
		| SOIL_FLAG_MULTIPLY_ALPHA
		| SOIL_FLAG_COMPRESS_TO_DXT
		| SOIL_FLAG_DDS_LOAD_DIRECT
		| SOIL_FLAG_INVERT_Y
		| SOIL_FLAG_TEXTURE_REPEATS
	);

	SOIL_free_image_data(data);

	assert(mId != 0);

	mHeader.depth *= 8;

	return;
}

void CTexture::Draw(float left, float right, float bottom, float top, int tleft, int tright, int tbottom, int ttop) const {
	DrawImage(left, right, bottom, top, tleft, tright, tbottom, ttop);
}

void CTexture::DrawImage(float left, float right, float bottom, float top, int tleft, int tright, int tbottom, int ttop) const {
	DrawImage(left, right, bottom, top,
		(float)tleft / mHeader.width,
		(float)tright / mHeader.width,
		(float)(mHeader.height - tbottom) / mHeader.height,
		(float)(mHeader.height - ttop) / mHeader.height);

	return;
}

void CTexture::SetParts(int row, int col) {
	mRow = row;
	mCol = col;
}

void CTexture::DrawImage(float left, float right, float bottom, float top, int index) const {
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
void CTexture::SetRowCol(int row, int col) {
	mRow = row;
	mCol = col;
}

void CTexture::DrawImage(float left, float right, float bottom, float top, float tleft, float tright, float tbottom, float ttop) const {
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
	glTexCoord2f(tleft, ttop);
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
