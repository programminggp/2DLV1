#include "pch.h"
#include "glew.h"
#include "glut.h"
#include "GLFW/glfw3.h"
#include "Application.h"

#define FPS 60
#define WIDTH 800
#define HEIGHT 600

//bool Application::game2d = true;
//bool Application::fullScreen = false;

GLFWwindow* window = nullptr;


char* Title = nullptr;
int Width;
int Height;
int Fps;

void (*pStart)() = nullptr;
void (*pUpdate)() = nullptr;
bool Game2d = true;
bool FullScreen = false;

void reshape(GLFWwindow* window, int width, int height);
void update();
void idle();


void reshape(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);	//��ʂ̕`��G���A�̎w��
	glMatrixMode(GL_PROJECTION);	//�s����v���W�F�N�V�������[�h�֕ύX
	glLoadIdentity();				//�s���������
	if (Game2d)
		gluOrtho2D(0, width, 0, height);	//2D�̉�ʂ�ݒ�
	else
		gluPerspective(75.0, (double)width / (double)height, 1.0, 10000.0);	//3D�̉�ʂ�ݒ�

	glMatrixMode(GL_MODELVIEW);		//�s������f���r���[���[�h�֕ύX
	glLoadIdentity();				//�s���������
}

void update()
{
	//�e�o�b�t�@�[���N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//�s��̃��[�h�����f���r���[�ɂ���
	glMatrixMode(GL_MODELVIEW);
	//���f���r���[�̍s���P�ʍs��ɂ���
	glLoadIdentity();

	pUpdate();
}

LARGE_INTEGER last_time;	//�O��̃J�E���^�l
void idle()
{
	LARGE_INTEGER freq;		//��b������̃J�E���^��
	LARGE_INTEGER time;		//����̃J�E���^�l

	//��b�Ԃ̃J�E���^�����擾
	QueryPerformanceFrequency(&freq);

	if (last_time.QuadPart == 0) {
		QueryPerformanceCounter(&last_time);
	}
	do {
		//���݂̃V�X�e���̃J�E���g�����擾
		QueryPerformanceCounter(&time);

		//���̃J�E���g-�O��̃J�E���g < 1�b������̃J�E���g����60�Ŋ���(1/60�b������̃J�E���g��)
	} while (time.QuadPart - last_time.QuadPart < freq.QuadPart / 60);
	last_time = time;

	//�`�悷��֐����Ă�
	update();
}

Application::Application
(
	const char* title,
	int width,
	int height,
	int fps,
	void (*start)(),  //��������
	void (*update)(),  //�X�V����
	bool game2d,
	bool fullscreen
	)
{
	Title = new char[strlen(title) + 1];
	strcpy(Title, title);

	Width = width;
	Height = height;
	Fps = Fps;;

	pStart = start;
	pUpdate = update;
	Game2d = game2d;
	FullScreen = fullscreen;

	//	GLFWwindow* window;

/* Initialize the library */
	if (!glfwInit())
		exit(EXIT_FAILURE);
	//return;

/* Create a windowed mode window and its OpenGL context */
	if (FullScreen)
		//Full Screen
		window = glfwCreateWindow(Width, Height, Title, glfwGetPrimaryMonitor(), NULL);
	else
		window = glfwCreateWindow(Width, Height, Title, NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
		//return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	// GLEW ������������
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		// GLEW �̏������Ɏ��s����
//		std::cerr << "Can't initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
		//return;
	}
	// ���������̃^�C�~���O��҂�  
	//glfwSwapInterval(1); 

	// �E�B���h�E�̃T�C�Y�ύX���ɌĂяo�������̓o�^
	glfwSetWindowSizeCallback(window, reshape);
	reshape(window, width, height);

	if (!Game2d) {
		glEnable(GL_DEPTH_TEST);	//3D�K�v 2D�s�v
		glEnable(GL_CULL_FACE);

		//���C�g�̐ݒ�i3D�K�v 2D�s�v�j
		//�Œ�V�F�[�_�[�p
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		float lightPosition[] = { 0.0f, 100.0f, 100.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glEnable(GL_NORMALIZE);
	}
}

Application::Application(void (*start)(), void (*update)())
{
	Application::Application("Hello", WIDTH, HEIGHT, FPS, start, update, true, false);
}

int Application::main()
{
	//��������
	pStart();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		idle();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		int state = glfwGetKey(window, GLFW_KEY_ESCAPE);
		if (state == GLFW_PRESS) {
			//ESC�L�[�Ń��[�v�I��
			break;
		}
	}

	glfwTerminate();
	return 0;
}

