#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <Windows.h>
#include <string>
#include "camera.h"


mat4 cameraObj::getWorldToViewMatrix()
{


	worldToViewTransform = lookAt(getPos(), getlookTo(), getupVec());
	return worldToViewTransform;

}

cameraObj::cameraObj()
{
	pos = vec3(0.0f, 0.0f, 10.0f);
	lookTo = vec3(0.0f, 0.0f, 0.0f);
	upVec = vec3(0.0f, 1.0f, 0.0f);
}

vec3 cameraObj::getPos()
{
	return pos;
}


vec3 cameraObj::getlookTo()
{
	return lookTo;
}

vec3 cameraObj::getupVec()
{
	return upVec;
}


void cameraObj::OnKeyboard(unsigned char key)
{
    vec3 newLookTo;
    vec3 newUpVec;
    vec3 newRightVec;

    switch (key) {
    case 'w':
        pos.y += 1.0f;
        lookTo.y += 1.0f;
        cout << endl;
        break;
    case 's':
        pos.y -= 1.0f;
        lookTo.y -= 1.0f;
        cout << endl;
        break;
    case 'a':
        pos.x -= 1.0f;
        lookTo.x -= 1.0f;
        cout << endl;
        break;
    case 'd':
        pos.x += 1.0f;
        lookTo.x += 1.0f;
        cout << endl;
        break;
    case 'q':
        lookTo.x += 1.0f;
        break;
    case 'e':
        lookTo.x -= 1.0f;
        break;
    case 'z':
        pos.z -= 1.0f;
        break;
    case 'x':
        pos.z += 1.0f;
        break;
    }
}

