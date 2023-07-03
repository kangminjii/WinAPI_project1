// WinAPI_project1.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "WinAPI_project1.h"
#include <cmath>
#include <commdlg.h>
#include <stdio.h>

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

void DrawCircle(HDC hdc, POINT center, int radius);
void DrawStar(HDC hdc, POINT center, int radius);
void DrawRectangle(HDC hdc, POINT center, int width, int height);
void OutFromFile(TCHAR filename[], HWND hwnd);

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

    //�޴� Ŭ���� ���� �׸���
    enum {CIRCLE, RECTANGLE, STAR, NONE};
    static int selectMenu = NONE;
  
    //ä��â
    static TCHAR str[10][128];
    static TCHAR first[128];
    static int count, yPos, line;
    static SIZE size;

    //���콺 ��ġ
    static POINT ptMousePos;

    switch (message)
    {
    case WM_CREATE: // �ʱ�ȭ �� ����
        count = 0;
        yPos = 200;
        line = 0;
        CreateCaret(hWnd, NULL, 5, 15);
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
        // �޴� ������ ���� �м��մϴ�:
        switch (wmId)
        {
        case ID_DRAW_CIRCLE:
            // : �� �׸���
        {
            int temp = selectMenu;
            int ans = MessageBox(hWnd, _T("�� �׸���?"), _T("���� ����"), MB_YESNOCANCEL);
            if (ans == IDYES)
            {
                selectMenu = CIRCLE;
            }
            else if (ans == IDNO)
            {
                selectMenu = NONE;
            }
            else
            {
                selectMenu = temp;
            }
            InvalidateRgn(hWnd, NULL, TRUE);
        }
            break;

        case ID_DRAW_RECTANGLE:
            // : �簢�� �׸���
            selectMenu = RECTANGLE;
            InvalidateRgn(hWnd, NULL, TRUE);
            break;

        case ID_DRAW_STAR:
            // : �� �׸���
            selectMenu = STAR;
            InvalidateRgn(hWnd, NULL, TRUE);
            break;
        
        case ID_FILEOPEN:
        {
            OPENFILENAME ofn;

            TCHAR filter[] = _T("Every file(*.*) \0*.*\0Text File\0*.txt;*.doc\0");
            TCHAR lpstrFile[100] = _T("");
            TCHAR str[100];

            memset(&ofn, 0, sizeof(OPENFILENAME));
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFilter = filter;
            ofn.lpstrFile = lpstrFile;
            ofn.nMaxFile = 100;
            ofn.lpstrInitialDir = _T(".");

            if (GetOpenFileName(&ofn) != 0)
            {
                _stprintf(str, _T("%s ������ ���ڽ��ϱ�?"), ofn.lpstrFile);
                MessageBox(hWnd, str, _T("���� ����"), MB_OK);
                OutFromFile(ofn.lpstrFile, hWnd);
            }
        }
            break;

        case ID_FILESAVE:
        {
            OPENFILENAME ifn;
            TCHAR lpstrFile[100] = _T("");
            TCHAR str[100] = _T("");

            // cout << ���������Է�:
            _stscanf(str, ifn.lpstrFile);
            
            memset(&ifn, 0, sizeof(OPENFILENAME));
            ifn.lStructSize = sizeof(OPENFILENAME);
            ifn.hwndOwner = hWnd;
           // ifn.lpstrFilter = filter;
           // ifn.lpstrFile = lpstrFile;
            ifn.nMaxFile = 100;
            ifn.lpstrInitialDir = _T(".");

            if (GetOpenFileName(&ifn) != 0)
            {
                SaveFromChatting(ifn.lpstrFile, hWnd);
            }
        }
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
        if (wParam == VK_BACK && count > 0)
        {
            count--;
        }
        else if (wParam == VK_RETURN)
        {
            count = 0;
            if (line < 10)
            {
                _tcscpy(str[line], first);
                line++;
            }
            else
            {
                for (int i = 0; i < 9; i++)
                {
                    _tcscpy(str[i], str[i + 1]);
                }
                _tcscpy(str[9], first);
            }
        }
        else
            first[count++] = wParam;
        first[count] = NULL;
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
            break;
        case RECTANGLE:
            DrawRectangle(hdc, ptMousePos, 100, 100); // ���簢��
            break;
        case STAR:
            DrawStar(hdc, ptMousePos, 50);
            break;
        default:
            break;
        }

        GetTextExtentPoint(hdc, str[line], _tcslen(str[line]), &size);

        for (int i = 0; i < 10; i++)
        {
            TextOut(hdc, 100, 20 * i, str[i], _tcslen(str[i]));
        }

        TextOut(hdc, 100, yPos + 20, first, _tcslen(first));

        SetCaretPos(100 + size.cx, yPos + 20);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
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
    angle = degreeToRadian(angle);

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
Q2. p.150 �� �ڵ带 Ȱ���Ͽ� "text.txt" ������ ������ �о� ȭ�鿡 ǥ���ϴ� �ڵ带 �ۼ��϶�.
*/

void OutFromFile(TCHAR filename[], HWND hWnd)
{
    FILE* fPtr;
    HDC hdc;
    int line;
    TCHAR buffer[500];
    
    line = 0;
    hdc = GetDC(hWnd);

#ifdef _UNICODE
    _tfopen_s(&fPtr, filename, _T("r, ccs = UNICODE"));
#else
    _tfopen_s(&fPtr, filename, _T("r"));
#endif
    while (_fgetts(buffer, 100, fPtr) != NULL)
    {
        if (buffer[_tcslen(buffer) - 1] == _T('\n'))
            buffer[_tcslen(buffer) - 1] = NULL;
        TextOut(hdc, 0, line * 20, buffer, _tcslen(buffer));
        line++;
    }
    fclose(fPtr);
    ReleaseDC(hWnd, hdc);
}

void SaveFromChatting(TCHAR filename[], HWND hWnd)
{
    FILE* fPtr;
    HDC hdc;
    int line;
    TCHAR buffer[500];

    line = 0;
    hdc = GetDC(hWnd);




    fclose(fPtr);
    ReleaseDC(hWnd, hdc);
}