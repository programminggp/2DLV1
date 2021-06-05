#include "CModelObj.h"
#include "CCollision.h"
#include <string.h>

/*
CMaterialObj::CMaterialObj() : m_pTex(NULL) ,m_TexDirectory(""){
}

void CMaterialObj::Map() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);

	if (m_pTex) {
		glBindTexture(GL_TEXTURE_2D, m_pTex->id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glEnable(GL_TEXTURE_2D);
	}
}

void CMaterialObj::Unmap() {
	if (m_pTex) {
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}
}

void CMaterialObj::Release() {
	if (m_pTex) {
		glDeleteTextures(1, &m_pTex->id);
		delete m_pTex;
		m_pTex = NULL;
	}
}
*/

bool CModelObj::LoadMaterial(char *path) {
	return LoadMaterial(path, 0);
}

bool CModelObj::LoadMaterial(char *path, char *newmtl) {
	char key[32];
	FILE* fp = fopen(path, "r");
	//�t�@�C�����J���Ȃ������ꍇ�̓G���[��\����false��Ԃ�
	if (fp == NULL) {
		printf("�t�@�C��������܂���%s\n", path);
		return false;
	}

	fscanf(fp, "%s", key);
	while (!feof(fp)) {
		CMaterial *m_material = new CMaterial();
		if (strcmp(key, "newmtl") == 0) {
			fscanf(fp, "%s", key);
			m_material->mpName = new char[strlen(key) + 1];
			strcpy(m_material->mpName, key);
			fscanf(fp, "%s", key);
			while (!feof(fp)) {
				if (strcmp(key, "newmtl") == 0) {
					break;
				}
				if (strcmp(key, "Ka") == 0) {
					fscanf(fp, "%f %f %f", &m_material->mAmbient[0], &m_material->mAmbient[1], &m_material->mAmbient[2]);
					m_material->mAmbient[3] = 1.0f;
				}
				else if (strcmp(key, "Kd") == 0) {
					fscanf(fp, "%f %f %f", &m_material->mDiffuse[0], &m_material->mDiffuse[1], &m_material->mDiffuse[2]);
					m_material->mDiffuse[3] = 1.0f;
				}
				else if (strcmp(key, "Ks") == 0) {
					fscanf(fp, "%f %f %f", &m_material->mSpecular[0], &m_material->mSpecular[1], &m_material->mSpecular[2]);
				}
				else if (strcmp(key, "Ns") == 0) {
					fscanf(fp, "%f", &m_material->mPower);
				}
				else if (strcmp(key, "d") == 0) {
					float aplha;
					fscanf(fp, "%f", &aplha);
					m_material->mAmbient[3] = aplha;
					m_material->mDiffuse[3] = aplha;
				}
				else if (strcmp(key, "map_Kd") == 0) {
					char str[128];
					fscanf(fp, "%s\n", str);
					m_material->mTexture.load(str);
					m_material->mTextureId = m_material->mTexture.id;
				}
				fscanf(fp, "%s", key);
			}
			mMaterial.push_back(m_material);
		}
		else {
			fscanf(fp, "%s", key);
		}
	}
	fclose(fp);
	return true;
}

CModelObj::CModelObj()
	:mpVertex(NULL), m_vertexNum(0), mMyVertexBufferId(0)
{
}

CModelObj::~CModelObj() {
	SAFE_DELETE_ARRAY(mpVertex);
	for (int i = 0; i < mMaterial.size(); i++) {
		delete mMaterial[i];
	}
//	Release();
}

bool CModelObj::Load(const char *path) {
	mTriangle.clear();
	//�t�@�C���|�C���^(fp)�̍쐬���J�����t�@�C���̃n���h����n���B
	FILE* fp = fopen(path, "r");
	//�t�@�C�����J���Ȃ������ꍇ�̓G���[��\����false��Ԃ�
	if (fp == NULL) {
		printf("�t�@�C��������܂���%s\n", path);
		return false;
	}
	//���W�f�[�^�p�J�E���^�[
	int	VCnt = 0;
	//�@���f�[�^�p�J�E���^�[
	int	NCnt = 0;
	//�e�N�X�`���[�R�[�h�p�J�E���^�[
	int	TCnt = 0;
	//�ʃf�[�^�p�J�E���^�[
	int	FCnt = 0;
	//�L�[���[�h�i�[�p
	char key[64];
	//�t�@�C���̖����łȂ���ΌJ��Ԃ�
	while (!feof(fp)) {
		//key���N���A
		key[0] = 0;
		//1�P��@�������ǂݍ���
		fscanf(fp, "%s", key);
		//�ǂݍ��񂾃L�[���[�h���uv�v�Ȃ���W�f�[�^�J�E���^�[���J�E���g�A�b�v
		if (strcmp(key, "v") == 0) {
			VCnt++;
		}
		else
			//�ǂݍ��񂾃L�[���[�h���uf�v�Ȃ�ʃf�[�^�J�E���^�[���J�E���g�A�b�v
			if (strcmp(key, "f") == 0) {
				FCnt++;
			}
			else
				//�ǂݍ��񂾃L�[���[�h���uvn�v�Ȃ�@���f�[�^�J�E���^�[���J�E���g�A�b�v
				if (strcmp(key, "vn") == 0) {
					NCnt++;
				}
				else
					//�ǂݍ��񂾃L�[���[�h���uvt�v�Ȃ�e�N�X�`���[�R�[�h�f�[�^�J�E���^�[���J�E���g�A�b�v
					if (strcmp(key, "vt") == 0) {
						TCnt++;
					}
					else
						//�ǂݍ��񂾃L�[���[�h���umtllib�v�Ȃ�}�e���A���t�@�C���̓ǂݍ���
						if (strcmp(key, "mtllib") == 0) {
							char str[64];
							fscanf(fp, "%s\n", str);
							LoadMaterial(str);
						}
	}
	//printf("VCnt %d\n", VCnt);

	//���W�f�[�^�̐������z����쐬
	CVector3 *pVertex = new CVector3[VCnt];
	//�@���f�[�^�̐������z����쐬
	CVector3 *pNormal = new CVector3[NCnt];
	//�e�N�X�`���[�R�[�h�f�[�^�̐������z����쐬
	CVector2 *pTexCoord = new CVector2[TCnt];
	//�����蔻��p�O�p�`
	CTriangle t;
	//�`��p�̒��_�f�[�^�̒��_�����v�Z�@3*�ʂ̐�
	m_vertexNum = 3 * FCnt;
//	m_vertexNum = 6 * FCnt;
	//�`��p���_�z����쐬
	//m_pVertexAry = new CVector3[m_vertexNum];
	////�`��p�@���z����쐬
	//m_pNormalAry = new CVector3[m_vertexNum];
	////�`��p�e�N�X�`���[�R�[�h�z����쐬
	//m_pTexCoordAry = new CVector2[m_vertexNum];
	mpVertex = new CVertex[m_vertexNum];
	//�ǂݍ��񂾍��W�f�[�^��0���珇�ԂɊi�[���邽�߁A�J�E���^�[��0�ɖ߂�
	VCnt = 0;
	NCnt = 0;
	TCnt = 0;
	//�ǂݏ����̈ʒu���t�@�C���̐擪�ɖ߂�
	fseek(fp, 0, SEEK_SET);
	//�t�@�C���̖����łȂ���ΌJ��Ԃ�
	while (!feof(fp)) {
		//key���N���A
		key[0] = 0;
		//�L�[���[�h�̓ǂݍ���
		fscanf(fp, "%s", key);
		//�u���v��ǂݍ��񂾂�A���W�f�[�^��ǂݍ���
		if (strcmp(key, "v") == 0) {
			fscanf(fp, "%f %f %f", &pVertex[VCnt].x, &pVertex[VCnt].y, &pVertex[VCnt].z);
			//�ǂݍ��ݐ�����̃f�[�^��
			VCnt++;
		}
		else//�uvn�v��ǂݍ��񂾂�A�@���f�[�^��ǂݍ���
		if (strcmp(key, "vn") == 0) {
			fscanf(fp, "%f %f %f", &pNormal[NCnt].x, &pNormal[NCnt].y, &pNormal[NCnt].z);
			//�ǂݍ��ݐ�����̃f�[�^��
			NCnt++;
		}
		else//�uvt�v��ǂݍ��񂾂�A�e�N�X�`���[�R�[�h�f�[�^��ǂݍ���
		if (strcmp(key, "vt") == 0) {
			fscanf(fp, "%f %f", &pTexCoord[TCnt].x, &pTexCoord[TCnt].y);
			pTexCoord[TCnt].y = 1.0f - pTexCoord[TCnt].y;
			//�ǂݍ��ݐ�����̃f�[�^��
			TCnt++;
		}
	}
	//�`��p���_�z��ւ̍��W�f�[�^�i�[��ԍ�
	int idx = 0, cnt = 0;
	for (int i = 0; i < mMaterial.size(); i++) {
		//�ǂݏ����̈ʒu���t�@�C���̐擪�ɖ߂�
		fseek(fp, 0, SEEK_SET);
		//key���N���A
		key[0] = 0;
		//�L�[���[�h�̓ǂݍ���
		fscanf(fp, "%s", key);
		//�t�@�C���̖����łȂ���ΌJ��Ԃ�
		while (!feof(fp)) {
			if (strcmp(key, "usemtl") == 0) {
				//�L�[���[�h�̓ǂݍ���
				fscanf(fp, "%s", key);
				if (strcmp(key, mMaterial[i]->mpName) == 0) {
					//key���N���A
					key[0] = 0;
					//�L�[���[�h�̓ǂݍ���
					fscanf(fp, "%s", key);
					//�t�@�C���̖����łȂ���ΌJ��Ԃ�
					while (!feof(fp)) {
						if (strcmp(key, "usemtl") == 0) {
							break;
						}
						if (strcmp(key, "f") == 0) {
							int v1, v2, v3;
							int n1, n2, n3;
							int t1, t2, t3;
							if (TCnt > 0) {
								fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);

								mpVertex[idx].mPosition = pVertex[v1 - 1];
								mpVertex[idx].mNormal = pNormal[n1 - 1];
								mpVertex[idx++].mTextureCoords = pTexCoord[t1 - 1];

								//m_pVertexAry[idx] = pVertex[v1 - 1];		//���_�P�̍��W�f�[�^
								//m_pNormalAry[idx] = pNormal[n1 - 1];		//���_�P�̖@���f�[�^
								//m_pTexCoordAry[idx++] = pTexCoord[t1 - 1];	//���_�P�̃e�N�X�`���[�R�[�h�f�[�^

								mpVertex[idx].mPosition = pVertex[v2 - 1];
								mpVertex[idx].mNormal = pNormal[n2 - 1];
								mpVertex[idx++].mTextureCoords = pTexCoord[t2 - 1];

								//m_pVertexAry[idx] = pVertex[v2 - 1];		//���_�Q�̍��W�f�[�^
								//m_pNormalAry[idx] = pNormal[n2 - 1];		//���_�Q�̖@���f�[�^
								//m_pTexCoordAry[idx++] = pTexCoord[t2 - 1];	//���_�Q�̃e�N�X�`���[�R�[�h�f�[�^

								mpVertex[idx].mPosition = pVertex[v3 - 1];
								mpVertex[idx].mNormal = pNormal[n3 - 1];
								mpVertex[idx++].mTextureCoords = pTexCoord[t3 - 1];

								//m_pVertexAry[idx] = pVertex[v3 - 1];
								//m_pNormalAry[idx] = pNormal[n3 - 1];
								//m_pTexCoordAry[idx++] = pTexCoord[t3 - 1];
							}
							else {
								fscanf(fp, "%d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3);

								mpVertex[idx].mPosition = pVertex[v1 - 1];
								mpVertex[idx++].mNormal = pNormal[n1 - 1];

								//m_pVertexAry[idx] = pVertex[v1 - 1];			//���_�P�̍��W�f�[�^
								//m_pNormalAry[idx++] = pNormal[n1 - 1];			//���_�P�̖@���f�[�^

								mpVertex[idx].mPosition = pVertex[v2 - 1];
								mpVertex[idx++].mNormal = pNormal[n2 - 1];

								//m_pVertexAry[idx] = pVertex[v2 - 1];		//���_�Q�̍��W�f�[�^
								//m_pNormalAry[idx++] = pNormal[n2 - 1];		//���_�Q�̖@���f�[�^

								mpVertex[idx].mPosition = pVertex[v3 - 1];
								mpVertex[idx++].mNormal = pNormal[n3 - 1];

								//m_pVertexAry[idx] = pVertex[v3 - 1];
								//m_pNormalAry[idx++] = pNormal[n3 - 1];
							}
							/*�O�p�`�ݒ�*/
							t.SetVertex(mpVertex[idx - 3].mPosition, mpVertex[idx - 2].mPosition, mpVertex[idx - 1].mPosition);
							mTriangle.push_back(t);
						}
						//�L�[���[�h�̓ǂݍ���
						fscanf(fp, "%s", key);
					}
				}
				else {
					//�L�[���[�h�̓ǂݍ���
					fscanf(fp, "%s", key);
				}
			}
			else {
				//�L�[���[�h�̓ǂݍ���
				fscanf(fp, "%s", key);
			}
		}
		mMaterialVertexCount.push_back(idx - cnt);
		cnt = idx;
	}
	m_vertexNum = idx;
	//�V�F�[�_�[�ǂݍ���
//	mShader.load("skinmesh.vert", "skinmesh.flag");
	mShader.load("shadow.vert", "shadow.flag");
	CreateVertexBuffer();
	//�ꎞ�f�[�^���
	delete[] pVertex;
	delete[] pNormal;
	delete[] pTexCoord;
	return true;
}

void CModelObj::Render() {

	mShader.Render(this);

	return;

	glPushMatrix();

	glMultMatrixf(mMatrix.f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	int offset = 0;
	glVertexPointer(3, GL_FLOAT, sizeof(CVertex), (void*)mpVertex);
	offset += sizeof(mpVertex->mPosition);
	glNormalPointer(GL_FLOAT, sizeof(CVertex), ((unsigned char*)mpVertex) + offset);
	offset += sizeof(mpVertex->mNormal);
	glTexCoordPointer(2, GL_FLOAT, sizeof(CVertex), ((unsigned char*)mpVertex) + offset);

	if (mMaterial[0]->mTextureId > 0) {
	}

//	glDrawArrays(GL_TRIANGLES, 0, m_vertexNum);
	int idx = 0;
	for (int i = 0; i < mMaterial.size(); i++) {
		mMaterial[i]->SetMaterial();
		glDrawArrays(GL_TRIANGLES, idx, mMaterialVertexCount[i]);
		idx += mMaterialVertexCount[i];
		mMaterial[i]->UnSetMaterial();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glPopMatrix();

}

void CModelObj::Release() {
	//if (m_pVertexAry) { delete[] m_pVertexAry; m_pVertexAry = NULL; }
	//if (m_pNormalAry) { delete[] m_pNormalAry; m_pNormalAry = NULL; }
	//if (m_pTexCoordAry) { delete[] m_pTexCoordAry; m_pTexCoordAry = NULL; }
}

/*�O�p�`�����蔻��ǉ�*/
void CModelObj::AddCollisionManager() {
	for each (CTriangle triangle in mTriangle)
	{
		//�O�p�`�R���C�_�𐶐�����
		new CTriangleCollider(CCollider::EGROUND, triangle.mVertex[0], triangle.mVertex[1], triangle.mVertex[2]);
	}
}

/*
���_�o�b�t�@���쐬����
*/
void CModelObj::CreateVertexBuffer() {
	//���b�V�����Ɉ��쐬����΂悢
	if (mMyVertexBufferId > 0)
		return;
	//���_�o�b�t�@�̍쐬
	glGenBuffers(1, &mMyVertexBufferId);
	//���_�o�b�t�@���o�C���h
	glBindBuffer(GL_ARRAY_BUFFER, mMyVertexBufferId);
	//�o�C���h�����o�b�t�@�Ƀf�[�^��]��
	glBufferData(GL_ARRAY_BUFFER, sizeof(CMyVertex)*m_vertexNum, mpVertex, GL_STATIC_DRAW);
	//�o�C���h����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//�z����
//	delete[] mpVertex;
}
