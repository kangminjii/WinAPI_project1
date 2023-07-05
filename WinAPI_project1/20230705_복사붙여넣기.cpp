// WinAPI_project1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "WinAPI_project1.h"
#include <cmath>

#define PI 3.141592
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
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

    // 도형 그리기
    enum { CIRCLE, RECTANGLE, STAR, NONE };
    static int selectMenu = NONE;
    // 메뉴창
    static HMENU hMenu, hSubMenu;
    // 마우스위치
    static POINT ptMousePos;

    static bool isClicked;
    static int paste;
    

    switch (message)
    {
    case WM_CREATE: // 초기화 값 세팅
       
        paste = 0;
        isClicked = FALSE;
        hMenu = GetMenu(hWnd);
        hSubMenu = GetSubMenu(hMenu, 2);
        EnableMenuItem(hSubMenu, ID_EDITCOPY, MF_GRAYED);
        EnableMenuItem(hSubMenu, ID_EDITPASTE, MF_GRAYED);

        break;
    case WM_KEYDOWN: // 눌리면 발생
    {
    }
    break;
    case WM_KEYUP: // 눌렀다 뗄때 발생
    {
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        if (selectMenu >= 0)
            EnableMenuItem(hSubMenu, ID_EDITCOPY, MF_ENABLED); // 복사 버튼 활성화
       
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case ID_EDITCOPY: // : 복사하기 버튼
            EnableMenuItem(hSubMenu, ID_EDITCOPY, MF_GRAYED); // 복사 버튼 비활성화
            EnableMenuItem(hSubMenu, ID_EDITPASTE, MF_ENABLED); // 붙여넣기 버튼 활성화
            InvalidateRgn(hWnd, NULL, TRUE);
        break;
        case ID_EDITPASTE: // : 붙여넣기 버튼
            paste = 1;
            EnableMenuItem(hSubMenu, ID_EDITPASTE, MF_GRAYED); // 붙여넣기 버튼 비활성화
            InvalidateRgn(hWnd, NULL, TRUE);
         break;
        case ID_DRAW_CIRCLE: // : 원 그리기
            isClicked = TRUE;
            selectMenu = CIRCLE;
            InvalidateRgn(hWnd, NULL, TRUE);
        break;
        case ID_DRAW_RECTANGLE:  // : 사각형 그리기
            isClicked = TRUE;
            selectMenu = RECTANGLE;
            InvalidateRgn(hWnd, NULL, TRUE);
            break;
        case ID_DRAW_STAR: // : 별 그리기
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
    case WM_LBUTTONDOWN: // 마우스 클릭시
    {
        ptMousePos.x = LOWORD(lParam);
        ptMousePos.y = HIWORD(lParam);

        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;

    case WM_LBUTTONUP: // 마우스 클릭에서 땔때
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
    1. 도형 선택
    2. 복사 메뉴 활성
    3. 복사 메뉴 선택
    4. 붙여 넣기 메뉴 활성, 복사 메뉴 비활성
    5. 붙여 넣기 메뉴 선택, 붙여 넣기 메뉴 비활성
    6. 선택된 도형 복사해서 좌상단에 그려주기

*/