//�W�����o�͂̃C���N���[�h
#include<string.h>
//CModel�̃C���N���[�h
#include"CModel.h"
//CVector�̃C���N���[�h
#include"CVector.h"
//CTriangle�̃C���N���[�h
#include"CTriangle.h"

//�f�t�H���g�R���X�g���N�^
CModel::CModel()
:mpVertex(nullptr), mpNormal(nullptr), mpTextureCoord(nullptr)
{

}


//���f���t�@�C���̓���
//Load(���f���t�@�C����,�}�e���A���t�@�C����)
void CModel::Load(char* obj, char* mtl) {
	//���_�f�[�^�̕ۑ��iCVector�^�j
	std::vector<CVector>vertex;
	//�@���f�[�^�̕ۑ��iCVector�^�j
	std::vector<CVector>normal;
	//�e�N�X�`���}�b�s���O�̕ۑ� (CVector�^)
	std::vector<CVector>uv;
	//�t�@�C���|�C���^�ϐ��̍쐬
	FILE* fp;
	//fopen(�t�@�C����,���[�h)
	//�I�[�v���o���Ȃ�����NULL��Ԃ�
	fp = fopen(mtl, "r");
	//�t�@�C���I�[�v���̃G���[�̔���
	//fp��NULL�̎��̓G���[
	if (fp == NULL) {
		//�R���\�[���ɃG���[���o�͂��Ė߂�
		printf("%s file open error\n", mtl);
		return;
	}
	//�t�@�C������f�[�^�����
	// ���̓G���A���쐬����
	char buf[256];
	//�}�e���A���C���f�b�N�X
	int idx = 0;
	//�t�@�C������P�s����
	// fgets(���̓G���A,�G���A�T�C�Y,�t�@�C���|�C���^)
	// �t�@�C���̍Ō�ɂȂ��NULL��Ԃ�
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//�f�[�^�𕪊�����
		char str[4][64] = { "","","","" };
		//�����񂩂�f�[�^��4�ϐ��֑������
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		//�擪��newmtl�̎��A�}�e���A����ǉ�����
		if (strcmp(str[0], "newmtl") == 0) {
			CMaterial* pm = new CMaterial();
			//�}�e���A�����̐ݒ�
			pm->Name(str[1]);
			//�}�e���A���̉ϒ��z��ɒǉ�
			mpMaterials.push_back(pm);
			//�z��̒������擾
			idx = mpMaterials.size() - 1;
		}
	
	
		//�擪��Kd�̎��ADiffuse��ݒ肷��
		else if (strcmp(str[0], "Kd") == 0) {
			mpMaterials[idx]->Diffuse()[0] = atof(str[1]);
			mpMaterials[idx]->Diffuse()[1] = atof(str[2]);
			mpMaterials[idx]->Diffuse()[2] = atof(str[3]);
		}
		//�擪��d�̎��Aa�l��ݒ肷��
		else if (strcmp(str[0], "d") == 0) {
			mpMaterials[idx]->Diffuse()[3] = atof(str[1]);
		}
		//�擪��map_Kd�̎��A�e�N�X�`������͂���
		else if (strcmp(str[0], "map_Kd") == 0) {
			mpMaterials[idx]->Texture()->Load(str[1]);
		}
	}
	//�t�@�C���̃N���[�Y
	fclose(fp);
	
	//�t�@�C���̃I�[�v��
	//fopen(�t�@�C����,���[�h)
	//�I�[�v���o���Ȃ�����NULL��Ԃ�
	fp = fopen(obj, "r");
	//�t�@�C���I�[�v���̃G���[�̔���
	//fp��NULL�̎��̓G���[
	if (fp == NULL) {
		//�R���\�[���ɃG���[���o�͂��Ė߂�
		printf("%s file open error\n", obj);
		return;
	}
//�t�@�C������P�s����
// fgets(���̓G���A,�G���A�T�C�Y,�t�@�C���|�C���^)
// �t�@�C���̍Ō�ɂȂ��NULL��Ԃ�
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//�f�[�^�𕪊�����
		char str[4][64] = { "","","","" };
		//�����񂩂�f�[�^���S�ϐ��֑������
		// sscanf(������,�ϊ��w��q,�ϐ�)
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		//�擪��newmtl�̎��A�}�e���A����ǉ�����
		if (strcmp(str[0], "newmtl") == 0) {
			CMaterial* pm = new CMaterial();
			//�}�e���A�����̐ݒ�
			pm->Name(str[1]);
			//�}�e���A���̉ϒ��z��ɒǉ�
			mpMaterials.push_back(pm);
			//�z��̒������擾
			idx = mpMaterials.size() - 1;
		}
		//������̔�r
		//strcmp(������P,������Q)
		//������P�ƕ�����Q�������Ƃ�0,�قȂ鎞�O�ȊO��Ԃ�
		// �擪��vn�̎��A���_��normal�ɒǉ�����
		if (strcmp(str[0], "vn") == 0) {
			normal.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		if (strcmp(str[0], "v") == 0) {
			//�ϒ��z��vertex�ɒǉ�����
			//atof(������) �����񂩂�float�^�̒l��Ԃ�
			vertex.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		//�擪��vt�̎��Auv�ɒǉ�����
		else if (strcmp(str[0], "vt") == 0) {
			//�ϒ��z��uv�ɒǉ�����
			//atof(������)�@�����񂩂�float�^�̒l��Ԃ�
			uv.push_back(CVector(atof(str[1]), atof(str[2]), 0.0));
		}
		//�擪��usemtl�̎��A�}�e���A���C���f�b�N�X���擾����
		else if (strcmp(str[0], "usemtl") == 0) {
			//�ϒ��z����ォ���r
			for (idx = mpMaterials.size() - 1; idx > 0; idx--) {
				//�������O�̃}�e���A��������΃��[�v�I��
				if (strcmp(mpMaterials[idx]->Name(), str[1]) == 0) {
					break; //���[�v����o��
				}
			}
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
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				//�}�e���A���ԍ��̐ݒ�
				t.MaterialIdx(idx);
				//�ϒ��z��mTriangles�ɎO�p�`��ǉ�
				mTriangles.push_back(t);
			}
			else {
				//�e�N�X�`���}�b�s���O�L��
				int u[3];//�e�N�X�`���}�b�s���O�̔ԍ��擾
				sscanf(str[1], "%d/%d/%d", &v[0], &u[0], &n[0]);
				sscanf(str[2], "%d/%d/%d", &v[1], &u[1], &n[1]);
				sscanf(str[3], "%d/%d/%d", &v[2], &u[2], &n[2]);
				//�O�p�`�쐬
				CTriangle t;
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				//�e�N�X�`���}�b�s���O�̐ݒ�
				t.SetUv(uv[u[0] - 1], uv[u[1] - 1], uv[u[2] - 1]);
				//�}�e���A���ԍ��̐ݒ�
				t.MaterialIdx(idx);
				//�ϒ��z��mTriangles�ɎO�p�`��ǉ�
				mTriangles.push_back(t);
			}
		}
	}
	//�t�@�C���̃N���[�Y
	fclose(fp);

	//���_�z��̍쐬
	//�S�Ă̍��W�̒l���}�e���A���̏��Ԃɕۑ�����
	mpVertex = new float[mTriangles.size() * 9];
	//�S�Ă̖@���̒l���}�e���A���̏��Ԃɕۑ�����
	mpNormal = new float[mTriangles.size() * 9];
	//�S�Ẵe�N�X�`���}�b�s���O�̒l���}�e���A���̏��Ԃɕۑ�����
	mpTextureCoord = new float[mTriangles.size() * 6];

	int v = 0, t = 0;
	//�}�e���A�����ɒ��_�z��ɐݒ肷��
	for (int i = 0; i < mpMaterials.size(); i++)
	{
		//�S�Ă̎O�p�`���r
		for (int j = 0; j < mTriangles.size(); j++)
		{
			//�}�e���A���ԍ�����v���鎞
			if (i == mTriangles[j].MaterialIdx()) {
				//���_�z��ɐݒ肷��
				//���_���W
				mpVertex[v++] = mTriangles[j].V0().X();
				mpVertex[v++] = mTriangles[j].V0().Y();
				mpVertex[v++] = mTriangles[j].V0().Z();
				mpVertex[v++] = mTriangles[j].V1().X();
				mpVertex[v++] = mTriangles[j].V1().Y();
				mpVertex[v++] = mTriangles[j].V1().Z();
				mpVertex[v++] = mTriangles[j].V2().X();
				mpVertex[v++] = mTriangles[j].V2().Y();
				mpVertex[v++] = mTriangles[j].V2().Z();
				v -= 9;
				//�@��
				mpNormal[v++] = mTriangles[j].N0().X();
				mpNormal[v++] = mTriangles[j].N0().Y();
				mpNormal[v++] = mTriangles[j].N0().Z();
				mpNormal[v++] = mTriangles[j].N1().X();
				mpNormal[v++] = mTriangles[j].N1().Y();
				mpNormal[v++] = mTriangles[j].N1().Z();
				mpNormal[v++] = mTriangles[j].N2().X();
				mpNormal[v++] = mTriangles[j].N2().Y();
				mpNormal[v++] = mTriangles[j].N2().Z();
				//�e�N�X�`���}�b�s���O
				mpTextureCoord[t++] = mTriangles[j].UV0().X();
				mpTextureCoord[t++] = mTriangles[j].UV0().Y();
				mpTextureCoord[t++] = mTriangles[j].UV1().X();
				mpTextureCoord[t++] = mTriangles[j].UV1().Y();
				mpTextureCoord[t++] = mTriangles[j].UV2().X();
				mpTextureCoord[t++] = mTriangles[j].UV2().Y();



			}
		}
		//���_����ݒ�
		mpMaterials[i]->VertexNum(v / 3);
	}
}

void CModel::Render()
{
	for (int i = 0; i < mTriangles.size(); i++)
	{
		mpMaterials[mTriangles[i].MaterialIdx()]->Enabled();
		mTriangles[i].Render();
		mpMaterials[mTriangles[i].MaterialIdx()]->Disabled();
	}
}

//�`��
void CModel::Render(const CMatrix& m) {
	//�s��̑ޔ�
	glPushMatrix();
	//�����s����|����
	glMultMatrixf(m.M());

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
	for (int i = 0; i < mpMaterials.size(); i++)
	{
		//�}�e���A����K�p����
		mpMaterials[i]->Enabled();
		//�`��ʒu����̃f�[�^�ŎO�p�`��`�悷��
		glDrawArrays(GL_TRIANGLES, first, mpMaterials[i]->VertexNum() - first);
		//�}�e���A���𖳌��ɂ���
		mpMaterials[i]->Disabled();
		//�`��ʒu���ړ�
		first = mpMaterials[i]->VertexNum();
	}
	//�s���߂�
	glPopMatrix();

	//���_���W�̔z��𖳌��ɂ���
	glDisableClientState(GL_VERTEX_ARRAY);
	//�@���̔z��𖳌��ɂ���
	glDisableClientState(GL_NORMAL_ARRAY);
	//�e�N�X�`���}�b�s���O�̔z��𖳌��ɂ���
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
//�f�X�g���N�^
CModel::~CModel()
{
	for (int i = 0; i < mpMaterials.size(); i++)
	{
		delete mpMaterials[i];
	}
	if (mpVertex != nullptr) 
	{
		//���_���W�z��폜
		delete[] mpVertex;
	}
	if (mpNormal != nullptr)
	{
		//�@���z��폜
		delete[] mpNormal;
	}
	if (mpTextureCoord != nullptr)
	{
		//�e�N�X�`���}�b�s���O�z��폜
		delete[] mpTextureCoord;

	}
	
}

