// WinAPI_project1.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "WinAPI_project1.h"
#include <cmath>

#define PI 3.141592
#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void DrawCircle(HDC hdc, POINT center, int radius);
void DrawStar(HDC hdc, POINT center, int radius);
void DrawRectangle(HDC hdc, POINT center, int width, int height);

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
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
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

    // ���� �׸���
    enum { CIRCLE, RECTANGLE, STAR, NONE };
    static int selectMenu = NONE;
    // �޴�â
    static HMENU hMenu, hSubMenu;
    // ���콺��ġ
    static POINT ptMousePos;

    static bool isClicked;
    static int paste;
    

    switch (message)
    {
    case WM_CREATE: // �ʱ�ȭ �� ����
       
        paste = 0;
        isClicked = FALSE;
        hMenu = GetMenu(hWnd);
        hSubMenu = GetSubMenu(hMenu, 2);
        EnableMenuItem(hSubMenu, ID_EDITCOPY, MF_GRAYED);
        EnableMenuItem(hSubMenu, ID_EDITPASTE, MF_GRAYED);

        break;
    case WM_KEYDOWN: // ������ �߻�
    {
    }
    break;
    case WM_KEYUP: // ������ ���� �߻�
    {
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        if (selectMenu >= 0)
            EnableMenuItem(hSubMenu, ID_EDITCOPY, MF_ENABLED); // ���� ��ư Ȱ��ȭ
       
        // �޴� ������ ���� �м��մϴ�:
        switch (wmId)
        {
        case ID_EDITCOPY: // : �����ϱ� ��ư
            EnableMenuItem(hSubMenu, ID_EDITCOPY, MF_GRAYED); // ���� ��ư ��Ȱ��ȭ
            EnableMenuItem(hSubMenu, ID_EDITPASTE, MF_ENABLED); // �ٿ��ֱ� ��ư Ȱ��ȭ
            InvalidateRgn(hWnd, NULL, TRUE);
        break;
        case ID_EDITPASTE: // : �ٿ��ֱ� ��ư
            paste = 1;
            EnableMenuItem(hSubMenu, ID_EDITPASTE, MF_GRAYED); // �ٿ��ֱ� ��ư ��Ȱ��ȭ
            InvalidateRgn(hWnd, NULL, TRUE);
         break;
        case ID_DRAW_CIRCLE: // : �� �׸���
            isClicked = TRUE;
            selectMenu = CIRCLE;
            InvalidateRgn(hWnd, NULL, TRUE);
        break;
        case ID_DRAW_RECTANGLE:  // : �簢�� �׸���
            isClicked = TRUE;
            selectMenu = RECTANGLE;
            InvalidateRgn(hWnd, NULL, TRUE);
            break;
        case ID_DRAW_STAR: // : �� �׸���
            isClicked = TRUE;
            selectMenu = STAR;
            InvalidateRgn(hWnd, NULL, TRUE);
            break;

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
        //UINT state = GetMenuState(hSubMenu, ID_EDITCOPY, MF_BYCOMMAND);
        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;
    case WM_LBUTTONDOWN: // ���콺 Ŭ����
    {
        ptMousePos.x = LOWORD(lParam);
        ptMousePos.y = HIWORD(lParam);

        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;

    case WM_LBUTTONUP: // ���콺 Ŭ������ ����
    {
    }
    break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);

        switch (selectMenu)
        {
        case CIRCLE:
            DrawCircle(hdc, ptMousePos, 50);
            if (paste)
            {
                DrawCircle(hdc, { 50, 50 }, 50);
                paste = 0;
            }
            break;
        case RECTANGLE:
            DrawRectangle(hdc, ptMousePos, 100, 100);
            if (paste)
            {
                DrawRectangle(hdc, { 50, 50 }, 100, 100);
                paste = 0;
            }
            break;
        case STAR:
            DrawStar(hdc, ptMousePos, 50);
            if (paste)
            {
                DrawStar(hdc, { 50, 50 }, 50);
                paste = 0;
            }
            break;
        default:
            break;
        }
        isClicked = FALSE;

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
      
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

void DrawCircle(HDC hdc, POINT center, int radius)
{
    Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
}
void DrawRectangle(HDC hdc, POINT center, int width, int height)
{
    Rectangle(hdc, center.x - width / 2, center.y - height / 2, center.x + width / 2, center.y + height / 2);
}

void DrawStar(HDC hdc, POINT center, int radius)
{
    double angle = 360 / 10;
    angle = (angle)*PI / 180;

    POINT pt[10] = {};

    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
        {
            pt[i].x = center.x + radius * sin(angle * i);
            pt[i].y = center.y + radius * cos(angle * i);
        }
        if (i % 2 == 1)
        {
            pt[i].x = center.x + (radius / 2) * sin(angle * i);
            pt[i].y = center.y + (radius / 2) * cos(angle * i);
        }
    }

    Polygon(hdc, pt, 10);
}

/*
Q1.
    1. ���� ����
    2. ���� �޴� Ȱ��
    3. ���� �޴� ����
    4. �ٿ� �ֱ� �޴� Ȱ��, ���� �޴� ��Ȱ��
    5. �ٿ� �ֱ� �޴� ����, �ٿ� �ֱ� �޴� ��Ȱ��
    6. ���õ� ���� �����ؼ� �»�ܿ� �׷��ֱ�

*/