#include "CModel.h"
#include <stdio.h>

CModel::~CModel() {
	for (int i = 0; i < mTriangles.size(); i++) {
		delete mTriangles[i];
	}
	for (int i = 0; i < mMaterials.size(); i++) {
		delete mMaterials[i];
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

	fclose(fp);

	fp = fopen(obj, "r");
	if (fp == NULL) {
		printf("file not found:%s\n", obj);
		return;
	}
	std::vector<CVector*> vertexes;
	std::vector<CVector*> normals;

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
			CTriangle *triangle = new CTriangle(*vertexes[v[0]-1], *vertexes[v[1]-1], *vertexes[v[2]-1]);
			triangle->SetNormal(normals[n[0]-1]->mX, normals[n[0]-1]->mY, normals[n[0]-1]->mZ);
			mTriangles.push_back(triangle);
		}
	}

	for (int i = 0; i < vertexes.size(); i++) {
		delete vertexes[i];
	}

	for (int i = 0; i < normals.size(); i++) {
		delete normals[i];
	}

	fclose(fp);

}

void CModel::Render(const CMatrix &matrix) {
	for (int i = 0; i < mTriangles.size(); i++) {
		mTriangles[i]->Render(matrix);
	}
}
