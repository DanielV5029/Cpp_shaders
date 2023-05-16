#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <Windows.h>
#include "tusrenderobj.h"
#include "aiterror.h"
#include "camera.h"
#include <vector>

using namespace std;
using namespace glm;

tusRenderObj obja;
rShader stA;
cameraObj cam;
mat4 worldToViewTransform;

static void renderSceneCallBack()
{
    // Clear the back buffer and the z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Update worldToViewTransform
    worldToViewTransform = cam.getWorldToViewMatrix();

    obja.setScale(vec3(0.5f, 0.5f, 0.5f));
    obja.setRot(0.0f, vec3(0.0f, 1.0f, 0.0f));
    obja.setTrans(vec3(0.0f, 0.0f, 0.0f));
    obja.render(worldToViewTransform);

    glutSwapBuffers();
}

static void KeyboardCB(unsigned char key, int mouse_x, int mouse_y)
{
    cam.OnKeyboard(key);
}

static void SpecialKeyboardCB(int key, int mouse_x, int mouse_y)
{
    cam.OnKeyboard(key);
}

static void initializeGlutCallbacks()
{
    glutDisplayFunc(renderSceneCallBack);
    glutIdleFunc(renderSceneCallBack);

}

struct Vertex
{
    float x, y, z;
};

struct Normal
{
    float x, y, z;
};

struct Face
{
    int v1, v2, v3;
    int n1, n2, n3;
};

vector<Vertex> vertices;
vector<Normal> normals;
vector<Face> faces;

void loadObjaFile(string filename)
{
    ifstream file(filename.c_str());
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string type;
        ss >> type;

        if (type == "v")
        {
            Vertex v;
            ss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        }
        else if (type == "vn")
        {
            Normal n;
            ss >> n.x >> n.y >> n.z;
            normals.push_back(n);
        }
        else if (type == "f")
        {
            Face f;
            char slash;
            ss >> f.v1 >> slash >> f.n1 >> f.v2 >> slash >> f.n2 >> f.v3 >> slash >> f.n3;
            faces.push_back(f);
        }
    }
}

static void createBuffer()
{
    // Create some vertices to put in our VBO.
    const int nv1 = 24;
    tusRenderObj::SimpleVertex vertices[] =
    {
        // Side 1 Front
        {vec3(-1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(1.0f,-1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(-1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(1.0f,-1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(-1.0f,-1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},

        // Side 2 Right Side
        {vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(1.0f, 1.0f,-1.0f), vec3(1.0f, 0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(1.0f,-1.0f,-1.0f), vec3(1.0f, 0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(1.0f,-1.0f,-1.0f), vec3(1.0f, 0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(1.0f,-1.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},

        // Side 3 Back
        {vec3(1.0f, 1.0f,-1.0f), vec3(0.0f, 0.0f,-1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(-1.0f, 1.0f,-1.0f), vec3(0.0f, 0.0f,-1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(-1.0f,-1.0f,-1.0f), vec3(0.0f, 0.0f,-1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(1.0f, 1.0f,-1.0f), vec3(0.0f, 0.0f,-1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(-1.0f,-1.0f,-1.0f), vec3(0.0f, 0.0f,-1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(1.0f,-1.0f,-1.0f), vec3(0.0f, 0.0f,-1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},

        // Side 4 Left Side
        {vec3(-1.0f, 1.0f,-1.0f), vec3(-1.0f, 0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(-1.0f, 1.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(-1.0f,-1.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(-1.0f, 1.0f,-1.0f), vec3(-1.0f, 0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(-1.0f,-1.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {vec3(-1.0f,-1.0f,-1.0f), vec3(-1.0f, 0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)}

    };
    obja.createBuffer(vertices, nv1);
    obja.setShade(&stA);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("First Shaders");

    initializeGlutCallbacks();

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) 
    {
		cerr<<"Error: "<<glewGetErrorString(res)<<"\n";
		return 1;
    }


    //Create shaders
    stA.buildShaders("vertexShader.glsl", "fragmentShader.glsl");
    //stB.buildShaders("vertexShader2.glsl", "fragmentShader2.glsl");
    

    // Enable the z-buffer
    glEnable(GL_DEPTH_TEST);
    // GL_LESS - Passes if the incoming depth value is less than the stored depth value
    glDepthFunc(GL_LESS);

    //Enable backface culling
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Create a vertex buffer
    createBuffer();

    glutKeyboardFunc(KeyboardCB);
    glutSpecialFunc(SpecialKeyboardCB);

    glutMainLoop();
    
    return 0;
}