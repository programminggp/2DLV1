#pragma once

class Application
{
public:

	Application (
		void (*start)()=nullptr,  //初期処理
		void (*update)()=nullptr  //更新処理
	);

	Application	(
		const char* title,
		int width,
		int height,
		int fps,
		void (*start)() = nullptr,  //初期処理
		void (*update)() = nullptr,  //更新処理
		bool game2d = true,
		bool fullscreen = false
	);

	int main();
};

