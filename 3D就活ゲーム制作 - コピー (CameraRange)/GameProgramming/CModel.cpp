#include "CModel.h"
//�W�����o�͂̃C���N���[�h
#include <stdio.h>
//������֐��̃C���N���[�h
#include <string.h>
//CVector�̃C���N���[�h
#include "CVector.h"

//���f���t�@�C���̓���
//Load(���f���t�@�C����, �}�e���A���t�@�C����)
void CModel::Load(char *obj, char *mtl) {
	//�t�@�C���|�C���^�ϐ��̍쐬
	FILE *fp;

	//���̓G���A���쐬���ړ�
	char buf[256];

	//�t�@�C���̃I�[�v��
	//fopen(�t�@�C����,���[�h)
	//�I�[�v���ł��Ȃ�����NULL��Ԃ�
	fp = fopen(mtl, "r");
	//�t�@�C���I�[�v���G���[�̔���
	//fp��NULL�̎��̓G���[
	if (fp == NULL) {
		//�R���\�[���ɃG���[�o�͂��Ė߂�
		printf("%s file open error\n", mtl);
		return;
	}

	//�}�e���A���C���f�b�N�X
	int idx = 0;
	//�t�@�C������f�[�^�����
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//�f�[�^�𕪊�����
		char str[4][64] = {"","","",""};
		//�����񂩂�f�[�^��4�ϐ��֑������
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		//�擪��newmtl�̎��A�}�e���A����ǉ�����
		if (strcmp(str[0], "newmtl") == 0) {
			CMaterial material;
			//�X�}�[�g�|�C���^�̐���
			std::shared_ptr<CTexture> t(new CTexture());
			//�X�}�[�g�|�C���^�̑��
			material.mpTexture = t;
			//�}�e���A�����̃R�s�[
			strncpy(material.mName, str[1], sizeof(material.mName) - 1);
			//�}�e���A���̉ϒ��z��ɒǉ�
			mMaterials.push_back(material);
			//�z��̒������擾
			idx = mMaterials.size() - 1;
		}
		//�擪��Kd�̎��ADiffuse��ݒ肷��
		else if (strcmp(str[0], "Kd") == 0) {
			mMaterials[idx].mDiffuse[0] = atof(str[1]);
			mMaterials[idx].mDiffuse[1] = atof(str[2]);
			mMaterials[idx].mDiffuse[2] = atof(str[3]);
		}
		//�擪��d�̎��A���l��ݒ肷��
		else if (strcmp(str[0], "d") == 0) {
			mMaterials[idx].mDiffuse[3] = atof(str[1]);
		}
		//�擪��map_Kd�̎��A�e�N�X�`������͂���
		else if (strcmp(str[0], "map_Kd") == 0) {
			mMaterials[idx].mpTexture->Load(str[1]);
		}
		//���͂����l���R���\�[���ɏo�͂���
		//		printf("%s", buf);
	}

	//�t�@�C���̃N���[�Y
	fclose(fp);


	//�t�@�C���̃I�[�v��
	//fopen(�t�@�C����,���[�h)
	//�I�[�v���ł��Ȃ�����NULL��Ԃ�
	fp = fopen(obj, "r");
	//�t�@�C���I�[�v���G���[�̔���
	//fp��NULL�̎��̓G���[
	if (fp == NULL) {
		//�R���\�[���ɃG���[�o�͂��Ė߂�
		printf("%s file open error\n", obj);
		return;
	}

	//�t�@�C������f�[�^�����
	//���_�f�[�^�̕ۑ�(CVector�^)
	std::vector<CVector> vertex;
	//�@���f�[�^�̕ۑ�(CVector�^)
	std::vector<CVector> normal;
	//�e�N�X�`���}�b�s���O�̕ۑ�(CVector�^)
	std::vector<CVector> uv;

	//�t�@�C������1�s����
	//fgets(���̓G���A,�G���A�T�C�Y,�t�@�C���|�C���^)
	//�t�@�C���̍Ō�ɂȂ��NULL��Ԃ�
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//�f�[�^�𕪊�����
		char str[4][64] = { "", "", "", "" };
		//�����񂩂�f�[�^��4�ϐ��֑������
		//sscanf(������, �ϊ��w��q, �ϐ�)
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		//������̔�r
		//strcmp(������1, ������2)
		//������0�A�قȂ鎞0�ȊO��Ԃ�
		//�擪��v�̎��A���_��vertex�ɒǉ�����
		if (strcmp(str[0], "v") == 0) {
			//�ϒ��z��vertex�ɒǉ�
			//atof(������)�@�����񂩂�float�^�̒l��Ԃ�
			vertex.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		//�擪��f�̎��A�O�p�`���쐬���Ēǉ�����
		else if (strcmp(str[0], "f") == 0) {
			//���_�Ɩ@���̔ԍ��쐬
			int v[3], n[3];
			//�e�N�X�`���}�b�s���O�̗L���𔻒�
			if (strstr(str[1], "//")) {
				//���_�Ɩ@���̔ԍ��擾
				sscanf(str[1], "%d//%d", &v[0], &n[0]);
				sscanf(str[2], "%d//%d", &v[1], &n[1]);
				sscanf(str[3], "%d//%d", &v[2], &n[2]);
				//�O�p�`�쐬
				CTriangle t;
				t.SetVertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.SetNormal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				//�}�e���A���ԍ��̐ݒ�
				t.mMaterialIdx = idx;
				//�ϒ��z��mTriangles�ɎO�p�`��ǉ�
				mTriangles.push_back(t);
			}
			else {
				//�e�N�X�`���}�b�s���O�L��
				int u[3]; //�e�N�X�`���}�b�s���O�̔ԍ�
				//���_�Ɩ@���̔ԍ��擾�ƃ}�b�s���O�̔ԍ��擾
				sscanf(str[1], "%d/%d/%d", &v[0], &u[0], &n[0]);
				sscanf(str[2], "%d/%d/%d", &v[1], &u[1], &n[1]);
				sscanf(str[3], "%d/%d/%d", &v[2], &u[2], &n[2]);
				//�O�p�`�쐬
				CTriangle t;
				t.SetVertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.SetNormal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				//�e�N�X�`���}�b�s���O�̐ݒ�
				t.mUv[0] = uv[u[0] - 1];
				t.mUv[1] = uv[u[1] - 1];
				t.mUv[2] = uv[u[2] - 1];
				//�}�e���A���ԍ��̐ݒ�
				t.mMaterialIdx = idx;
				//�ϒ��z��mTriangles�ɎO�p�`��ǉ�
				mTriangles.push_back(t);
			}
		}
		//�擪��vn�̎��A�@����normal�ɒǉ�����
		else if (strcmp(str[0], "vn") == 0) {
			//�ϒ��z��normal�ɒǉ�
			//atof(������)�@�����񂩂�float�^�̒l��Ԃ�
			normal.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		//�擪��usemtl�̎��A�}�e���A���C���f�b�N�X���擾����
		else if (strcmp(str[0], "usemtl") == 0) {
			//�ϒ��z����ォ���r
			for (idx = mMaterials.size() - 1; idx > 0;  idx--) {
				//�������O�̃}�e���A��������΃��[�v�I��
				if (strcmp(mMaterials[idx].mName, str[1]) == 0) {
					break;
				}
			}
		}
		//�擪��vt�̎��Auv�ɒǉ�����
		else if (strcmp(str[0], "vt") == 0) {
			//�ϒ��z��uv�ɒǉ�
			//atof(������)�@�����񂩂�float�^�̒l��Ԃ�
			uv.push_back(CVector(atof(str[1]), atof(str[2]), 0.0));
		}

		//���͂����l���R���\�[���ɏo�͂���
//		printf("%s", buf);
	}

	//�t�@�C���̃N���[�Y
	fclose(fp);

	//���_�z��̍쐬
	//�S�Ă̍��W�̒l�����Ԃɕۑ�����
	mpVertex = new float[mTriangles.size() * 9];
	//�S�Ă̖@���̒l�����Ԃɕۑ�����
	mpNormal = new float[mTriangles.size() * 9];
	//�S�Ẵe�N�X�`���}�b�s���O�̒l�����Ԃɕۑ�����
	mpTextureCoord = new float[mTriangles.size() * 6];

	int v = 0, t = 0;
	//�}�e���A�����ɒ��_�z��ɐݒ肷��
	for (int i = 0; i < mMaterials.size(); i++) {
		//�S�Ă̎O�p�`���r
		for (int j = 0; j < mTriangles.size(); j++) {
			//�}�e���A���ԍ�����v���鎞
			if (i == mTriangles[j].mMaterialIdx) {
				//���_�z��ɐݒ肷��
				//���_���W
				mpVertex[v++] = mTriangles[j].mV[0].mX;
				mpVertex[v++] = mTriangles[j].mV[0].mY;
				mpVertex[v++] = mTriangles[j].mV[0].mZ;
				mpVertex[v++] = mTriangles[j].mV[1].mX;
				mpVertex[v++] = mTriangles[j].mV[1].mY;
				mpVertex[v++] = mTriangles[j].mV[1].mZ;
				mpVertex[v++] = mTriangles[j].mV[2].mX;
				mpVertex[v++] = mTriangles[j].mV[2].mY;
				mpVertex[v++] = mTriangles[j].mV[2].mZ;
				v -= 9;
				//�@��
				mpNormal[v++] = mTriangles[j].mN[0].mX;
				mpNormal[v++] = mTriangles[j].mN[0].mY;
				mpNormal[v++] = mTriangles[j].mN[0].mZ;
				mpNormal[v++] = mTriangles[j].mN[1].mX;
				mpNormal[v++] = mTriangles[j].mN[1].mY;
				mpNormal[v++] = mTriangles[j].mN[1].mZ;
				mpNormal[v++] = mTriangles[j].mN[2].mX;
				mpNormal[v++] = mTriangles[j].mN[2].mY;
				mpNormal[v++] = mTriangles[j].mN[2].mZ;
				//�e�N�X�`���}�b�s���O
				mpTextureCoord[t++] = mTriangles[j].mUv[0].mX;
				mpTextureCoord[t++] = mTriangles[j].mUv[0].mY;
				mpTextureCoord[t++] = mTriangles[j].mUv[1].mX;
				mpTextureCoord[t++] = mTriangles[j].mUv[1].mY;
				mpTextureCoord[t++] = mTriangles[j].mUv[2].mX;
				mpTextureCoord[t++] = mTriangles[j].mUv[2].mY;
			}
		}
		//���_����ݒ�
		mMaterials[i].mVertexNum = v / 3;
	}
}

//�`��
void CModel::Render() {
	//�ϒ��z��̑傫�������J��Ԃ�
	for (int i = 0; i < mTriangles.size(); i++) {
		//�}�e���A���̓K�p
		mMaterials[mTriangles[i].mMaterialIdx].Enabled();
		//�ϒ��z��ɓY�����ŃA�N�Z�X����
		mTriangles[i].Render();
		//�}�e���A���𖳌�
		mMaterials[mTriangles[i].mMaterialIdx].Disabled();
	}
}

//Render(�����s��)
void CModel::Render(const CMatrix &m) {
	//�s��̑ޔ�
	glPushMatrix();
	//�����s����|����
	glMultMatrixf(&m.mM[0][0]);

	//���_���W�̔z���L���ɂ���
	glEnableClientState(GL_VERTEX_ARRAY);
	//�@���̔z���L���ɂ���
	glEnableClientState(GL_NORMAL_ARRAY);
	//�e�N�X�`���}�b�s���O�̔z���L���ɂ���
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//���_���W�̔z����w�肷��
	glVertexPointer(3, GL_FLOAT, 0, mpVertex);
	//�@���̔z����w�肷��
	glNormalPointer(GL_FLOAT, 0, mpNormal);
	//�e�N�X�`���R�[�h�̔z����w�肷��
	glTexCoordPointer(2, GL_FLOAT, 0, mpTextureCoord);

	int first = 0; //�`��ʒu
	//�}�e���A�����ɕ`�悷��
	for (int i = 0; i < mMaterials.size(); i++) {
		//�}�e���A����K�p����
		mMaterials[i].Enabled();
		//�`��ʒu����̃f�[�^�ŎO�p�`��`�悵�܂�
		glDrawArrays(GL_TRIANGLES, first, mMaterials[i].mVertexNum - first);
		//�}�e���A���𖳌��ɂ���
		mMaterials[i].Disabled();
		//�`��ʒu���ړ�
		first = mMaterials[i].mVertexNum;
	}
	//�s���߂�
	glPopMatrix();

	//���_���W�̔z��𖳌��ɂ���
	glDisableClientState(GL_VERTEX_ARRAY);
	//�@���̔z��𖳌��ɂ���
	glDisableClientState(GL_NORMAL_ARRAY);
	//�e�N�X�`���}�b�s���O�̔z��𖳌��ɂ���
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	return;
}

//�f�t�H���g�R���X�g���N�^
CModel::CModel()
: mpVertex(0), mpNormal(0), mpTextureCoord(0)
{
}
//�f�X�g���N�^
CModel::~CModel() {
	if (mpVertex) {
		//���_���W�z��폜
		delete[] mpVertex;
	}
	if (mpNormal) {
		//�@���z��폜
		delete[] mpNormal;
	}
	if (mpTextureCoord) {
		//�e�N�X�`���}�b�s���O�z��폜
		delete[] mpTextureCoord;
	}
}
