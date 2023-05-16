#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace glm;

class tusRenderObj
{
private: 
	GLuint numVerts;
	GLuint vbo;

public:
	void createBuffer(vec3 verts[], GLuint nv);
	void render();
};
