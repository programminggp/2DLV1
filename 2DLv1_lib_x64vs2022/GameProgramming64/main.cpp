#include "main.h"
#include "Application.h"

#include <stdio.h>

#include "glut.h"

class Game
{
public:
	static void Start();
	static void Update();
};


void Game::Start()
{
	printf("gameStart\n");
}

void Game::Update()
{
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(400.0f, 0.0f, 0.0f);
	glVertex3f(400.0f, 300.0f, 0.0f);
	glVertex3f(0.0f, 300.0f, 0.0f);
	glEnd();
}

int main()
{
	Application app(
		//"Test",
		//WINDOW_WIDTH,
		//WINDOW_HEIGHT,
		//60,
		Game::Start,
		Game::Update
	);
	return app.main();
}