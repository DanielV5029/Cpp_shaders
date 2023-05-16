#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <Windows.h>
#include <string>

using namespace std;
using namespace glm;

class rShader
{
private:
	GLuint shaderObj;
public:
	void buildShaders(char* filename, char* filename2);
	const string readFileToString(char* filename);
	void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);
	void use();
	GLuint shaderProgram;

};
