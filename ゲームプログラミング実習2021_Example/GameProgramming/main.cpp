#include <Windows.h>
#include "glew.h"
#include "GLFW/glfw3.h"
#include "main.h"
#include "CSceneManager.h"
#include "glut.h"
bool InitFlg = true;

//�V�[���}�l�[�W���̃C���X�^���X
CSceneManager SceneManager;

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
		SceneManager.Init();
		InitFlg = false;
	}
	else {
		SceneManager.Update();
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

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
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

		idle();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
