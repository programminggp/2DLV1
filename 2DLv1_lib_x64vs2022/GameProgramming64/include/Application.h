#pragma once

class Application
{
public:

	Application(void (*start)()=nullptr, void (*update)()=nullptr);

	int main();

	static bool game2d;
	static bool fullScreen;

private:

	int fps;
	int width;
	int height;

	void (*pStart)();
	void (*pUpdate)();

	void update();
	void idle();
};

