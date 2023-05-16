#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <Windows.h>
#include <string>
#include "shaderTech.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
using namespace glm;

class tusRenderObj
{
	
private:
	
	GLuint numVerts;
	GLuint vbo;
	mat4 scalem2;
	mat4 rot2;
	mat4 trans2;
	const int windowWidth = 1024;
	const int windowHeight = 768;
	// Transform uniforms location
	GLuint gModelToWorldTransformLocation;
	GLuint gWorldToViewTransformLocation;
	GLuint gProjectionTransformLocation;
	mat4 modelToWorldTransform2;
public:
	rShader* shader;

	struct SimpleVertex
	{
		vec3		pos;	// Position
		vec3		normal; // Vertex Normal
		vec4		colour;	// Colour
	};
	void createBuffer(SimpleVertex verts[], GLuint nv);
	void render(mat4 modelToView);
	void setShade(rShader* st);
	void setScale(vec3 v);
	void setRot(float move,vec3 v);
	void setTrans(vec3 v);
	mat4 getScale();
	mat4 getRot();
	mat4 getTrans();
};
