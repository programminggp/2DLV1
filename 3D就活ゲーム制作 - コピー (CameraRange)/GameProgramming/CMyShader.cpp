#include "CMyShader.h"
#include "CLight.h"
#include "CModelX.h"
#include "CMatrix44.h"
#include "CModelObj.h"

void CMyShader::Render(CModelX *model, CMatrix44 *pCombinedMatrix) {
	//�V�F�[�_�[��L���ɂ���
	enable();
	for (int i = 0; i < model->mFrame.size(); i++) {
		if (model->mFrame[i]->mMesh.mFaceNum != 0) {
			//�ʂ̂��郁�b�V���͕`�悷��
			Render(model, &model->mFrame[i]->mMesh, pCombinedMatrix);
		}
	}
	//�V�F�[�_�[�𖳌��ɂ���
	disable();
}
/*
���b�V���̕`��
*/
void CMyShader::Render(CModelX *model, CMesh *mesh, CMatrix44 *pCombinedMatrix) {
	//�X�L���}�g���b�N�X����
	for (int i = 0; i < mesh->mSkinWeights.size(); i++) {
		//�X�L�����b�V���̍s��z���ݒ肷��
		model->mpSkinningMatrix[mesh->mSkinWeights[i]->mFrameIndex]
			= pCombinedMatrix[mesh->mSkinWeights[i]->mFrameIndex] * mesh->mSkinWeights[i]->mOffset;
	}

	/*
	���C�g�ݒ�
	*/
	CVector3 vec = CLight::getLight(0)->getDir();
	vec *= -1;
	//int lightId = glGetUniformLocation(getProgram(), "lightVec");  //���C�g�̌�����ݒ�
	//glUniform3fv(lightId, 1, (float*)&vec);
	//glUniform3fv(glGetUniformLocation(getProgram(), "lightAmbientColor"), 1, (float*)&(CLight::getLight(0)->getAmbientColor()));
	//glUniform3fv(glGetUniformLocation(getProgram(), "lightDiffuseColor"), 1, (float*)&(CLight::getLight(0)->getDiffuseColor()));
	//�X�L�����b�V���s��ݒ�
	int MatrixLocation = glGetUniformLocation(getProgram(), "Transforms");
	glUniformMatrix4fv(MatrixLocation, model->mFrame.size(), GL_FALSE, model->mpSkinningMatrix[0].f);
	/*
	���[���h�g�����X�t�H�[��
	*/
//	int worldId = glGetUniformLocation(getProgram(), "WorldMatrix");
//	glUniformMatrix4fv(worldId, 1, GL_FALSE, model->mFrame[0]->mCombinedMatrix.f);

	/* �e�N�X�`�����j�b�g1���w�肷�� */
	glUniform1i(glGetUniformLocation(getProgram(), "DepthTexture"), 1);

	//���_�o�b�t�@���o�C���h����
	glBindBuffer(GL_ARRAY_BUFFER, mesh->mMyVertexBufferId);

	//���_���W�̈ʒu��ݒ�
	int idx = 0;
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(CMyVertex), (void*)idx);
	//�@���x�N�g���̈ʒu��ݒ�
	idx += sizeof(CVector3);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(CMyVertex), (void*)idx);
	//�e�N�X�`���}�b�s���O�f�[�^�̈ʒu��ݒ�
	idx += sizeof(CVector3);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(CMyVertex), (void*)idx);

	//�X�L���E�F�C�g�f�[�^�̈ʒu��ݒ�
	idx += sizeof(CVector2);
	int  weightLoc = glGetAttribLocation(getProgram(), "weights");
	glEnableVertexAttribArray(weightLoc);
	glVertexAttribPointer(weightLoc, 4, GL_FLOAT, GL_TRUE, sizeof(CMyVertex), (void*)idx);
	//�X�L���E�F�C�g�̃C���f�b�N�X�f�[�^�̈ʒu��ݒ�
	idx += sizeof(float)* 4;
	int  indexLoc = glGetAttribLocation(getProgram(), "indices");
	glEnableVertexAttribArray(indexLoc);
	glVertexAttribPointer(indexLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CMyVertex), (void*)idx);

	//�}�e���A�����ɒ��_��`�悵�܂�
	int k = 0;

	for (int i = 0; i < mesh->mMaterial.size(); i++) {
		//�}�e���A���̒l���V�F�[�_�[�ɐݒ�
		SetShader(mesh->mMaterial[i]);
		//�O�p�`�`��A�J�n���_�ԍ��A�`��Ɏg�p���钸�_��
		glDrawArrays(GL_TRIANGLES, k, mesh->mMaterialVertexCount[i]);	//DrawArrays:VertexIndex�Ȃ�
		//�J�n�ʒu�v�Z
		k += mesh->mMaterialVertexCount[i];
		//�}�e���A���̉���
		mesh->mMaterial[i]->UnSetMaterial();
	}

	//�����ɂ���
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//���_�o�b�t�@�̃o�C���h����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
/*
Obj���f���̕`��
*/
void CMyShader::Render(CModelObj *mesh) {
	//�V�F�[�_�[��L���ɂ���
	enable();
	/*
	���C�g�ݒ�
	*/
	CVector3 vec = CLight::getLight(0)->getDir();
	vec *= -1;
	int lightId = glGetUniformLocation(getProgram(), "lightVec");  //���C�g�̌�����ݒ�
	glUniform3fv(lightId, 1, (float*)&vec);
	glUniform3fv(glGetUniformLocation(getProgram(), "lightAmbientColor"), 1, (float*)&(CLight::getLight(0)->getAmbientColor()));
	glUniform3fv(glGetUniformLocation(getProgram(), "lightDiffuseColor"), 1, (float*)&(CLight::getLight(0)->getDiffuseColor()));
	//�X�L�����b�V���s��ݒ�
	int MatrixLocation = glGetUniformLocation(getProgram(), "Transforms");
	glUniformMatrix4fv(MatrixLocation, 1, GL_FALSE, mesh->mMatrix.f);

	/* �e�N�X�`�����j�b�g1���w�肷�� */
	glUniform1i(glGetUniformLocation(getProgram(), "DepthTexture"), 1);

	//���_�o�b�t�@���o�C���h����
	glBindBuffer(GL_ARRAY_BUFFER, mesh->mMyVertexBufferId);

	//���_���W�̈ʒu��ݒ�
	int idx = 0;
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(CMyVertex), (void*)idx);
	//�@���x�N�g���̈ʒu��ݒ�
	idx += sizeof(CVector3);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(CMyVertex), (void*)idx);
	//�e�N�X�`���}�b�s���O�f�[�^�̈ʒu��ݒ�
	idx += sizeof(CVector3);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(CMyVertex), (void*)idx);

	//�X�L���E�F�C�g�f�[�^�̈ʒu��ݒ�
	idx += sizeof(CVector2);
	int  weightLoc = glGetAttribLocation(getProgram(), "weights");
	glEnableVertexAttribArray(weightLoc);
	glVertexAttribPointer(weightLoc, 4, GL_FLOAT, GL_TRUE, sizeof(CMyVertex), (void*)idx);
	//�X�L���E�F�C�g�̃C���f�b�N�X�f�[�^�̈ʒu��ݒ�
	idx += sizeof(float)* 4;
	int  indexLoc = glGetAttribLocation(getProgram(), "indices");
	glEnableVertexAttribArray(indexLoc);
	glVertexAttribPointer(indexLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CMyVertex), (void*)idx);

	//�}�e���A�����ɒ��_��`�悵�܂�
	int k = 0;

	for (int i = 0; i < mesh->mMaterial.size(); i++) {
		//�}�e���A���̒l���V�F�[�_�[�ɐݒ�
		SetShader(mesh->mMaterial[i]);
		//�O�p�`�`��A�J�n���_�ԍ��A�`��Ɏg�p���钸�_��
		glDrawArrays(GL_TRIANGLES, k, mesh->mMaterialVertexCount[i]);	//DrawArrays:VertexIndex�Ȃ�
		//�J�n�ʒu�v�Z
		k += mesh->mMaterialVertexCount[i];
		//�}�e���A���̉���
		mesh->mMaterial[i]->UnSetMaterial();
	}

	//�����ɂ���
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//���_�o�b�t�@�̃o�C���h����
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//�V�F�[�_�[�𖳌��ɂ���
	disable();
}
/*
�}�e���A���̒l���V�F�[�_�[�ɐݒ肷��
*/
void CMyShader::SetShader(CMaterial *material) {
//	float mColorRGBA[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	int AmbientId = glGetUniformLocation(getProgram(), "Ambient");  //�J���[�ݒ�
	glUniform4fv(AmbientId, 1, (GLfloat*)material->mDiffuse);

	int DiffuseId = glGetUniformLocation(getProgram(), "Diffuse");  //�J���[�ݒ�
	glUniform4fv(DiffuseId, 1, (GLfloat*)material->mDiffuse);

	//int ColorRGAB_ID = glGetUniformLocation(getProgram(), "ColorRGBA");  //�J���[�ݒ�@�d�˂ăJ���[�̕\��
	//glUniform4fv(ColorRGAB_ID, 1, (GLfloat*)mColorRGBA);

	int PowId = glGetUniformLocation(getProgram(), "Pow");  //������ݒ�
	glUniform1f(PowId, material->mPower);

	int SpecularId = glGetUniformLocation(getProgram(), "Specular");  //�J���[�ݒ�
	glUniform3fv(SpecularId, 1, (GLfloat*)material->mSpecular);

	int EmissiveId = glGetUniformLocation(getProgram(), "Emissive");  //�J���[�ݒ�
	glUniform3fv(EmissiveId, 1, (GLfloat*)material->mEmissive);
	GLint samplerId = glGetUniformLocation(getProgram(), "Sampler");
	GLint textureFlg = glGetUniformLocation(getProgram(), "TextureFlg");
	if (material->mTextureId > 0) {
		//�e�N�X�`������
		material->SetMaterial();
		glUniform1i(samplerId, 0);//GL_TEXTURE0��K�p
		glUniform1i(textureFlg, 0);//GL_TEXTURE0��K�p
	}
	else
	{
		//�e�N�X�`���Ȃ�
		glUniform1i(textureFlg, -1);//GL_TEXTURE1��K�p
	}
}
