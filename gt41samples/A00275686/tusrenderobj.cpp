#include <GL/glew.h>
#include "tusrenderobj.h"

void tusRenderObj::createBuffer(vec3 verts[], GLuint nv)
{
    numVerts = nv;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * nv, verts, GL_STATIC_DRAW);
}

void tusRenderObj::render()
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, numVerts);
    glDisableVertexAttribArray(0);
}