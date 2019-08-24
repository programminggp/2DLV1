#include "CModel.h"
#include <stdio.h>
#include <assert.h>
#include "CMatrix.h"
#include "glut.h"

void Print(CVector &v) {
	printf("%10f, %10f, %10f\n", v.mX, v.mY, v.mZ);
}

CModel::CModel()
: mpVertex(0)
, mpNormal(0)
{}

CModel::~CModel() {
	for (int i = 0; i < mTriangles.size(); i++) {
		delete mTriangles[i];
	}
	for (int i = 0; i < mMaterials.size(); i++) {
		delete mMaterials[i];
	}
	if (mpVertex) {
		delete[] mpVertex;
	}
	if (mpNormal) {
		delete[] mpNormal;
	}
}

void CModel::Load(char *obj, char *mtl) {
	FILE *fp;
	char buffer[100];
	char buf[4][50];

	fp = fopen(mtl, "r");
	if (fp == NULL) {
		printf("file not found:%s\n", mtl);
		return;
	}

	CMaterial *material;

	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		sscanf(buffer, "%s %s %s %s\n", buf[0], buf[1], buf[2], buf[3]);
		if (strcmp(buf[0], "newmtl") == 0) {
			material = new CMaterial();
			material->mpName = new char[strlen(buf[1]) + 1];
			strcpy(material->mpName, buf[1]);
			mMaterials.push_back(material);
		}
		else if (strcmp(buf[0], "Ns") == 0) {
			material->mShinness = atof(buf[1]);
		}
		else if (strcmp(buf[0], "Ka") == 0) {
			material->mAmbient[0] = atof(buf[1]);
			material->mAmbient[1] = atof(buf[2]);
			material->mAmbient[2] = atof(buf[3]);
		}
		else if (strcmp(buf[0], "Kd") == 0) {
			material->mDiffuse[0] = atof(buf[1]);
			material->mDiffuse[1] = atof(buf[2]);
			material->mDiffuse[2] = atof(buf[3]);
		}
		else if (strcmp(buf[0], "Ks") == 0) {
			material->mSpecular[0] = atof(buf[1]);
			material->mSpecular[1] = atof(buf[2]);
			material->mSpecular[2] = atof(buf[3]);
		}
		else if (strcmp(buf[0], "Ke") == 0) {
			material->mEmission[0] = atof(buf[1]);
			material->mEmission[1] = atof(buf[2]);
			material->mEmission[2] = atof(buf[3]);
		}
		else if (strcmp(buf[0], "d") == 0) {
			material->mAmbient[3] = atof(buf[1]);
			material->mDiffuse[3] = atof(buf[1]);
			material->mSpecular[3] = atof(buf[1]);
			material->mEmission[3] = atof(buf[1]);
		}
	}
	//ダミーのマテリアルの追加
	material = new CMaterial();
	mMaterials.push_back(material);

	fclose(fp);

	fp = fopen(obj, "r");
	if (fp == NULL) {
		printf("file not found:%s\n", obj);
		return;
	}
	std::vector<CVector*> vertexes;
	std::vector<CVector*> normals;

	int materiaId = 0;
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		sscanf(buffer, "%s %s %s %s\n", buf[0], buf[1], buf[2], buf[3]);
		if (strcmp(buf[0], "v") == 0) {
			vertexes.push_back(new CVector(atof(buf[1]), atof(buf[2]), atof(buf[3])));
		}
		else if (strcmp(buf[0], "vn") == 0) {
			normals.push_back(new CVector(atof(buf[1]), atof(buf[2]), atof(buf[3])));
		}
		else if (strcmp(buf[0], "f") == 0) {
			int v[3], n[3];
			sscanf(buf[1], "%d//%d", &v[0], &n[0]);
			sscanf(buf[2], "%d//%d", &v[1], &n[1]);
			sscanf(buf[3], "%d//%d", &v[2], &n[2]);
			CTriangle *triangle = new CTriangle(*vertexes[v[0] - 1], *vertexes[v[1] - 1], *vertexes[v[2] - 1]);
			triangle->mNormal[0].mX = normals[n[0] - 1]->mX;
			triangle->mNormal[0].mY = normals[n[0] - 1]->mY;
			triangle->mNormal[0].mZ = normals[n[0] - 1]->mZ;
			triangle->mNormal[1].mX = normals[n[1] - 1]->mX;
			triangle->mNormal[1].mY = normals[n[1] - 1]->mY;
			triangle->mNormal[1].mZ = normals[n[1] - 1]->mZ;
			triangle->mNormal[2].mX = normals[n[2] - 1]->mX;
			triangle->mNormal[2].mY = normals[n[2] - 1]->mY;
			triangle->mNormal[2].mZ = normals[n[2] - 1]->mZ;
			triangle->mMaterialId = materiaId;
			mTriangles.push_back(triangle);
		}
		else if (strcmp(buf[0], "usemtl") == 0) {
			//ダミーマテリアルの前まで検索
			for (materiaId = 0; materiaId < mMaterials.size() - 1; materiaId++) {
				if (strcmp(mMaterials[materiaId]->mpName, buf[1]) == 0) {
					break;
				}
			}
			assert(materiaId < mMaterials.size());
		}		
	}

	for (int i = 0; i < vertexes.size(); i++) {
		delete vertexes[i];
	}

	for (int i = 0; i < normals.size(); i++) {
		delete normals[i];
	}

	mpVertex = new float[mTriangles.size() * 9];
	mpNormal = new float[mTriangles.size() * 9];
	int v = 0;
	for (int m = 0; m < mMaterials.size(); m++) {
		for (int i = 0; i < mTriangles.size(); i++) {
			if (mTriangles[i]->mMaterialId == m) {
				mpVertex[v++] = mTriangles[i]->mV[0].mX;
				mpVertex[v++] = mTriangles[i]->mV[0].mY;
				mpVertex[v++] = mTriangles[i]->mV[0].mZ;
				mpVertex[v++] = mTriangles[i]->mV[1].mX;
				mpVertex[v++] = mTriangles[i]->mV[1].mY;
				mpVertex[v++] = mTriangles[i]->mV[1].mZ;
				mpVertex[v++] = mTriangles[i]->mV[2].mX;
				mpVertex[v++] = mTriangles[i]->mV[2].mY;
				mpVertex[v++] = mTriangles[i]->mV[2].mZ;
				v -= 9;
				mpNormal[v++] = mTriangles[i]->mNormal[0].mX;
				mpNormal[v++] = mTriangles[i]->mNormal[0].mY;
				mpNormal[v++] = mTriangles[i]->mNormal[0].mZ;
				mpNormal[v++] = mTriangles[i]->mNormal[1].mX;
				mpNormal[v++] = mTriangles[i]->mNormal[1].mY;
				mpNormal[v++] = mTriangles[i]->mNormal[1].mZ;
				mpNormal[v++] = mTriangles[i]->mNormal[2].mX;
				mpNormal[v++] = mTriangles[i]->mNormal[2].mY;
				mpNormal[v++] = mTriangles[i]->mNormal[2].mZ;
			}
		}
		mMaterials[m]->mVertexNo = v / 3;
	}

	fclose(fp);

}

void CModel::Render(const CMatrix &matrix) {
	//glPushMatrix();
	//glMultMatrixf(&matrix.mM[0][0]);
	//for (int i = 0; i < mTriangles.size(); i++) {
	//	mMaterials[mTriangles[i]->mMaterialId]->SetMaterial();
	//	mTriangles[i]->Render(matrix);
	//	mTriangles[i]->Render();
	//}
	//glPopMatrix();
	//return;

	/* 頂点データ，法線データの配列を有効にする */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	/* 頂点データ，法線データの場所を指定する */
	glVertexPointer(3, GL_FLOAT, 0, mpVertex);
	glNormalPointer(GL_FLOAT, 0, mpNormal);

	glPushMatrix();
	glMultMatrixf(&matrix.mM[0][0]);

	int first = 0, count;
	for (int i = 0; i < mMaterials.size(); i++) {
		count = mMaterials[i]->mVertexNo - first;
		/* 頂点配列の図形を描画する */
		mMaterials[i]->SetMaterial();
		glDrawArrays(GL_TRIANGLES, first, count);
		first += count;
	}

	glPopMatrix();

	/* 頂点データ，法線データの配列を無効にする */
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	return;

}
