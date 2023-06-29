// WinAPI_project1.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "WinAPI_project1.h"
#include <cmath>

#define MAX_LOADSTRING 100
#define PI 3.141592
#define degreeToRadian(degree) ((degree) * PI / 180)

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


void DrawGrid(HDC hdc, POINT center, int width, int height, int count);
void DrawCircle(HDC hdc, POINT center, int radius);
void DrawSunFlower(HDC hdc, POINT center, int radius, int count);
void DrawStar(HDC hdc, POINT center, int radius, int number);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIPROJECT1));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_IBEAM);
    wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(220, 255, 100));
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPIPROJECT1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ�:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        300, 300, 800, 800, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    static TCHAR str[100];
    static int count, yPos, line;
    static SIZE size;

    switch (message)
    {
    case WM_CREATE: // �ʱ�ȭ �� ����
        count = 0;
        yPos = 100;
        line = 0;
        CreateCaret(hWnd, NULL, 5, 15);
        ShowCaret(hWnd);
        break;
    case WM_KEYDOWN: // ������ �߻�
    {
        int breakpoint = 999;
    }
    break;
    case WM_KEYUP: // ������ ���� �߻�
    {
        int breakpoint = 999;
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // �޴� ������ ���� �м��մϴ�:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_CHAR:
    {
        int breakpoint = 999;

        if (wParam == VK_BACK && count > 0)
            count--;
        else
            str[count++] = wParam;
        str[count] = NULL;
        InvalidateRect(hWnd, NULL, TRUE);

    }
    break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);

        GetTextExtentPoint(hdc, str, _tcslen(str), &size);
        TextOut(hdc, 100, yPos, str, _tcslen(str));

        // �� �׸���
        //POINT center = { 200, 200 };
        //DrawGrid(hdc, center, 10, 10, 10);

        // �� �׸���
        //POINT center = { 200, 100 };
        //DrawCircle(hdc, center, 50);

        // �عٶ�� �׸���
        //POINT center = { 300, 300 };
        //DrawSunFlower(hdc, center, 40, 10);

        //Rectangle(hdc, 100, 100, 700, 500); // ���簢��
        //POINT pt[5] = { {10,150}, {250,30}, {500,150}, {350,300}, {150,300} };
        //Polygon(hdc, pt, 5); // �ٰ���


        // �� �׸���
        HPEN hPen, oldPen;
        hPen = CreatePen(PS_DOT, 2, RGB(255, 0, 255));
        oldPen = (HPEN)SelectObject(hdc, hPen);
       
       /* HBRUSH hBrush, oldBrush;
        hBrush = (HBRUSH)GetStockObject(NULL_BRUSH); // �����ϰ� ��ĥ
        oldBrush = (HBRUSH)SelectObject(hdc, hBrush);*/

        POINT center = { 300, 300 };
        DrawStar(hdc, center, 50, 5);

        SelectObject(hdc, oldPen);
        DeleteObject(hPen);
      
        /*SelectObject(hdc, oldBrush);
        DeleteObject(hBrush);*/
        //SetCaretPos(100 + size.cx, yPos);
        
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        //HideCaret(hWnd);
        DestroyCaret();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

/*
Q1. ���� �׸���
    DrawGrid(...) �Լ� �����϶�.
    ���� ��ġ, ���� Width, Height,
    ���� ����, �Ǵ� ���� ������ ���ڷ� �Ѵ�.
*/

void DrawGrid(HDC hdc, POINT center, int width, int height, int count)
{
    center.x -= width * count / 2;
    center.y -= height * count / 2;

    for (int i = 0; i <= count; i++)
    {
        // ����
        MoveToEx(hdc, center.x + width * i, center.y, NULL);
        LineTo(hdc, center.x + width * i, center.y + height * count);
        // ����
        MoveToEx(hdc, center.x, center.y + height * i, NULL);
        LineTo(hdc, center.x + width * count, center.y + height * i);
    }
}

/*
Q2. �� �׸���
    DrawCircle(...) �Լ��� �����϶�.
    ���� ��ġ, �������� ���ڷ� �Ѵ�.
*/

void DrawCircle(HDC hdc, POINT center, int radius)
{
    Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
}

/*
Q3. �عٶ�⸦ �׸��� �Լ��� �����϶�.
    ���� �׸��� ���� �⺻ ������ �ܰ��� �׷��� ���� ������ �Է¹޾�
    �عٶ�� �������� �׷������� �Ѵ�.
*/

void DrawSunFlower(HDC hdc, POINT center, int radius, int count)
{
    Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);

    double angle = 360.0 / double(count);
    angle = degreeToRadian(angle);

    double radius1 = (radius * sin(angle / 2)) / (1 - sin(angle / 2));
    double length = radius + radius1;

    for (int i = 0; i < count; i++)
    {
        POINT a;
      
        a.x = center.x + (length * sin(angle * i));
        a.y = center.y + (length * cos(angle * i));
        DrawCircle(hdc, a, radius1);
        //Ellipse(hdc, a.x - radius1, a.y - radius1, a.x + radius1, a.y + radius1);
    }
}

/*
Q4. ���� �׸��� �Լ��� �����϶�.
    ���� ��ġ, �������� ���ڷ� �޵��� �Ѵ�.
*/

void DrawStar(HDC hdc, POINT center, int radius, int number)
{
    double angle = 360 / number;
    double radius2 = radius / sin((degreeToRadian(angle/2)));

    for (int i = 0; i < number; i++)
    {
        int x = center.x + (radius * sin(degreeToRadian(angle * i)));
        int y = center.y + (radius * cos(degreeToRadian(angle * i)));
        int x1 = center.x + (radius2 * sin(degreeToRadian(angle * i - angle/2)));
        int y1 = center.y + (radius2 * cos(degreeToRadian(angle * i - angle/2)));
        int x2 = center.x + (radius2 * sin(degreeToRadian(angle * i + angle/2)));
        int y2 = center.y + (radius2 * cos(degreeToRadian(angle * i + angle/2)));

        POINT pt[4] = { {x, y}, {x1, y1}, {x, y}, {x2, y2} };
        Polygon(hdc, pt, 4);
    }
}