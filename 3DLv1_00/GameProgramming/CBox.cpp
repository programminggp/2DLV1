#include "CBox.h"

void CBox::Render(const CMatrix &m) {
	mMaterial.SetMaterial();
	for (int i = 0; i < 12; i++) {
		mT[i].Render(m);
	}
	mMaterial.UnSetMaterial();
}

void CBox::Set(float x, float y, float z, float w, float h, float d) {

	mT[0].SetVertex(x - w, y - h, z + d, x + w, y - h, z + d, x + w, y + h, z + d);
	mT[0].SetNormal(0.0f, 0.0f, 1.0f);
	mT[1].SetVertex(x - w, y - h, z + d, x + w, y + h, z + d, x - w, y + h, z + d);
	mT[1].SetNormal(0.0f, 0.0f, 1.0f);

	mT[2].SetVertex(x + w, y - h, z + d, x + w, y - h, z - d, x + w, y + h, z - d);
	mT[2].SetNormal(1.0f, 0.0f, 0.0f);
	mT[3].SetVertex(x + w, y - h, z + d, x + w, y + h, z - d, x + w, y + h, z + d);
	mT[3].SetNormal(1.0f, 0.0f, 0.0f);

	mT[4].SetVertex(x - w, y - h, z - d, x + w, y + h, z - d, x + w, y - h, z - d);
	mT[4].SetNormal(0.0f, 0.0f, -1.0f);
	mT[5].SetVertex(x - w, y - h, z - d, x - w, y + h, z - d, x + w, y + h, z - d);
	mT[5].SetNormal(0.0f, 0.0f, -1.0f);

	mT[6].SetVertex(x - w, y - h, z + d, x - w, y + h, z - d, x - w, y - h, z - d);
	mT[6].SetNormal(-1.0f, 0.0f, 0.0f);
	mT[7].SetVertex(x - w, y - h, z + d, x - w, y + h, z + d, x - w, y + h, z - d);
	mT[7].SetNormal(-1.0f, 0.0f, 0.0f);

	mT[8].SetVertex(x - w, y + h, z + d, x + w, y + h, z + d, x + w, y + h, z - d);
	mT[8].SetNormal(0.0f, 1.0f, 0.0f);
	mT[9].SetVertex(x - w, y + h, z + d, x + w, y + h, z - d, x - w, y + h, z - d);
	mT[9].SetNormal(0.0f, 1.0f, 0.0f);

	mT[10].SetVertex(x - w, y - h, z + d, x + w, y - h, z - d, x + w, y - h, z + d);
	mT[10].SetNormal(0.0f, -1.0f, 0.0f);
	mT[11].SetVertex(x - w, y - h, z + d, x - w, y - h, z - d, x + w, y - h, z - d);
	mT[11].SetNormal(0.0f, -1.0f, 0.0f);
}
