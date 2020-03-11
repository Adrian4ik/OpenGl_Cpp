#define UNICODE

// WinAPI
#include <Windows.h>
#include <tchar.h>
 
// Other
#include <iostream> // для setlocale(LC_ALL, "Russian");
#include <math.h>
#include <string>
#include <vector>

// OpenGL
#pragma comment(lib, "opengl32.lib")

// GLUT
#pragma comment(lib, "glut32.lib")
#include "glut.h"

int Angle = 0;

// Функции для работы с OpenGL/GLUT
void GLInit();
void GLRenderScene();
void GLKeyDown(unsigned char key, int x, int y);

using namespace std;

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nShowCmd)
{
    // Аргументы командной строки (путь к EXE)
    char* argv0 = new char[512];
    GetModuleFileNameA(0, argv0, 512);

    // Число аргументов (один только путь к EXE, поэтому, argc = 1)
    int argc = 1;

    // Инициализация GLUT, для данного EXE
    glutInit(&argc, &argv0);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_SINGLE | GLUT_RGB);

    // Координаты и размер окна GLUT
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(800, 600);

    // Создание окна GLUT
    glutCreateWindow("OpenGL C++");

    // Обработчик рендеринга (вызывается при отрисовке окна, аналогично WM_PAINT)
    glutDisplayFunc(GLRenderScene);

    // Обработчик клавитуры (при WM_KEYDOWN)
    glutKeyboardFunc(GLKeyDown);

    // Инициализация OpenGL
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

    // Главный цикл приложения
    glutMainLoop();
    
    return 0;
}

void GLInit()
{
    // Цвет фона - черный
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void GLRenderScene()
{
    // Очищаем буфер цвета и глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // Включаем тест глубины,
   // чтобы грани 3D-фигур - рисовались непрозрачными, и не просвечивали
    glEnable(GL_DEPTH_TEST);

    // Поворот
    glRotatef(Angle, 1.0f, 1.0f, 0.0f);

    // -------- Рисование параллелепипеда ----------
    // Длина x высота x глубина:
    //   0.5    1.0      0.25

    // Передняя грань
    glColor3f(0.0f, 1.0f, 0.0f); // зеленый
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, 0.0f, 0.0f); // ЛН
    glVertex3f(0.0f, 1.0f, 0.0f); // ЛВ
    glVertex3f(0.5f, 1.0f, 0.0f); // ПВ
    glVertex3f(0.5f, 0.0f, 0.0f); // ПН
    glEnd();

    // Задняя грань
    // Та же передняя, только, Z = 0.25, а, не 0
    glColor3f(1.0f, 0.0f, 0.0f); // красный
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, 0.0f, 0.25f); // ЛН
    glVertex3f(0.0f, 1.0f, 0.25f); // ЛВ
    glVertex3f(0.5f, 1.0f, 0.25f); // ПВ
    glVertex3f(0.5f, 0.0f, 0.25f); // ПН
    glEnd();

    // Левая грань
    glColor3f(1.0f, 1.0f, 0.0f); // желтый
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, 0.0f, 0.0f); // Перед-низ
    glVertex3f(0.0f, 1.0f, 0.0f); // Перед-верх
    glVertex3f(0.0f, 1.0f, 0.25f); // Зад-верх
    glVertex3f(0.0f, 0.0f, 0.25f); // Зад-низ
    glEnd();

    // Правая грань
    // Та же левая, только, X = 0.5
    glColor3f(0.0f, 1.0f, 1.0f); // Голубой
    glBegin(GL_POLYGON);
    glVertex3f(0.5f, 0.0f, 0.0f); // Перед-низ
    glVertex3f(0.5f, 1.0f, 0.0f); // Перед-верх
    glVertex3f(0.5f, 1.0f, 0.25f); // Зад-верх
    glVertex3f(0.5f, 0.0f, 0.25f); // Зад-низ
    glEnd();

    // Верхняя грань
    glColor3f(1.0f, 0.0f, 1.0f); // Розовый
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, 1.0f, 0.0f); // Перед-лево
    glVertex3f(0.5f, 1.0f, 0.0f); // Перед-право
    glVertex3f(0.5f, 1.0f, 0.25f); // Зад-право
    glVertex3f(0.0f, 1.0f, 0.25f); // Зад-лево
    glEnd();

    // Нижняя грань
    // Та же верхняя, только, Y = 0
    glColor3f(1.0f, 1.0f, 1.0f); // Белый
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, 0.0f, 0.0f); // Перед-лево
    glVertex3f(0.5f, 0.0f, 0.0f); // Перед-право
    glVertex3f(0.5f, 0.0f, 0.25f); // Зад-право
    glVertex3f(0.0f, 0.0f, 0.25f); // Зад-лево
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
            Angle -= 5; // Уменьшаем угол поворота на 5 градусов

            glutPostRedisplay(); // Перерисовываем окно
            break;
        case VK_RIGHT:
            Angle += 5; // Увеличиваем угол поворота на 5 градусов

            glutPostRedisplay(); // Перерисовываем окно
            break;
    }
}