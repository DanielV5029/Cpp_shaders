#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <Windows.h>
#include "aiterror.h"
#include "shaderTech.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
using namespace glm;



void rShader::buildShaders(char* filename, char* filename2)
{
    shaderProgram = glCreateProgram();

    if (shaderProgram == 0)
    {
        cerr << "Error creating shader program\n";
        exit(1);
    }

    string VS = readFileToString(filename);
    string FS = readFileToString(filename2);

    addShader(shaderProgram, VS.c_str(), GL_VERTEX_SHADER);
    addShader(shaderProgram, FS.c_str(), GL_FRAGMENT_SHADER);

    GLint success = 0;
    GLchar errorLog[1024] = { 0 };

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (success == 0)
    {
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        std::stringstream ss;
        ss << "Error linking shader program: " << errorLog << endl;
        AIT_ASSERT(0, ss.str());
    }

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        cerr << "Error linking shader program: " << errorLog << endl;
        std::stringstream ss;
        ss << "Error linking shader program: " << errorLog << endl;
        AIT_ASSERT(0, ss.str());
    }

}


const string rShader::readFileToString(char* filename)
{
    ifstream file(filename, ios::in);
    if (file.is_open())
    {
        stringstream continut;
        continut << file.rdbuf();
        continut << '\0';
        return continut.str();
    }
    return "";
}

void rShader::addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType)
{
    shaderObj = glCreateShader(shaderType);

    if (shaderObj == 0)
    {
        cerr << "Error creating shader type " << shaderType << endl;
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0] = strlen(pShaderText);
    glShaderSource(shaderObj, 1, p, Lengths);
    glCompileShader(shaderObj);
    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);
        cerr << "Error compiling shader type " << shaderType << ": " << InfoLog << endl;
        exit(1);
    }

    glAttachShader(shaderProgram, shaderObj);
}

void rShader::use()
{
    glUseProgram(shaderProgram);
}
