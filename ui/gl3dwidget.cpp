#include "gl3dwidget.h"
#include <iostream>
#include <fstream>
using namespace std;

GL3Dwidget::GL3Dwidget(QWidget *parent, string path):QOpenGLWidget(parent)
{
    ifstream in(path, ios::in);
    if(in)
    {
        string off_tag;
        in >> off_tag;
        int num_vertices, num_faces, num_edges;
        in >> num_vertices >> num_faces >> num_edges;
        for(auto i = 0; i < num_vertices; i++)
        {
            float x, y, z;
            in >> x >> y >> z;
            vertices.push_back(Point3d(x, y, z));
        }
        for(auto j = 0; j < num_faces; j++)
        {
            int edge_vertices;
            in >> edge_vertices;
            vector<int>v;
            for(auto i = 0; i < edge_vertices; i++)
            {
                int indice;
                in >> indice;
                v.push_back(indice);
            }
            faces.push_back(v);
        }
    }
    else
    {
        //文件不存在
        cout << "文件不存在" << endl;
    }
}

void GL3Dwidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
}

void GL3Dwidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    for(auto f: faces)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_POLYGON);
        for(size_t v: f)
        {
            auto x = vertices[v].x;
            auto y = vertices[v].y;
            auto z = vertices[v].z;
            glVertex3f(x, y, z);
        }
        glEnd();
    }
}

void GL3Dwidget::resizeGL(int w, int h)
{
    glViewport(0, 0, static_cast<GLint>(w), static_cast<GLint>(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
