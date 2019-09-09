#ifndef CENEMY
#define CENEMY

#include "CCharacter.h"
#include "CCollider.h"

class CEnemy : public CCharacter {
public:
	CCollider mCollider;

	CEnemy(CModel *model, float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz);

	void Update();
};


#endif
