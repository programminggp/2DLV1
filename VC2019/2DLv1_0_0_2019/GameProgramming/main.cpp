#include "CMain2D.h"
#include "CSceneGame.h"


int main(void)
{
	CMain2D main(800, 600);
	main.SetScene(new CSceneGame());
}
