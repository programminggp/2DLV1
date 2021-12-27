#include "glew.h"
#include "CMyShader.h"
//#include "CLight.h"
#include "CModelX.h"
#include "CMatrix.h"
#include "CModel.h"
#include "CVertex.h"


void CMyShader::Render(CModelX* model, CMatrix* pCombinedMatrix) {
	//�V�F�[�_�[��L���ɂ���
	Enable();
	for (size_t i = 0; i < model->Frames().size(); i++) {
		if (model->Frames()[i]->Mesh().FaceNum() != 0) {
			//�ʂ̂��郁�b�V���͕`�悷��
			Render(model, &model->Frames()[i]->Mesh(), pCombinedMatrix);
		}
	}
	//�V�F�[�_�[�𖳌��ɂ���
	Disable();
}
/*
���b�V���̕`��
*/
void CMyShader::Render(CModelX* model, CMesh* mesh, CMatrix* pCombinedMatrix) {
	//�X�L���}�g���b�N�X����
	for (size_t i = 0; i < mesh->SkinWeights().size(); i++) {
		//�X�L�����b�V���̍s��z���ݒ肷��
		model->SkinningMatrix()[mesh->SkinWeights()[i]->FrameIndex()]
			//			= pCombinedMatrix[mesh->mSkinWeights[i]->mFrameIndex] * mesh->mSkinWeights[i]->mOffset;
			= mesh->SkinWeights()[i]->Offset() * pCombinedMatrix[mesh->SkinWeights()[i]->FrameIndex()];
	}

	/*
	���C�g�ݒ�
	*/
	CVector vec(100.0f, 700.0f, -300.0f), ambient(0.9f, 0.9f, 0.9f), diffuse(1.0f, 1.0f, 1.0f);
	vec = vec.Normalize();
	int lightId = glGetUniformLocation(GetProgram(), "lightVec");  //���C�g�̌�����ݒ�
	glUniform3fv(lightId, 1, (float*)&vec);
	glUniform3fv(glGetUniformLocation(GetProgram(), "lightAmbientColor"), 1, (float*)&ambient);
	glUniform3fv(glGetUniformLocation(GetProgram(), "lightDiffuseColor"), 1, (float*)&diffuse);
	//�X�L�����b�V���s��ݒ�
	int MatrixLocation = glGetUniformLocation(GetProgram(), "Transforms");
	glUniformMatrix4fv(MatrixLocation, model->Frames().size(), GL_FALSE, model->SkinningMatrix()[0].M());
	/*
	���[���h�g�����X�t�H�[��
	*/
	//	int worldId = glGetUniformLocation(getProgram(), "WorldMatrix");
	//	glUniformMatrix4fv(worldId, 1, GL_FALSE, model->mFrame[0]->mCombinedMatrix.f);

	/* �e�N�X�`�����j�b�g1���w�肷�� */
	glUniform1i(glGetUniformLocation(GetProgram(), "DepthTexture"), 1);

	//���_�o�b�t�@���o�C���h����
	glBindBuffer(GL_ARRAY_BUFFER, mesh->MyVertexBufferId());

	//���_���W�̈ʒu��ݒ�
	int idx = 0;
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(CVertex), (void*)idx);
	//�@���x�N�g���̈ʒu��ݒ�
	idx += sizeof(CVector);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(CVertex), (void*)idx);
	//�e�N�X�`���}�b�s���O�f�[�^�̈ʒu��ݒ�
	idx += sizeof(CVector);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(CVertex), (void*)idx);

	//�X�L���E�F�C�g�f�[�^�̈ʒu��ݒ�
	idx += sizeof(CVector);
	int  weightLoc = glGetAttribLocation(GetProgram(), "weights");
	glEnableVertexAttribArray(weightLoc);
	glVertexAttribPointer(weightLoc, 4, GL_FLOAT, GL_TRUE, sizeof(CVertex), (void*)idx);
	//�X�L���E�F�C�g�̃C���f�b�N�X�f�[�^�̈ʒu��ݒ�
	idx += sizeof(float) * 4;
	int  indexLoc = glGetAttribLocation(GetProgram(), "indices");
	glEnableVertexAttribArray(indexLoc);
	glVertexAttribPointer(indexLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex), (void*)idx);

	//�}�e���A�����ɒ��_��`�悵�܂�
	int k = 0;

	for (size_t i = 0; i < mesh->Materials().size(); i++) {
		//�}�e���A���̒l���V�F�[�_�[�ɐݒ�
		SetShader(mesh->Materials()[i]);
		//�O�p�`�`��A�J�n���_�ԍ��A�`��Ɏg�p���钸�_��
		glDrawArrays(GL_TRIANGLES, k, mesh->MaterialVertexCount()[i]);	//DrawArrays:VertexIndex�Ȃ�
		//�J�n�ʒu�v�Z
		k += mesh->MaterialVertexCount()[i];
		//�}�e���A���̉���
		mesh->Materials()[i]->Disabled();
	}

	//�����ɂ���
	glDisableVertexAttribArray(weightLoc);
	glDisableVertexAttribArray(indexLoc);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//���_�o�b�t�@�̃o�C���h����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
/*
Obj���f���̕`��

void CMyShader::Render(CModel *mesh) {
//�V�F�[�_�[��L���ɂ���
Enable();

CVector vec(100.0f, 700.0f, -300.0f), ambient(0.9f, 0.9f, 0.9f), diffuse(1.0f, 1.0f, 1.0f);
vec = vec.Normalize();
int lightId = glGetUniformLocation(GetProgram(), "lightVec");  //���C�g�̌�����ݒ�
glUniform3fv(lightId, 1, (float*)&vec);
glUniform3fv(glGetUniformLocation(GetProgram(), "lightAmbientColor"), 1, (float*)&ambient);
glUniform3fv(glGetUniformLocation(GetProgram(), "lightDiffuseColor"), 1, (float*)&diffuse);
//�X�L�����b�V���s��ݒ�
int MatrixLocation = glGetUniformLocation(GetProgram(), "Transforms");
glUniformMatrix4fv(MatrixLocation, 1, GL_FALSE, mesh->mMatrix.f);

//�e�N�X�`�����j�b�g1���w�肷��
glUniform1i(glGetUniformLocation(GetProgram(), "DepthTexture"), 1);

//���_�o�b�t�@���o�C���h����
glBindBuffer(GL_ARRAY_BUFFER, mesh->mMyVertexBufferId);

//���_���W�̈ʒu��ݒ�
int idx = 0;
glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3, GL_FLOAT, sizeof(CVertex), (void*)idx);
//�@���x�N�g���̈ʒu��ݒ�
idx += sizeof(CVector);
glEnableClientState(GL_NORMAL_ARRAY);
glNormalPointer(GL_FLOAT, sizeof(CVertex), (void*)idx);
//�e�N�X�`���}�b�s���O�f�[�^�̈ʒu��ݒ�
idx += sizeof(CVector);
glEnableClientState(GL_TEXTURE_COORD_ARRAY);
glTexCoordPointer(2, GL_FLOAT, sizeof(CVertex), (void*)idx);

//�X�L���E�F�C�g�f�[�^�̈ʒu��ݒ�
idx += sizeof(CVector);
int  weightLoc = glGetAttribLocation(GetProgram(), "weights");
glEnableVertexAttribArray(weightLoc);
glVertexAttribPointer(weightLoc, 4, GL_FLOAT, GL_TRUE, sizeof(CVertex), (void*)idx);
//�X�L���E�F�C�g�̃C���f�b�N�X�f�[�^�̈ʒu��ݒ�
idx += sizeof(float)* 4;
int  indexLoc = glGetAttribLocation(GetProgram(), "indices");
glEnableVertexAttribArray(indexLoc);
glVertexAttribPointer(indexLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex), (void*)idx);

//�}�e���A�����ɒ��_��`�悵�܂�
int k = 0;

for (int i = 0; i < mesh->mMaterials.size(); i++) {
//�}�e���A���̒l���V�F�[�_�[�ɐݒ�
SetShader(&mesh->mMaterials[i]);
//�O�p�`�`��A�J�n���_�ԍ��A�`��Ɏg�p���钸�_��
glDrawArrays(GL_TRIANGLES, k, mesh->mMaterialVertexCount[i]);	//DrawArrays:VertexIndex�Ȃ�
//�J�n�ʒu�v�Z
k += mesh->mMaterialVertexCount[i];
//�}�e���A���̉���
mesh->mMaterials[i].Disabled();
}

//�����ɂ���
glDisableClientState(GL_VERTEX_ARRAY);
glDisableClientState(GL_NORMAL_ARRAY);
glDisableClientState(GL_TEXTURE_COORD_ARRAY);

//���_�o�b�t�@�̃o�C���h����
glBindBuffer(GL_ARRAY_BUFFER, 0);

//�V�F�[�_�[�𖳌��ɂ���
Disable();
}
*/
/*
�}�e���A���̒l���V�F�[�_�[�ɐݒ肷��
*/
void CMyShader::SetShader(CMaterial* material) {
	//	float mColorRGBA[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	int AmbientId = glGetUniformLocation(GetProgram(), "Ambient");  //�J���[�ݒ�
	glUniform4fv(AmbientId, 1, (GLfloat*)material->Diffuse());

	int DiffuseId = glGetUniformLocation(GetProgram(), "Diffuse");  //�J���[�ݒ�
	glUniform4fv(DiffuseId, 1, (GLfloat*)material->Diffuse());

	//int ColorRGAB_ID = glGetUniformLocation(getProgram(), "ColorRGBA");  //�J���[�ݒ�@�d�˂ăJ���[�̕\��
	//glUniform4fv(ColorRGAB_ID, 1, (GLfloat*)mColorRGBA);

	int PowId = glGetUniformLocation(GetProgram(), "Pow");  //������ݒ�
	glUniform1f(PowId, material->Power());

	int SpecularId = glGetUniformLocation(GetProgram(), "Specular");  //�J���[�ݒ�
	glUniform3fv(SpecularId, 1, (GLfloat*)material->Specular());

	int EmissiveId = glGetUniformLocation(GetProgram(), "Emissive");  //�J���[�ݒ�
	glUniform3fv(EmissiveId, 1, (GLfloat*)material->Emissive());
	GLint samplerId = glGetUniformLocation(GetProgram(), "Sampler");
	GLint textureFlg = glGetUniformLocation(GetProgram(), "TextureFlg");
	//if (material->mTextureId > 0) {
	if (material->Texture()->Id()) {
		//�e�N�X�`������
		material->Enabled();
		glUniform1i(samplerId, 0);//GL_TEXTURE0��K�p
		glUniform1i(textureFlg, 0);//GL_TEXTURE0��K�p
	}
	else
	{
		//�e�N�X�`���Ȃ�
		glUniform1i(textureFlg, -1);//GL_TEXTURE1��K�p
	}
}
