#include <stdio.h>
#include <stdlib.h>

#include "glew.h"
#include "CShader.h"

CShader::CShader()
	: mProgram(0)
	, compiled(0)
	, linked(0)
{
}
CShader::CShader(const char* vertexPath, const char* pixelPath){
	Load(vertexPath, pixelPath);
}
bool CShader::readFile(GLuint program, GLuint shader, const char *file) {
	FILE *fp;
	if (!(fp = fopen(file, "rb"))) {
		printf("ファイルが開けません[%s]\n", file);
		return false;
	}
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	GLchar *code = new char[size];
	fread(code, size, 1, fp);
	fclose(fp);

	glShaderSource(shader, 1, (const GLchar **)&code, &size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (compiled == GL_FALSE) {
		GLint length;
		GLchar *log;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		log = (GLchar*)malloc(length);
		glGetShaderInfoLog(shader, length, &length, log);
		fprintf(stderr, "compile log='%s'\n", log);
		free(log);
	}
	delete[] code;

	glAttachShader(program, shader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if (linked == GL_TRUE) {
		//glUseProgram(program);
	}
	else {
		GLint length;
		GLchar *log;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		log = (GLchar*)malloc(length);
		glGetProgramInfoLog(program, length, &length, log);
		fprintf(stderr, "link log='%s'\n", log);
		free(log);
	}


	glDeleteShader(shader);
	//glDeleteShader(flagShader);

	return true;

}
bool CShader::Load(const char* vertexPath, const char* flagPath){
	mProgram = glCreateProgram();
	if (vertexPath) {

		bool ret = readFile(mProgram, glCreateShader(GL_VERTEX_SHADER), vertexPath);
		if (!ret) return false;
	}
	if (flagPath) {

		bool ret = readFile(mProgram, glCreateShader(GL_FRAGMENT_SHADER), flagPath);
		if (!ret) return false;
	}


	return true;

}
CShader::~CShader(){
	glDeleteProgram(mProgram);

}
void CShader::Enable(){
	glUseProgram(mProgram);
}
void CShader::Disable(){
	glUseProgram(0);
}