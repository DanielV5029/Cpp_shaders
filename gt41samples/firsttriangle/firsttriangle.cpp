#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;


GLuint VBO_Triangle;
const int NUMVERTS_T = 3;

GLuint VBO_Line;
const int NUMVERTS_Line = 2;

GLuint VBO_Line_Strip;
const int NUMVERTS_Line_S = 4;

GLuint VBO_T_Strip;
const int NUMVERTS_T_S = 6;


static void renderSceneCallBack()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //Draw VBO_T_Strip
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_T_Strip);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, NUMVERTS_T_S);
    glDisableVertexAttribArray(0);

    //Draw VBO_Triangle
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Triangle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, NUMVERTS_T);
    glDisableVertexAttribArray(0);

    //Draw VBO_Line
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Line);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_LINES, 0, NUMVERTS_Line);
    glDisableVertexAttribArray(0);

    //Draw VBO_Line_Strip
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Line_Strip);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_LINE_STRIP, 0, NUMVERTS_Line_S);
    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}

static void initializeGlutCallbacks()
{
    glutDisplayFunc(renderSceneCallBack);
}

static void createVertexBuffers()
{
	// Create some vertices to put in our VBO.
	vec3 vertices[NUMVERTS_T_S];
    vertices[0] = vec3(-0.5f, 0.5f, 0.0f);
    vertices[1] = vec3(-0.6f, 0.5f, 0.0f); 
    vertices[2] = vec3(-0.5f, 0.6f, 0.0f);
    vertices[3] = vec3(-0.5f, 0.5f, 0.0f);
    vertices[4] = vec3(-0.6f, 0.5f, 0.0f);
    vertices[5] = vec3(-0.6f, 0.5f, 0.0f);
    glGenBuffers(1, &VBO_T_Strip);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_T_Strip);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * NUMVERTS_T_S, vertices, GL_STATIC_DRAW);

    // Create some vertices to put in our VBO.
    vec3 vertices2[NUMVERTS_T];
    vertices2[0] = vec3(0.5f, 0.5f, 0.0f);
    vertices2[1] = vec3(0.6f, 0.5f, 0.0f);
    vertices2[2] = vec3(0.5f, 0.6f, 0.0f);
    glGenBuffers(1, &VBO_Triangle);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Triangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * NUMVERTS_T, vertices2, GL_STATIC_DRAW);

    // Create some vertices to put in our VBO.
    vec3 vertices3[NUMVERTS_Line];
    vertices3[0] = vec3(-0.1f, -0.5f, 0.0f);
    vertices3[1] = vec3(-0.1f, -0.6f, 0.0f);
    glGenBuffers(1, &VBO_Line);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Line);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * NUMVERTS_Line, vertices3, GL_STATIC_DRAW);

    // Create some vertices to put in our VBO.
    vec3 vertices4[NUMVERTS_Line_S];
    vertices4[0] = vec3(-0.5f, -0.5f, 0.0f);
    vertices4[1] = vec3(-0.5f, -0.6f, 0.0f);
    vertices4[2] = vec3(-0.6f, -0.6f, 0.0f);
    vertices4[3] = vec3(-0.6f, -0.7f, 0.0f);
    glGenBuffers(1, &VBO_Line_Strip);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Line_Strip);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * NUMVERTS_Line_S, vertices4, GL_STATIC_DRAW);
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
	createVertexBuffers();

    glutMainLoop();
    
    return 0;
}
