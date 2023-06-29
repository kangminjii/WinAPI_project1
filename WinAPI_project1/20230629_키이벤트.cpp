// WinAPI_project1.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "WinAPI_project1.h"

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
    HBRUSH hBrush, oldBrush; // ��ĥ

    static TCHAR str[100];
    static SIZE size;
    static int down, up, yPos, count;

    switch (message)
    {
    case WM_CREATE: // �ʱ�ȭ �� ����
        down = 0;
        up = 0;
        yPos = 100;
        break;
    case WM_KEYDOWN: // ������ �߻�
    {
        if (wParam == VK_DOWN)
            down = 1;

        if (wParam == VK_UP)
            up = 1;

        InvalidateRect(hWnd, NULL, TRUE); // �ٽ� �׷��ֱ�, ȭ�� ���� �����Լ�
    }
    break;
    case WM_KEYUP: // ������ ���� �߻�
    {
        if (wParam == VK_DOWN)
            down = 0;

        if (wParam == VK_UP)
            up = 0;

        InvalidateRect(hWnd, NULL, TRUE);
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
        str[count++] = wParam;
        str[count] = NULL;
        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);

        //GetTextExtentPoint(hdc, str, _tcslen(str), &size);
       //TextOut(hdc, 100, yPos, str, _tcslen(str));

        POINT center = { 300,300 };
        
        Rectangle(hdc, center.x - 75, center.y + 50, center.x - 25, center.y - 50);     // Left
        Rectangle(hdc, center.x - 25, center.y - 50, center.x + 25, center.y - 150);    // Up
        Rectangle(hdc, center.x + 75, center.y + 50, center.x + 25, center.y - 50);     // Right
        Rectangle(hdc, center.x - 25, center.y + 150, center.x + 25, center.y + 50);    // Down
        
        if (down == 1)
        {
            hBrush = CreateSolidBrush(RGB(0, 0, 255));
            oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
            Rectangle(hdc, center.x - 25, center.y + 150, center.x + 25, center.y + 50);    // Down
        }
        else
        {
            hBrush = CreateSolidBrush(RGB(255, 255, 255));
            oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
            Rectangle(hdc, center.x - 25, center.y + 150, center.x + 25, center.y + 50);    // Down
        }

        if (up == 1)
        {
            hBrush = CreateSolidBrush(RGB(0, 0, 255));
            oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
            Rectangle(hdc, center.x - 25, center.y - 50, center.x + 25, center.y - 150);    // Up
        }
        else
        {
            hBrush = CreateSolidBrush(RGB(255, 255, 255));
            oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
            Rectangle(hdc, center.x - 25, center.y - 50, center.x + 25, center.y - 150);    // Up
        }


        SelectObject(hdc, oldBrush);
        DeleteObject(hBrush);
       
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

/*
Q1. p.93 ���� 7
    - Ű down, up ���� üũ
    - ȭ�� ���� �̺�Ʈ �߻�
    - ���¿� �ٶ� �簢�� 4�� �׷��ֱ�
*/

