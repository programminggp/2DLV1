#pragma once

class Application
{
public:

	Application (
		void (*start)()=nullptr,  //��������
		void (*update)()=nullptr  //�X�V����
	);

	Application	(
		const char* title,
		int width,
		int height,
		int fps,
		void (*start)() = nullptr,  //��������
		void (*update)() = nullptr,  //�X�V����
		bool game2d = true,
		bool fullscreen = false
	);

	int main();
};

