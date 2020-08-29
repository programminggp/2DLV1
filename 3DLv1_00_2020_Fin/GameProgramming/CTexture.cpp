#include "CTexture.h"

//SetRowCol(�s��, ��)
void CTexture::SetRowCol(int row, int col) {
	mRows = row;
	mCols = col;
}

/*
�摜�t�@�C���̓ǂݍ��݁i�e�N�X�`���t�@�C���̓ǂݍ��݁j
*/
void CTexture::Load(const char* filename) {
	//�e�N�X�`���f�[�^������΍폜����
	if (mId) {
		//�e�N�X�`���f�[�^�̍폜
		glDeleteTextures(1, &mId);
		mId = 0;
	}
	if (mpName) {
		delete[] mpName;
		mpName = 0;
	}
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
	fread(&mHeader, sizeof(mHeader), 1, fp);
	//�摜�f�[�^�̃o�C�g�����v�Z����
	int length = mHeader.width * mHeader.height * mHeader.depth / 8;
	//�摜�f�[�^�̊i�[�̈���m��
	data = new unsigned char[length];
	//�摜�f�[�^���w�b�_�̑�������ǂݍ���
	fread(data, length, 1, fp);
	//�摜�t�@�C���̃N���[�Y
	fclose(fp);

	//�e�N�X�`���f�[�^�̍쐬
	glGenTextures(1, &mId);
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
void CTexture::DrawImage(int left, int right, int bottom, int top, float tleft, float tright, float tbottom, float ttop) {
	//�e�N�X�`����L���ɂ���
	glEnable(GL_TEXTURE_2D);
	//�A���t�@�u�����h��L���ɂ���
	glEnable(GL_BLEND);
	//�u�����h���@���w��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//�e�N�X�`�����w��
	glBindTexture(GL_TEXTURE_2D, mId);

//	float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//�F�̐ݒ�
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

	//glDisable(GL_LIGHTING);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

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

	//		glEnable(GL_LIGHTING);

	//�e�N�X�`�������
	glBindTexture(GL_TEXTURE_2D, 0);
	//�A���t�@�u�����h�𖳌�
	glDisable(GL_BLEND);
	//�e�N�X�`���𖳌�
	glDisable(GL_TEXTURE_2D);
}
//DrawImage(�����W, �E���W, �����W, ����W, �R�}��)
void CTexture::DrawImage(int left, int right, int bottom, int top, int frame)  {
	int col = frame % mCols;
	int row = frame / mCols + 1;
	DrawImage(left, right, bottom, top,
		(float)mHeader.width * col++ / mCols,
		(float)mHeader.width * col / mCols,
		(float)mHeader.height * row-- / mRows,
		(float)mHeader.height * row / mRows
		);
}
