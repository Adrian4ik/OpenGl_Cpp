#define UNICODE

// WinAPI
#include <Windows.h>
#include <tchar.h>
 
// Other
#include <iostream> // ��� setlocale(LC_ALL, "Russian");
#include <math.h>
#include <string>
#include <vector>

// OpenGL
#pragma comment(lib, "opengl32.lib")

// GLUT
#pragma comment(lib, "glut32.lib")
#include "glut.h"

int Angle = 0;

// ������� ��� ������ � OpenGL/GLUT
void GLInit();
void GLRenderScene();
void GLKeyDown(unsigned char key, int x, int y);

using namespace std;

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nShowCmd)
{
    // ��������� ��������� ������ (���� � EXE)
    char* argv0 = new char[512];
    GetModuleFileNameA(0, argv0, 512);

    // ����� ���������� (���� ������ ���� � EXE, �������, argc = 1)
    int argc = 1;

    // ������������� GLUT, ��� ������� EXE
    glutInit(&argc, &argv0);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_SINGLE | GLUT_RGB);

    // ���������� � ������ ���� GLUT
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(800, 600);

    // �������� ���� GLUT
    glutCreateWindow("OpenGL C++");

    // ���������� ���������� (���������� ��� ��������� ����, ���������� WM_PAINT)
    glutDisplayFunc(GLRenderScene);

    // ���������� ��������� (��� WM_KEYDOWN)
    glutKeyboardFunc(GLKeyDown);

    // ������������� OpenGL
    GLInit();

    string hopa = "OpenGL C++ Window: ";
    int ww = glutGet(GLUT_WINDOW_WIDTH);
    hopa += to_string(ww);
    int wh = glutGet(GLUT_WINDOW_HEIGHT);
    hopa += "x";
    hopa += to_string(wh);
    int sw = glutGet(GLUT_SCREEN_WIDTH);
    hopa += "; screen: ";
    hopa += to_string(sw);
    int sh = glutGet(GLUT_SCREEN_HEIGHT);
    hopa += "x";
    hopa += to_string(sh);

    const char* cstr = &hopa[0];

    glutSetWindowTitle(cstr);

    // ������� ���� ����������
    glutMainLoop();
    
    return 0;
}

void GLInit()
{
    // ���� ���� - ������
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void GLRenderScene()
{
    // ������� ����� ����� � �������
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // �������� ���� �������,
   // ����� ����� 3D-����� - ���������� �������������, � �� ������������
    glEnable(GL_DEPTH_TEST);

    // �������
    glRotatef(Angle, 1.0f, 1.0f, 0.0f);

    // -------- ��������� ��������������� ----------
    // ����� x ������ x �������:
    //   0.5    1.0      0.25

    // �������� �����
    glColor3f(0.0f, 1.0f, 0.0f); // �������
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, 0.0f, 0.0f); // ��
    glVertex3f(0.0f, 1.0f, 0.0f); // ��
    glVertex3f(0.5f, 1.0f, 0.0f); // ��
    glVertex3f(0.5f, 0.0f, 0.0f); // ��
    glEnd();

    // ������ �����
    // �� �� ��������, ������, Z = 0.25, �, �� 0
    glColor3f(1.0f, 0.0f, 0.0f); // �������
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, 0.0f, 0.25f); // ��
    glVertex3f(0.0f, 1.0f, 0.25f); // ��
    glVertex3f(0.5f, 1.0f, 0.25f); // ��
    glVertex3f(0.5f, 0.0f, 0.25f); // ��
    glEnd();

    // ����� �����
    glColor3f(1.0f, 1.0f, 0.0f); // ������
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, 0.0f, 0.0f); // �����-���
    glVertex3f(0.0f, 1.0f, 0.0f); // �����-����
    glVertex3f(0.0f, 1.0f, 0.25f); // ���-����
    glVertex3f(0.0f, 0.0f, 0.25f); // ���-���
    glEnd();

    // ������ �����
    // �� �� �����, ������, X = 0.5
    glColor3f(0.0f, 1.0f, 1.0f); // �������
    glBegin(GL_POLYGON);
    glVertex3f(0.5f, 0.0f, 0.0f); // �����-���
    glVertex3f(0.5f, 1.0f, 0.0f); // �����-����
    glVertex3f(0.5f, 1.0f, 0.25f); // ���-����
    glVertex3f(0.5f, 0.0f, 0.25f); // ���-���
    glEnd();

    // ������� �����
    glColor3f(1.0f, 0.0f, 1.0f); // �������
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, 1.0f, 0.0f); // �����-����
    glVertex3f(0.5f, 1.0f, 0.0f); // �����-�����
    glVertex3f(0.5f, 1.0f, 0.25f); // ���-�����
    glVertex3f(0.0f, 1.0f, 0.25f); // ���-����
    glEnd();

    // ������ �����
    // �� �� �������, ������, Y = 0
    glColor3f(1.0f, 1.0f, 1.0f); // �����
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, 0.0f, 0.0f); // �����-����
    glVertex3f(0.5f, 0.0f, 0.0f); // �����-�����
    glVertex3f(0.5f, 0.0f, 0.25f); // ���-�����
    glVertex3f(0.0f, 0.0f, 0.25f); // ���-����
    glEnd();

    glutSwapBuffers();
}

void GLKeyDown(unsigned char key, int x, int y)
{
    switch (key)
    {
        case VK_ESCAPE:
            exit(0);
            break;
        case VK_LEFT:
            Angle -= 5; // ��������� ���� �������� �� 5 ��������

            glutPostRedisplay(); // �������������� ����
            break;
        case VK_RIGHT:
            Angle += 5; // ����������� ���� �������� �� 5 ��������

            glutPostRedisplay(); // �������������� ����
            break;
    }
}