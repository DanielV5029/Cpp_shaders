#include "tusrenderobj.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <Windows.h>
#include <string>
#include "aiterror.h"
#include "camera.h"
using namespace std;

cameraObj camera;


void tusRenderObj::createBuffer(SimpleVertex verts[], GLuint nv)
{
    numVerts = nv;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SimpleVertex) * nv, verts, GL_STATIC_DRAW);

}

void tusRenderObj::render(mat4 modelToView)
{
    shader->use();

    // Create out projection transform
    mat4 projectionTransform = perspective(45.0f, (float)windowWidth / (float)windowHeight, 1.0f, 100.0f);


    // Update the transforms in the shader program on the GPU
    glUniformMatrix4fv(gWorldToViewTransformLocation, 1, GL_FALSE, &modelToView[0][0]);
    glUniformMatrix4fv(gProjectionTransformLocation, 1, GL_FALSE, &projectionTransform[0][0]);



    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (const GLvoid*)12);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (const GLvoid*)24);

    //draw triangle
    //modelToWorldTransform2 = getTrans()*getRot()*getScale();
    modelToWorldTransform2 = getTrans() * getRot() * getScale();
	glUniformMatrix4fv(gModelToWorldTransformLocation, 1, GL_FALSE, &modelToWorldTransform2[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, numVerts);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);


    gModelToWorldTransformLocation = glGetUniformLocation(shader->shaderProgram, "gModelToWorldTransform");
    assert(gModelToWorldTransformLocation != 0xFFFFFFFF);

    gWorldToViewTransformLocation = glGetUniformLocation(shader->shaderProgram, "gWorldToViewTransform");
    assert(gWorldToViewTransformLocation != 0xFFFFFFFF);

    gProjectionTransformLocation = glGetUniformLocation(shader->shaderProgram, "gProjectionTransform");
    assert(gProjectionTransformLocation != 0xFFFFFFFF);
}

void tusRenderObj::setShade(rShader* st)
{
    shader = st;
}

void tusRenderObj::setScale(vec3 v)
{
    scalem2 = mat4(1.0f);
    scalem2 = scale(scalem2, v);
}

void tusRenderObj::setRot(float move, vec3 v)
{
    static float angle2 = 0.0f;
    angle2 += move;
    rot2 = mat4(1.0f);
    rot2 = rotate(rot2, angle2, v);
}

void tusRenderObj::setTrans(vec3 v)
{
    trans2 = mat4(1.0f);
    trans2 = translate(trans2, v);
}


mat4 tusRenderObj::getScale()
{
    return scalem2;
}

mat4 tusRenderObj::getRot()
{
    return rot2;
}

mat4 tusRenderObj::getTrans()
{
    return trans2;
}





