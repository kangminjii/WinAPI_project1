// WinAPI_project1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "WinAPI_project1.h"
#include <cmath>

#define MAX_LOADSTRING 100
#define PI 3.141592
#define degreeToRadian(degree) ((degree) * PI / 180)

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIPROJECT1));

    MSG msg;

    // 기본 메시지 루프입니다:
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
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
    case WM_CREATE: // 초기화 값 세팅
        count = 0;
        yPos = 100;
        line = 0;
        CreateCaret(hWnd, NULL, 5, 15);
        ShowCaret(hWnd);
        break;
    case WM_KEYDOWN: // 눌리면 발생
    {
        int breakpoint = 999;
    }
    break;
    case WM_KEYUP: // 눌렀다 뗄때 발생
    {
        int breakpoint = 999;
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
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

        // 선 그리기
        //POINT center = { 200, 200 };
        //DrawGrid(hdc, center, 10, 10, 10);

        // 원 그리기
        //POINT center = { 200, 100 };
        //DrawCircle(hdc, center, 50);

        // 해바라기 그리기
        //POINT center = { 300, 300 };
        //DrawSunFlower(hdc, center, 40, 10);

        //Rectangle(hdc, 100, 100, 700, 500); // 직사각형
        //POINT pt[5] = { {10,150}, {250,30}, {500,150}, {350,300}, {150,300} };
        //Polygon(hdc, pt, 5); // 다각형


        // 별 그리기
        HPEN hPen, oldPen;
        hPen = CreatePen(PS_DOT, 2, RGB(255, 0, 255));
        oldPen = (HPEN)SelectObject(hdc, hPen);
       
       /* HBRUSH hBrush, oldBrush;
        hBrush = (HBRUSH)GetStockObject(NULL_BRUSH); // 투명하게 색칠
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

// 정보 대화 상자의 메시지 처리기입니다.
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
Q1. 격자 그리기
    DrawGrid(...) 함수 구현하라.
    격자 위치, 격자 Width, Height,
    격자 개수, 또는 격자 간격을 인자로 한다.
*/

void DrawGrid(HDC hdc, POINT center, int width, int height, int count)
{
    center.x -= width * count / 2;
    center.y -= height * count / 2;

    for (int i = 0; i <= count; i++)
    {
        // 세로
        MoveToEx(hdc, center.x + width * i, center.y, NULL);
        LineTo(hdc, center.x + width * i, center.y + height * count);
        // 가로
        MoveToEx(hdc, center.x, center.y + height * i, NULL);
        LineTo(hdc, center.x + width * count, center.y + height * i);
    }
}

/*
Q2. 원 그리기
    DrawCircle(...) 함수를 구현하라.
    원의 위치, 반지름을 인자로 한다.
*/

void DrawCircle(HDC hdc, POINT center, int radius)
{
    Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
}

/*
Q3. 해바라기를 그리는 함수를 구현하라.
    원을 그리기 위한 기본 정보에 외각에 그려질 원의 개수를 입력받아
    해바라기 형식으로 그려지도록 한다.
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
Q4. 별을 그리는 함수를 구현하라.
    별의 위치, 반지름을 인자로 받도록 한다.
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