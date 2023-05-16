#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <Windows.h>
#include <string>
#include <glm/gtc/matrix_transform.hpp>


using namespace std;
using namespace glm;

class cameraObj
{
private:
	vec3 pos;
	vec3 lookTo;
	vec3 upVec;
public:
	mat4 worldToViewTransform;
	mat4 getWorldToViewMatrix();

	//void setPos(vec3 v);
	//void setlookTo(vec3 v);
	//void setupVec(vec3 v);
	cameraObj();
	vec3 getPos();
	vec3 getlookTo();
	vec3 getupVec();
	void OnKeyboard(unsigned char key);

};
