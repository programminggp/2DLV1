#include "CMain2D.h"
#include "CSceneGame.h"


int main(void)
{
	CMain2D main;

	CSceneGame *scene = new CSceneGame();
	main.SetScene(scene);
	delete scene;
}
