#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &normals[0]);

    for (int i = 0; i < faces.size(); i++)
    {
        glBegin(GL_TRIANGLES);
        glArrayElement(faces[i].v1 - 1);
        glArrayElement(faces[i].v2 - 1);
        glArrayElement(faces[i].v3 - 1);
        glEnd();
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Obja Viewer");

    loadObjaFile("triangle.obja.txt");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}