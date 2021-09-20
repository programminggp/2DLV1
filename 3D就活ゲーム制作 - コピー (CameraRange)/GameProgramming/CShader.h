#ifndef SHADER_HPP
#define SHADER_HPP

#include "glew.h"
//#include "glut.h"

class CShader {
private:
//	GLuint vertexShader;
//	GLuint flagShader;
	GLuint mProgram;
	GLint compiled;
	GLint linked;
	
	bool readFile(GLuint program,GLuint shader, const char *file);
public:
	CShader();
	CShader(const char* vertexPath,const char*  flagPath);
	~CShader();
	bool load(const char* vertexPath,const char*  flagPath);
	void enable();
	void disable();
	GLuint getProgram() {
		return mProgram;
	}


};
#endif