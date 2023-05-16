/*
// Create a new model to world transform
	trans = mat4(1.0f);
	trans = translate(trans, vec3(-3.0f, y, 0.0f));

	rot = mat4(1.0f);
	rot = rotate(rot, angle, vec3(0.0f, 1.0f, 0.0f));

	modelToWorldTransform = trans * rot;

	glUniformMatrix4fv(gModelToWorldTransformLocation, 1, GL_FALSE, &modelToWorldTransform[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, NUMVERTS);

	// Create a new model to world transform
	trans = mat4(1.0f);
	trans = translate(trans, vec3(3.0f, y, 0.0f));

	rot = mat4(1.0f);
	rot = rotate(rot, angle, vec3(0.0f, 1.0f, 0.0f));

	modelToWorldTransform = trans * rot;

	glUniformMatrix4fv(gModelToWorldTransformLocation, 1, GL_FALSE, &modelToWorldTransform[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, NUMVERTS);*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Windows.h>
#include "aiterror.h"

using namespace std;
using namespace glm;

const int windowWidth = 1024; 
const int windowHeight = 768;

GLuint VBO;
GLuint VBO2;
GLuint VBO3;
const int NUMVERTS = 3;
GLuint gModelToWorldTransformLocation;
GLuint gWorldToViewTransformLocation;
GLuint gProjectionTransformLocation;

// Our simple vertex container
struct SimpleVertex
{
    vec3		pos;	// Position
	vec4		colour;	// Colour
};


static void renderSceneCallBack()
{

	glClear(GL_COLOR_BUFFER_BIT);


	// Create our world space to view space transformation matrix
	mat4 worldToViewTransform = lookAt(
		vec3(0.0f,0.0f,10.0f), // The position of your camera, in world space
		vec3(0.0f,0.0f,0.0f), // where you want to look at, in world space
		vec3(0.0f,1.0f,0.0f)  // Camera up direction (set to 0,-1,0 to look upside-down)
		); 

    // Create out projection transform
    mat4 projectionTransform = perspective(45.0f, (float)windowWidth / (float)windowHeight, 1.0f, 100.0f);

    // Update the transforms in the shader program on the GPU
    glUniformMatrix4fv(gWorldToViewTransformLocation, 1, GL_FALSE, &worldToViewTransform[0][0]);
    glUniformMatrix4fv(gProjectionTransformLocation, 1, GL_FALSE, &projectionTransform[0][0]);

    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (const GLvoid*)12);


	// **********************************************************
	mat4 scalem = mat4(1.0f);
	scalem = scale(scalem, vec3(0.5f, 0.5f, 0.5f));

	static float angle = 0.0f;
	angle+=1.0f;
	mat4 rot = mat4(1.0f);
	rot = rotate(rot, angle, vec3(0.0f, 1.0f, 0.0f));

	static float y = -2.0f;
	y+=0.01f;
	mat4 trans = mat4(1.0f);
	trans = translate(trans, vec3(0.0f, y, 0.0f));  

	mat4 modelToWorldTransform = trans * rot * scalem;

	glUniformMatrix4fv(gModelToWorldTransformLocation, 1, GL_FALSE, &modelToWorldTransform[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, NUMVERTS);

	// **********************************************************
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	
	mat4 scalem2 = mat4(1.0f);
	scalem2 = scale(scalem2, vec3(0.5f, 0.5f, 0.5f));

	static float angle2 = 0.0f;
	angle2 += 1.0f;
	mat4 rot2 = mat4(1.0f);
	rot2 = rotate(rot2, angle2, vec3(0.0f, 1.0f, 0.0f));

	static float y2 = -2.0f;
	y2 += 0.01f;
	mat4 trans2 = mat4(1.0f);
	trans2 = translate(trans2, vec3(3.0f, y2, 0.0f));

	mat4 modelToWorldTransform2 = trans2 * rot2 * scalem2;

	glUniformMatrix4fv(gModelToWorldTransformLocation, 1, GL_FALSE, &modelToWorldTransform2[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, NUMVERTS);

	// **********************************************************
	glBindBuffer(GL_ARRAY_BUFFER, VBO3);

	mat4 scalem3 = mat4(1.0f);
	scalem3 = scale(scalem3, vec3(0.5f, 0.5f, 0.5f));

	static float angle3 = 0.0f;
	angle3 += 1.0f;
	mat4 rot3 = mat4(1.0f);
	rot3 = rotate(rot3, angle3, vec3(0.0f, 1.0f, 0.0f));

	static float y3 = -2.0f;
	y3 += 0.01f;
	mat4 trans3 = mat4(1.0f);
	trans3 = translate(trans3, vec3(-3.0f, y3, 0.0f));

	mat4 modelToWorldTransform3 = trans3 * rot3 * scalem3;

	glUniformMatrix4fv(gModelToWorldTransformLocation, 1, GL_FALSE, &modelToWorldTransform3[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, NUMVERTS);
	// **********************************************************

    glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

    glutSwapBuffers();
}

static void initializeGlutCallbacks()
{
    glutDisplayFunc(renderSceneCallBack);
    glutIdleFunc(renderSceneCallBack);
}

static void createVertexBuffer()
{
	// Create some vertices to put in our VBO.
	// Create vertex buffer
	SimpleVertex vertices[] =
	{
		{vec3(0.0f, 1.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f)},
		{vec3(-1.0f, 0.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f)},
		{vec3( 1.0f,0.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f)},

	};
    
 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SimpleVertex) * NUMVERTS, vertices, GL_STATIC_DRAW);

	SimpleVertex vertices2[] =
	{
		{vec3(0.0f, 1.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f)},
		{vec3(-1.0f, 0.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f)},
		{vec3(1.0f,0.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f)},
	};

	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SimpleVertex) * NUMVERTS, vertices2, GL_STATIC_DRAW);

	SimpleVertex vertices3[] =
	{
		{vec3(0.0f, 1.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f)},
		{vec3(-1.0f, 0.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f)},
		{vec3(1.0f,0.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f)}
	};

	glGenBuffers(1, &VBO3);
	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SimpleVertex) * NUMVERTS, vertices3, GL_STATIC_DRAW);
}

static void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType)
{
    GLuint shaderObj = glCreateShader(shaderType);

	if (shaderObj == 0) 
	{
		std::stringstream ss;
		ss<<"Error creating shader type "<<shaderType<<endl;
		AIT_ASSERT(0, ss.str());
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(shaderObj, 1, p, Lengths);
    glCompileShader(shaderObj);
    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
    if (!success) 
	{
        GLchar InfoLog[1024];
        glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);
		std::stringstream ss;
		ss <<"Error compiling shader type "<<shaderType<<": "<<InfoLog<<endl;
		AIT_ASSERT(0, ss.str());
    }

    glAttachShader(shaderProgram, shaderObj);
}

const string readFileToString(char* filename)
{
	ifstream file (filename, ios::in);
	if (file.is_open())
	{
        stringstream continut;
        continut << file.rdbuf();
        continut << '\0';
		return continut.str();
	}
    return "";
}

static void buildShaders()
{
    GLuint shaderProgram = glCreateProgram();

    if (shaderProgram == 0) 
	{
		AIT_ASSERT(0, "Error creating shader program\n");
    }

	string VS = readFileToString("vertexShader.glsl");
	string FS = readFileToString("fragmentShader.glsl");

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
		ss<<"Error linking shader program: "<<errorLog<<endl;
		AIT_ASSERT(0, ss.str());
	}

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success) 
	{
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        cerr<<"Error linking shader program: "<<errorLog<<endl;
        std::stringstream ss;
		ss<<"Error linking shader program: "<<errorLog<<endl;
		AIT_ASSERT(0, ss.str());
    }

    glUseProgram(shaderProgram);

    gModelToWorldTransformLocation = glGetUniformLocation(shaderProgram, "gModelToWorldTransform");
    assert(gModelToWorldTransformLocation != 0xFFFFFFFF);
    gWorldToViewTransformLocation = glGetUniformLocation(shaderProgram, "gWorldToViewTransform");
    assert(gWorldToViewTransformLocation != 0xFFFFFFFF);
    gProjectionTransformLocation = glGetUniformLocation(shaderProgram, "gProjectionTransform"); 
    assert(gProjectionTransformLocation != 0xFFFFFFFF);
    
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformations");

    initializeGlutCallbacks();

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) 
    {
		cerr<<"Error: "<<glewGetErrorString(res)<<"\n";
		return 1;
    }

	buildShaders();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 

	// Create a vertex buffer
	createVertexBuffer();

    glutMainLoop();
    
    return 0;
}