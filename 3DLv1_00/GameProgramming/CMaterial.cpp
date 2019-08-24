#include "CMaterial.h"
#include "glut.h"

CMaterial::CMaterial()
: mpName(0)
, mVertexNo(0)
{
}

CMaterial::~CMaterial() {
	if (mpName) {
		delete mpName;
	}
}

void CMaterial::SetMaterial() {
	
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mAmbient);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mDiffuse);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mSpecular);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mEmission);
//	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mShinness);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecular);
	//glMaterialfv(GL_FRONT, GL_EMISSION, mEmission);
	//glMaterialf(GL_FRONT, GL_SHININESS, mShinness);
}