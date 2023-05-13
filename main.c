#include <windows.h>
#include <gl/gl.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "L_sys.h"


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

int width, height;
typedef struct {
    float x, y;
    float angle;
}   TDrawer;

TDrawer d;
TDrawer d2;
TDrawer dL;
TDrawer dR;
BOOL flag = FALSE;
int sign = -1;
int n = 0;
float p = 1;
int deg = 0;


void InitDrawer(TDrawer *obj, float x1, float y1, float alfa)
{   // Initialize turtle
    x1 /= (float)width;
    y1 /= (float)height;
    obj->x = x1;
    obj->y = y1;
    obj->angle = alfa * M_PI / 180;
}

void setD(TDrawer *obj, TDrawer *d)
{   // Variable assignment
    obj->x = d->x;
    obj->y = d->y;
    obj->angle = d->angle;
}

void putToD(float x1, float y1, float alfa, TDrawer *obj)
{   // Values assignment
    obj->x = x1;
    obj->y = y1;
    obj->angle = alfa * M_PI / 180;
}

void moveToD(float f, TDrawer *obj)
{   // Object movement without drawing
    float newX = (f*cos(obj->angle)/width+obj->x);
    float newY = (f*sin(obj->angle)/height+obj->y);

    obj->x = newX;
    obj->y = newY;
}

void forwardD(float f, TDrawer *obj)
{   // Object movement with drawing
    void Line(float x1, float y1, float x2, float y2)
    {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    float newX = (f*cos(obj->angle)/width+obj->x);
    float newY = (f*sin(obj->angle)/height+obj->y);

    // Black line drawing code
    //glColor3f(0,0,0);
    glBegin(GL_LINES);
    Line(obj->x,obj->y, newX,newY);
    glEnd();

    obj->x = newX;
    obj->y = newY;
}

void rightD(float alfa, TDrawer *obj)
{   // turn right n degrees (not radians)
    obj->angle -= alfa * M_PI / 180;
}

void leftD(float alfa, TDrawer *obj)
{   // turn left n degrees
    obj->angle += alfa * M_PI / 180;
}

//--------------------STACK---------------------
typedef struct {
    int MAX;    // Top of stack
    int tos;    // Current stack element index
    TDrawer *stack; // Array of stack elements
} Tstack_Drawer;

void InitDrawerStack(Tstack_Drawer *obj, int tos, int MAX)
{   // Setter
    obj->tos = tos;
    obj->MAX = MAX;
    obj->stack = (TDrawer*)malloc(sizeof(TDrawer) * MAX);
}

void push_Drawer(Tstack_Drawer *stackD, TDrawer *d)
{
    if (stackD->tos >= stackD->MAX)
    {
        printf("Stack Overflow!");
        return;
    }
    // Add current statement of object d
    // and increment stack index
    setD(&stackD->stack[stackD->tos], d);
    stackD->tos += 1;
}

void pop_Drawer(Tstack_Drawer *stackD, TDrawer *obj)
{
    stackD->tos -= 1;
    if (stackD->tos < 0)
    {   // If stack is empty return it index
        // to last position
        printf("Stack is empty!");
        stackD->tos += 1;
    }
    setD(obj, &stackD->stack[stackD->tos]);

}
//--------------------STACK---------------------


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          1000,
                          1000,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    char *axiom = (char*)malloc(2);
    axiom = set_str(axiom, "0");
    axiom = set_str(axiom, Generate_Lsys_2(axiom, 3));
    //int deg = 240;
    //int go = 30;
    char *A = (char *)malloc(2);
    A = "F";
    A = set_str(A, Generate_Lsys(A, 2));

    Tstack_Drawer stackDL;
    InitDrawerStack(&stackDL, 0, 20);


    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClearColor(1,1,1, 0);
            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();
                glLoadIdentity();
                glOrtho(0,width, height,0, -1,1);
            glPopMatrix();

            InitDrawer(&d, 300, 300, 0);
            InitDrawer(&d2, -100,-350, 0);
            InitDrawer(&dL, 0, -600, 90);
            InitDrawer(&dR, 0, 0, 0);

            /* Serpinskiy's triangle
            for (int side = 0; side < 6; side++)
            {
                for (int i = 0; i < len(A); i++)
                {
                    if (A[i] == '+')
                        rightD(deg, &d);
                    if (A[i] == '-')
                        leftD(deg, &d);
                    if (A[i] == 'F')
                        forwardD(10, &d);
                }
                leftD(60, &d);
            }

            deg -= sign;
            if (deg == 90) sign = 1;
            if (deg == -90) sign = -1;
            */
            //
            /*
            forwardD(200, &d);
            push_Drawer(&stackDL, &d);
            rightD(45, &d);
            forwardD(100, &d);
            pop_Drawer(&stackDL, &d);
            leftD(45, &d);
            forwardD(100, &d);
            */

            // Dragon curve
            /*
            if (flag)
            {
                axiom = set_str(axiom, Generate_Lsys_DragonC(axiom, n));
                flag = FALSE;
            }


            for (int side = 0; side < 4; side++)
            {
                for (int i = 0; i < len(axiom); i++)
                {
                    if (axiom[i] == 'F')
                    {
                        glColor3f(0,0,1);
                        forwardD(10 + p, &dR);
                    }
                    if (axiom[i] == '+')
                    {
                        rightD(deg, &dR);
                    }
                    if (axiom[i] == '-')
                    {
                        leftD(deg, &dR);
                    }

                    glColor3f(1,0,0);
                    forwardD(2, &dR);
                }
                leftD(90, &dR);

            }
            */
            // Piphagor's tree
            axiom = set_str(axiom, Generate_Lsys_2(axiom, n));

            for (int i = 0; i < len(axiom); i++)
            {
                if (axiom[i] == '0')
                {
                    glColor3f(0,0,1);
                    forwardD(10 + p, &dL);
                }
                if (axiom[i] == '1')
                {
                    glColor3f(0,1,0);
                    forwardD(15 + p, &dL);
                }
                if (axiom[i] == '[')
                {
                    push_Drawer(&stackDL, &dL);
                    leftD(deg, &dL);
                }
                if (axiom[i] == ']')
                {
                    pop_Drawer(&stackDL, &dL);
                    rightD(deg, &dL);
                }
                glColor3f(1,0,0);
                forwardD(6, &dL);
            }


            /* Random geometry
            for (int i = 0; i < 50; i++)
            {
                forwardD(20, &d);
                leftD(7.2, &d);
            }

            float n = 5;
            putToD(0,0, 360/n, &d);
            for (int i = 0; i < n; i++)
            {
                forwardD(200, &d);
                rightD(360/n, &d);
            }

            for (int i = 0; i < 100; i++)
            {
                if (i % 2 == 0)
                    forwardD(i/2, &d2);
                else
                    moveToD(i/2, &d2);
                rightD(7.2/2, &d2);
            }
            for (int i = 0; i < 101; i++)
            {
                forwardD(i/2, &d2);
                leftD(7.2/2, &d2);
            }
            */

            SwapBuffers(hDC);

            theta += 0.1f;
            Sleep (1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_SIZE:
            width = LOWORD(lParam);
            height = HIWORD(lParam);
            glViewport(0,0, LOWORD(lParam), HIWORD(lParam));
            glLoadIdentity();
            float k = LOWORD(lParam) / (float)HIWORD(lParam);
            glOrtho(-k, k, -1,1, -1,1);
        break;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                    break;
                case VK_LEFT:
                    deg++;
                    break;
                case VK_RIGHT:
                    deg--;
                    break;
                case VK_UP:
                    flag = !flag;
                    n++;
                    break;
                case VK_DOWN:
                    flag = !flag;
                    n--;
                    break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

