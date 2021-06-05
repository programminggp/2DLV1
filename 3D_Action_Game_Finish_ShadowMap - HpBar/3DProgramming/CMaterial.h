#ifndef CMATERIAL_H
#define CMATERIAL_H

#include "CTexture.h"
#include "glut.h"

#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}
//�z��̃T�C�Y�擾���}�N����
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
/*
CMaterial
�}�e���A���N���X
*/
class CMaterial {
public:
	char *mpName; 	//�}�e���A����
	float mAmbient[4];
	float mDiffuse[4];
	float mPower;
	float mSpecular[3];
	float mEmissive[3];
	//�e�N�X�`���t�@�C����
	char *mpTextureFilename;
	//�e�N�X�`��ID
	GLuint mTextureId;
	CTexture mTexture;

	CMaterial();

	~CMaterial() {
		SAFE_DELETE_ARRAY(mpName);
		SAFE_DELETE_ARRAY(mpTextureFilename);
	}
	//�}�e���A����K�p����
	void SetMaterial();
	//�e�N�X�`���𖳌��ɂ���
	void UnSetMaterial();
};


#endif
