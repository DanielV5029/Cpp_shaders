#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "tusrenderobj.h"

using namespace std;
using namespace glm;

tusRenderObj obja;
tusRenderObj objb;

static void renderSceneCallBack()
{
    glClear(GL_COLOR_BUFFER_BIT);
    obja.render();
    objb.render();
    glutSwapBuffers();
}

static void initializeGlutCallbacks()
{
    glutDisplayFunc(renderSceneCallBack);
}

static void createTusRenderObjs()
{
    // Create some vertices to put in our VBO.
    const int nv1 = 2;
    vec3 vertices[nv1];
    vertices[0] = vec3(-0.5f, -0.5f, 0.0f);
    vertices[1] = vec3(-0.5f, 0.5f, 0.0f);
    obja.createBuffer(vertices, nv1);

    const int nv2 = 2;
    vec3 vertices2[nv2];
    vertices2[0] = vec3(0.5f, -0.5f, 0.0f);
    vertices2[1] = vec3(0.5f, 0.5f, 0.0f);
    objb.createBuffer(vertices2, nv2);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Basic Application");

    initializeGlutCallbacks();

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) 
    {
		cerr<<"Error: "<<glewGetErrorString(res)<<"\n";
		return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 

	// Create a vertex buffer
	createTusRenderObjs();

    glutMainLoop();
    
    return 0;
}