#ifndef SHADER_HPP
#define SHADER_HPP

#include "glut.h"

class CShader {
private:
	GLuint mProgram;
	GLint compiled;
	GLint linked;
	bool readFile(GLuint program, GLuint shader, const char *file);
public:
	CShader();
	CShader(const char* vertexPath, const char*  fragPath);
	~CShader();
	bool Load(const char* vertexPath, const char*  fragPath);
	void Enable();
	void Disable();
	GLuint GetProgram() {
		return mProgram;
	}
};
#endif