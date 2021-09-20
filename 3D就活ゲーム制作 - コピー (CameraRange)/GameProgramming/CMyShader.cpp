#include "CMyShader.h"
#include "CLight.h"
#include "CModelX.h"
#include "CMatrix44.h"
#include "CModelObj.h"

void CMyShader::Render(CModelX *model, CMatrix44 *pCombinedMatrix) {
	//シェーダーを有効にする
	enable();
	for (int i = 0; i < model->mFrame.size(); i++) {
		if (model->mFrame[i]->mMesh.mFaceNum != 0) {
			//面のあるメッシュは描画する
			Render(model, &model->mFrame[i]->mMesh, pCombinedMatrix);
		}
	}
	//シェーダーを無効にする
	disable();
}
/*
メッシュの描画
*/
void CMyShader::Render(CModelX *model, CMesh *mesh, CMatrix44 *pCombinedMatrix) {
	//スキンマトリックス生成
	for (int i = 0; i < mesh->mSkinWeights.size(); i++) {
		//スキンメッシュの行列配列を設定する
		model->mpSkinningMatrix[mesh->mSkinWeights[i]->mFrameIndex]
			= pCombinedMatrix[mesh->mSkinWeights[i]->mFrameIndex] * mesh->mSkinWeights[i]->mOffset;
	}

	/*
	ライト設定
	*/
	CVector3 vec = CLight::getLight(0)->getDir();
	vec *= -1;
	//int lightId = glGetUniformLocation(getProgram(), "lightVec");  //ライトの向きを設定
	//glUniform3fv(lightId, 1, (float*)&vec);
	//glUniform3fv(glGetUniformLocation(getProgram(), "lightAmbientColor"), 1, (float*)&(CLight::getLight(0)->getAmbientColor()));
	//glUniform3fv(glGetUniformLocation(getProgram(), "lightDiffuseColor"), 1, (float*)&(CLight::getLight(0)->getDiffuseColor()));
	//スキンメッシュ行列設定
	int MatrixLocation = glGetUniformLocation(getProgram(), "Transforms");
	glUniformMatrix4fv(MatrixLocation, model->mFrame.size(), GL_FALSE, model->mpSkinningMatrix[0].f);
	/*
	ワールドトランスフォーム
	*/
//	int worldId = glGetUniformLocation(getProgram(), "WorldMatrix");
//	glUniformMatrix4fv(worldId, 1, GL_FALSE, model->mFrame[0]->mCombinedMatrix.f);

	/* テクスチャユニット1を指定する */
	glUniform1i(glGetUniformLocation(getProgram(), "DepthTexture"), 1);

	//頂点バッファをバインドする
	glBindBuffer(GL_ARRAY_BUFFER, mesh->mMyVertexBufferId);

	//頂点座標の位置を設定
	int idx = 0;
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(CMyVertex), (void*)idx);
	//法線ベクトルの位置を設定
	idx += sizeof(CVector3);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(CMyVertex), (void*)idx);
	//テクスチャマッピングデータの位置を設定
	idx += sizeof(CVector3);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(CMyVertex), (void*)idx);

	//スキンウェイトデータの位置を設定
	idx += sizeof(CVector2);
	int  weightLoc = glGetAttribLocation(getProgram(), "weights");
	glEnableVertexAttribArray(weightLoc);
	glVertexAttribPointer(weightLoc, 4, GL_FLOAT, GL_TRUE, sizeof(CMyVertex), (void*)idx);
	//スキンウェイトのインデックスデータの位置を設定
	idx += sizeof(float)* 4;
	int  indexLoc = glGetAttribLocation(getProgram(), "indices");
	glEnableVertexAttribArray(indexLoc);
	glVertexAttribPointer(indexLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CMyVertex), (void*)idx);

	//マテリアル毎に頂点を描画します
	int k = 0;

	for (int i = 0; i < mesh->mMaterial.size(); i++) {
		//マテリアルの値をシェーダーに設定
		SetShader(mesh->mMaterial[i]);
		//三角形描画、開始頂点番号、描画に使用する頂点数
		glDrawArrays(GL_TRIANGLES, k, mesh->mMaterialVertexCount[i]);	//DrawArrays:VertexIndexなし
		//開始位置計算
		k += mesh->mMaterialVertexCount[i];
		//マテリアルの解除
		mesh->mMaterial[i]->UnSetMaterial();
	}

	//無効にする
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//頂点バッファのバインド解除
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
/*
Objモデルの描画
*/
void CMyShader::Render(CModelObj *mesh) {
	//シェーダーを有効にする
	enable();
	/*
	ライト設定
	*/
	CVector3 vec = CLight::getLight(0)->getDir();
	vec *= -1;
	int lightId = glGetUniformLocation(getProgram(), "lightVec");  //ライトの向きを設定
	glUniform3fv(lightId, 1, (float*)&vec);
	glUniform3fv(glGetUniformLocation(getProgram(), "lightAmbientColor"), 1, (float*)&(CLight::getLight(0)->getAmbientColor()));
	glUniform3fv(glGetUniformLocation(getProgram(), "lightDiffuseColor"), 1, (float*)&(CLight::getLight(0)->getDiffuseColor()));
	//スキンメッシュ行列設定
	int MatrixLocation = glGetUniformLocation(getProgram(), "Transforms");
	glUniformMatrix4fv(MatrixLocation, 1, GL_FALSE, mesh->mMatrix.f);

	/* テクスチャユニット1を指定する */
	glUniform1i(glGetUniformLocation(getProgram(), "DepthTexture"), 1);

	//頂点バッファをバインドする
	glBindBuffer(GL_ARRAY_BUFFER, mesh->mMyVertexBufferId);

	//頂点座標の位置を設定
	int idx = 0;
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(CMyVertex), (void*)idx);
	//法線ベクトルの位置を設定
	idx += sizeof(CVector3);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(CMyVertex), (void*)idx);
	//テクスチャマッピングデータの位置を設定
	idx += sizeof(CVector3);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(CMyVertex), (void*)idx);

	//スキンウェイトデータの位置を設定
	idx += sizeof(CVector2);
	int  weightLoc = glGetAttribLocation(getProgram(), "weights");
	glEnableVertexAttribArray(weightLoc);
	glVertexAttribPointer(weightLoc, 4, GL_FLOAT, GL_TRUE, sizeof(CMyVertex), (void*)idx);
	//スキンウェイトのインデックスデータの位置を設定
	idx += sizeof(float)* 4;
	int  indexLoc = glGetAttribLocation(getProgram(), "indices");
	glEnableVertexAttribArray(indexLoc);
	glVertexAttribPointer(indexLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CMyVertex), (void*)idx);

	//マテリアル毎に頂点を描画します
	int k = 0;

	for (int i = 0; i < mesh->mMaterial.size(); i++) {
		//マテリアルの値をシェーダーに設定
		SetShader(mesh->mMaterial[i]);
		//三角形描画、開始頂点番号、描画に使用する頂点数
		glDrawArrays(GL_TRIANGLES, k, mesh->mMaterialVertexCount[i]);	//DrawArrays:VertexIndexなし
		//開始位置計算
		k += mesh->mMaterialVertexCount[i];
		//マテリアルの解除
		mesh->mMaterial[i]->UnSetMaterial();
	}

	//無効にする
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//頂点バッファのバインド解除
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//シェーダーを無効にする
	disable();
}
/*
マテリアルの値をシェーダーに設定する
*/
void CMyShader::SetShader(CMaterial *material) {
//	float mColorRGBA[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	int AmbientId = glGetUniformLocation(getProgram(), "Ambient");  //カラー設定
	glUniform4fv(AmbientId, 1, (GLfloat*)material->mDiffuse);

	int DiffuseId = glGetUniformLocation(getProgram(), "Diffuse");  //カラー設定
	glUniform4fv(DiffuseId, 1, (GLfloat*)material->mDiffuse);

	//int ColorRGAB_ID = glGetUniformLocation(getProgram(), "ColorRGBA");  //カラー設定　重ねてカラーの表示
	//glUniform4fv(ColorRGAB_ID, 1, (GLfloat*)mColorRGBA);

	int PowId = glGetUniformLocation(getProgram(), "Pow");  //強さを設定
	glUniform1f(PowId, material->mPower);

	int SpecularId = glGetUniformLocation(getProgram(), "Specular");  //カラー設定
	glUniform3fv(SpecularId, 1, (GLfloat*)material->mSpecular);

	int EmissiveId = glGetUniformLocation(getProgram(), "Emissive");  //カラー設定
	glUniform3fv(EmissiveId, 1, (GLfloat*)material->mEmissive);
	GLint samplerId = glGetUniformLocation(getProgram(), "Sampler");
	GLint textureFlg = glGetUniformLocation(getProgram(), "TextureFlg");
	if (material->mTextureId > 0) {
		//テクスチャあり
		material->SetMaterial();
		glUniform1i(samplerId, 0);//GL_TEXTURE0を適用
		glUniform1i(textureFlg, 0);//GL_TEXTURE0を適用
	}
	else
	{
		//テクスチャなし
		glUniform1i(textureFlg, -1);//GL_TEXTURE1を適用
	}
}
