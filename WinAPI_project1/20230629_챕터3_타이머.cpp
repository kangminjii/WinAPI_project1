// WinAPI_project1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "WinAPI_project1.h"
#include "CObject.h"
#include <cmath>


#define MAX_LOADSTRING 100
#define timer_ID_1 11
#define timer_ID_2 12
const int circleRadius = 50;

double LengthPts(POINT pt1, POINT pt2)
{
    return (sqrt((float)(pt2.x - pt1.x) * (pt2.x - pt1.x) + (pt2.y - pt1.y) * (pt2.y - pt1.y)));
}

BOOL InCircle(POINT pt1, POINT pt2)
{
    if (LengthPts(pt1, pt2) < circleRadius)  return TRUE;

    return FALSE;
}


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    static POINT ptCurPos;
    static POINT ptMousePos;
    static RECT rectView;

    static bool bFlag;

    switch (message)
    {
    case WM_CREATE: // 초기화 값 세팅
    {
        ptCurPos.x = 100;
        ptCurPos.y = 100;
        bFlag = FALSE;
        GetClientRect(hWnd, &rectView); // 윈도우창 크기값을 rectView에 저장함
        //SetTimer(hWnd, timer_ID_1, 500, NULL);
        //SetTimer(hWnd, timer_ID_2, 1000, NULL);
    }
    break;

    case WM_TIMER: // 타이머 이벤트, 타이머는 일이 바쁘지 않을때만 잘 작동됨
    {
        if (wParam == timer_ID_1)
        {
            ptCurPos.x += circleRadius;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        if (wParam == timer_ID_2)
        {
            ptCurPos.y += circleRadius;
            InvalidateRect(hWnd, NULL, TRUE);
        }
    }
    break;

    case WM_KEYDOWN: // 눌리면 발생
    {
        if (wParam == VK_RIGHT || wParam == VK_LEFT || wParam == VK_UP || wParam == VK_DOWN)
            bFlag = TRUE;

        // 화면 경계선 밖으로 못나가게 정함
        if (wParam == VK_RIGHT)
        {
            ptCurPos.x += circleRadius;
            if (ptCurPos.x + circleRadius > rectView.right)
                ptCurPos.x = rectView.right - circleRadius;
        }
        else if (wParam == VK_LEFT)
        {
            ptCurPos.x -= circleRadius;
            if (ptCurPos.x - circleRadius < rectView.left)
                ptCurPos.x = rectView.left + circleRadius;
        }
        else if (wParam == VK_UP)
        {
            ptCurPos.y -= circleRadius;
            if (ptCurPos.y - circleRadius < rectView.top)
                ptCurPos.y = rectView.top + circleRadius;
        }
        else if (wParam == VK_DOWN)
        {
            ptCurPos.y += circleRadius;
            if (ptCurPos.y + circleRadius > rectView.bottom)
                ptCurPos.y = rectView.bottom - circleRadius;
        }
        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;

    case WM_KEYUP: // 눌렀다 뗄때 발생
    {
        bFlag = FALSE;
        InvalidateRect(hWnd, NULL, TRUE);
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
    }
    break;

    case WM_LBUTTONDOWN:
    {
        ptMousePos.x = LOWORD(lParam);
        ptMousePos.y = HIWORD(lParam);
        if (InCircle(ptMousePos, ptCurPos))
            bFlag = TRUE;
        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;

    case WM_LBUTTONUP:
    {
        bFlag = FALSE;
        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;

    case WM_MOUSEMOVE:
    {
        if (bFlag)
        {
            ptCurPos.x = LOWORD(lParam);
            ptCurPos.y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, TRUE);
        }
    }
    break;

    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);

        if (bFlag) // 키를 누를때만 원에 색칠되게함
            SelectObject(hdc, GetStockObject(LTGRAY_BRUSH));

        if(bFlag)
            Ellipse(hdc, ptCurPos.x - circleRadius, ptCurPos.y - circleRadius, ptCurPos.x + circleRadius, ptCurPos.y + circleRadius);

        /*if (bFlag)
            Rectangle(hdc, ptCurPos.x - circleRadius, ptCurPos.y - circleRadius, ptCurPos.x + circleRadius, ptCurPos.y + circleRadius);*/

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        KillTimer(hWnd, timer_ID_1);

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