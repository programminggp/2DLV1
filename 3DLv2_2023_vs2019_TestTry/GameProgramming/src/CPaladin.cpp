#include "CPaladin.h"

#define PALADIN_MODEL_PATH "res\\paladin\\paladin.x"
#define ANIMATION_ATTACKSP1 "res\\paladin\\SwordAndShieldAttack.x"

CModelX CPaladin::sModel;

CPaladin::CPaladin()
{
	if (sModel.IsLoaded() == false)
	{
		sModel.Load(PALADIN_MODEL_PATH);
		//�A�j���[�V�����̒ǉ�
		sModel.AddAnimationSet(ANIMATION_ATTACKSP1);
	}
	Init(&sModel);
}
