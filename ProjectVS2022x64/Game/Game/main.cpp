#include <Windows.h>
#include <stdio.h>
#include "gl/glew.h"
#include "gl/freeglut.h"
#include "glfw/glfw3.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Hello World"
//#define FULL_SCREEN
//#define THREED


class GL;
class Application;

class A;
class B;

class A
{
public:
	A();
	void render();
	void renderB();
};

class B
{
public:
	B();
	void render();
	void renderA();
};

A::A()
{
}

void A::render()
{
	printf("A::render()\n");
}

void A::renderB()
{
	B b;
	b.render();
}

B::B()
{
}

void B::render()
{
	printf("B::render()\n");
}

void B::renderA()
{
	A a;
	a.render();
}

class Application
{
	A a;
	B b;
public:
	void start()
	{
		a.renderB();
		b.renderA();
	}

	void update()
	{
	}
};


class GL
{
public:
	GL()
		: pWindow(nullptr)
		, fpsCounter(0.0)
	{

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

		// �E�B���h�E�̃T�C�Y�ύX���ɌĂяo�������̓o�^
		glfwSetWindowSizeCallback(pWindow, reshape);
		reshape(pWindow, WINDOW_WIDTH, WINDOW_HEIGHT);

#ifdef THREED
		//3D�K�v 2D�s�v
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		//���C�g�̐ݒ�i3D�K�v 2D�s�v�j
		//�Œ�V�F�[�_�[�p
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		float lightPosition[] = { 0.0f, 100.0f, 100.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

		glEnable(GL_NORMALIZE);
#endif
	}

	void update()
	{
		application.start();
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

		application.update();
	}

	static void reshape(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);	//��ʂ̕`��G���A�̎w��
		glMatrixMode(GL_PROJECTION);	//�s����v���W�F�N�V�������[�h�֕ύX
		glLoadIdentity();				//�s���������
#ifdef THREED
		gluPerspective(75.0, (double)width / (double)height, 1.0, 10000.0);	//3D�̉�ʂ�ݒ�
#else
		gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);	//2D�̉�ʂ�ݒ�
#endif
	}

};

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	GL gl;

	gl.update();

	return 0;
}

