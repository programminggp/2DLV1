#include "CVertex.h"
#include <string.h>

CVertex::CVertex()
{
	memset(mTexCoord, 0, sizeof(mTexCoord));
	memset(mBoneWeight, 0, sizeof(mBoneWeight));
	memset(mBoneIndex, 0, sizeof(mBoneIndex));
	mBoneWeight[0] = 1.0f;
}
