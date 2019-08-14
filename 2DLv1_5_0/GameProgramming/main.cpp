#include "CMain2D.h"
#include "CSceneGame.h"
#include "CSceneManager.h"


int main(void)
{
	CMain2D main;
//	main.SetScene(new CSceneGame());
	main.SetScene(new CSceneManager());
}
