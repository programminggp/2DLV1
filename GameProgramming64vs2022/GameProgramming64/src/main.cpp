#include <Windows.h>
#include <stdio.h>
#include "gl/glew.h"
#include "gl/freeglut.h"
#include "GLFW/glfw3.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Hello World"
//#define FULL_SCREEN

class GL;
class Application;


#include "CSceneManager.h"

//�V�[���}�l�[�W���̃C���X�^���X
CSceneManager SceneManager;

//Init�֐�
//�ŏ��Ɉ�x�����Ă΂��֐�
void Init() {
	//�V�[���}�l�[�W���̏�����
	SceneManager.Init();
}
//Update�֐�
//�v���O�����̎��s���A�J��Ԃ��Ă΂��֐�
void Update() {
	//�V�[���}�l�[�W���̍X�V
	SceneManager.Update();
}

class Application
{
	//�V�[���}�l�[�W���̃C���X�^���X
	CSceneManager SceneManager;
public:
	void Start()
	{
		SceneManager.Init();
	}

	void Update()
	{
		SceneManager.Update();
	}
};



class GL
{
public:
	GL()
		: pWindow(nullptr)
		, fpsCounter(0.0)
	{
		//glutInit(&argc, argv);

		/* Initialize the library */
		if (!glfwInit())
			return;

		/* Create a windowed mode window and its OpenGL context */
#ifndef FULL_SCREEN
		pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
#else
	//Full Screen
		pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, glfwGetPrimaryMonitor(), NULL);
#endif
		if (!pWindow)
		{
			glfwTerminate();
			return;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(pWindow);


		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

		// GLEW ������������
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			// GLEW �̏������Ɏ��s����
			printf("Can't initialize GLEW\n");
	//		std::cerr << "Can't initialize GLEW" << std::endl;
			return;
		}
		// ���������̃^�C�~���O��҂�  
		//glfwSwapInterval(1); 


		glEnable(GL_DEPTH_TEST);	//3D�K�v 2D�s�v
		glEnable(GL_CULL_FACE);

		// �E�B���h�E�̃T�C�Y�ύX���ɌĂяo�������̓o�^
		glfwSetWindowSizeCallback(pWindow, reshape);
		reshape(pWindow, WINDOW_WIDTH, WINDOW_HEIGHT);

		//���C�g�̐ݒ�i3D�K�v 2D�s�v�j
		//�Œ�V�F�[�_�[�p
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		float lightPosition[] = { 0.0f, 100.0f, 100.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

		glEnable(GL_NORMALIZE);

		//���b�V���V�F�[�_�[�p
	//	CLight::getLight(0)->setDir(CVector3(0, -1, 1).GetNormalize());
	//	CLight::getLight(0)->setColor(CVector3(0.9f, 0.9f, 0.9f), CVector3(1.0f, 1.0f, 1.0f));

	}

	void Update()
	{
		application.Start();
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(pWindow))
		{

			idle();

			/* Swap front and back buffers */
			glfwSwapBuffers(pWindow);

			/* Poll for and process events */
			glfwPollEvents();

			int state = glfwGetKey(pWindow, GLFW_KEY_ESCAPE);
			if (state == GLFW_PRESS) {
				//ESC�L�[�Ń��[�v�I��
				break;
			}
		}

		glfwTerminate();
	}

private:
	GLFWwindow* pWindow;
	double fpsCounter;
	Application application;

	void idle()
	{
		double time;
		do
		{
			time = glfwGetTime();
		} while (fpsCounter > time);
		fpsCounter = time + 1.0 / 60.0;
		display();
	}

	void display()
	{
		//�e�o�b�t�@�[���N���A
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		//�s��̃��[�h�����f���r���[�ɂ���
		glMatrixMode(GL_MODELVIEW);
		//���f���r���[�̍s���P�ʍs��ɂ���
		glLoadIdentity();

		application.Update();
	}

	static void reshape(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);	//��ʂ̕`��G���A�̎w��
		glMatrixMode(GL_PROJECTION);	//�s����v���W�F�N�V�������[�h�֕ύX
		glLoadIdentity();				//�s���������
		//	gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);	//2D�̉�ʂ�ݒ�
		gluPerspective(75.0, (double)width / (double)height, 1.0, 10000.0);	//3D�̉�ʂ�ݒ�

		//glMatrixMode(GL_MODELVIEW);		//�s������f���r���[���[�h�֕ύX
		//glLoadIdentity();				//�s���������
	}

};


bool InitFlg = true;

/* display�֐�
1�b�Ԃ�60����s�����
*/
void display() {
	//�e�o�b�t�@�[���N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//�s��̃��[�h�����f���r���[�ɂ���
	glMatrixMode(GL_MODELVIEW);
	//���f���r���[�̍s���P�ʍs��ɂ���
	glLoadIdentity();

	if (InitFlg) {
		Init();
		InitFlg = false;
	}
	else {
		Update();
	}

}


/*�E�B���h�E�T�C�Y�ύX���̏���
void reshape(int width, int height)
width:��ʕ�
height:��ʍ���
*/
void reshape(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);	//��ʂ̕`��G���A�̎w��
	glMatrixMode(GL_PROJECTION);	//�s����v���W�F�N�V�������[�h�֕ύX
	glLoadIdentity();				//�s���������
//	gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);	//2D�̉�ʂ�ݒ�
	gluPerspective(75.0, (double)width / (double)height, 1.0, 10000.0);	//3D�̉�ʂ�ݒ�

	glMatrixMode(GL_MODELVIEW);		//�s������f���r���[���[�h�֕ύX
	glLoadIdentity();				//�s���������
}
//
LARGE_INTEGER last_time;	//�O��̃J�E���^�l
//�P�b�ԂɂU�O��`�悷��悤�ɒ��߂���
void idle() {
	LARGE_INTEGER freq;		//��b������̃J�E���^��
	LARGE_INTEGER time;		//����̃J�E���^�l

	//��b�Ԃ̃J�E���^�����擾
	QueryPerformanceFrequency(&freq);

	if (last_time.QuadPart == 0) {
		QueryPerformanceCounter(&last_time);
	}
	do{
		//���݂̃V�X�e���̃J�E���g�����擾
		QueryPerformanceCounter(&time);

		//���̃J�E���g-�O��̃J�E���g < 1�b������̃J�E���g����60�Ŋ���(1/60�b������̃J�E���g��)
	} while (time.QuadPart - last_time.QuadPart < freq.QuadPart / 60);
	last_time = time;

	//�`�悷��֐����Ă�
	display();
}

double sNextTime = 1.0/60.0;
void Idle()
{
	double time;
	do
	{
		time = glfwGetTime();
	} while (sNextTime > time);
	sNextTime = time + 1.0 / 60.0;
	display();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	GL gl;

	gl.Update();


	return 0;



	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
#ifndef FULL_SCREEN
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
#else
	//Full Screen
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", glfwGetPrimaryMonitor(), NULL);
#endif
	if (!window)
	{
		glfwTerminate();
		return -1;
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
		return 1;
	}
	// ���������̃^�C�~���O��҂�  
	//glfwSwapInterval(1); 


	glEnable(GL_DEPTH_TEST);	//3D�K�v 2D�s�v
	glEnable(GL_CULL_FACE);

	// �E�B���h�E�̃T�C�Y�ύX���ɌĂяo�������̓o�^
	glfwSetWindowSizeCallback(window, reshape);
	reshape(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	//���C�g�̐ݒ�i3D�K�v 2D�s�v�j
	//�Œ�V�F�[�_�[�p
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float lightPosition[] = {0.0f, 100.0f, 100.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glEnable(GL_NORMALIZE);

	//���b�V���V�F�[�_�[�p
//	CLight::getLight(0)->setDir(CVector3(0, -1, 1).GetNormalize());
//	CLight::getLight(0)->setColor(CVector3(0.9f, 0.9f, 0.9f), CVector3(1.0f, 1.0f, 1.0f));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		Idle();

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
