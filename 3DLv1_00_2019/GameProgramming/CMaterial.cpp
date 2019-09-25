#include "CMaterial.h"
#include <string.h>
#include "glut.h"

CMaterial::CMaterial() {
	memset(mName, 0, sizeof(mName));
	memset(mDiffuse, 0, sizeof(mDiffuse));
}

void CMaterial::SetMaterial() {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
}
