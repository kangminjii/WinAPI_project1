// WinAPI_project1.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "WinAPI_project1.h"
#include <cmath>
#include "Circle.h"
#include "Square.h"
#include "Star.h"
#include <time.h>

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


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //TODO: 여기에 코드를 입력합니다.
    //
    //전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

     //애플리케이션 초기화를 수행합니다:
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



  //함수: MyRegisterClass()
  //
  //용도: 창 클래스를 등록합니다.

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


 /*  함수: InitInstance(HINSTANCE, int)

   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.

   주석:

        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
        주 프로그램 창을 만든 다음 표시합니다.*/

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


 /* 함수: WndProc(HWND, UINT, WPARAM, LPARAM)

  용도: 주 창의 메시지를 처리합니다.

  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
  WM_PAINT    - 주 창을 그립니다.
  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.*/


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    srand(time(NULL));

    static Circle c[100];
    static Square r[100];
    static Star s[100];
    static RECT rectView;
    static int count;
    static int random = rand() % 2;

    switch (message)
    {
    case WM_CREATE: // 초기화 값 세팅
    {
        count = 0;
        GetClientRect(hWnd, &rectView); // 윈도우창 크기값을 rectView에 저장함
        SetTimer(hWnd, 1, 100, NULL);
    }
    break;

    case WM_TIMER: // 타이머 이벤트, 타이머는 일이 바쁘지 않을때만 잘 작동됨
    {
        for (int i = 0; i < count; i++)
        {
            c[i].Update(rectView);
            r[i].Update(rectView);
            s[i].Update(rectView);
        }

        InvalidateRect(hWnd, NULL, TRUE);
    }
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

    case WM_LBUTTONDOWN: // 마우스 클릭시
    {
        random = rand() % 3;
        if(random == 0)
            c[count++].SetPosition(LOWORD(lParam), HIWORD(lParam));
        else if(random == 1)
            r[count++].SetPosition(LOWORD(lParam), HIWORD(lParam));
        else if(random == 2)
            s[count++].SetPosition(LOWORD(lParam), HIWORD(lParam));
        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;

    case WM_LBUTTONUP: // 마우스 클릭에서 땔때
    {
    }
    break;

    case WM_MOUSEMOVE:
    {
    }
    break;

    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        
        for (int i = 0; i < count; i++)
        {
            c[i].Draw(hdc);
            r[i].Draw(hdc);
            s[i].Draw(hdc);
        }
       
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        KillTimer(hWnd, 1);

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
Q2.
    1. 클라이언트 영역에 마우스 클릭, 그 위치에 원을 생성
        기본으로 원 생성
        1.1 랜덤으로 사각형, 원, 별이 생성되도록 한다.

    2. 임의의 방향으로 이동 / 클라이언트 외곽에서 반사
    3. 클래스로 구현
        사각형/별도 같은 식으로 작동하도록 한다.

    4. 다른 오브젝트와의 관계 설정
        모드 설정 1번 반사, 2번 합체, 3번 분열로 키 설정
       4.1 반사 - 다른 오브젝트와 부딪히면 튕기기
       4.2 합체 - 상성 관계에 따라 다른 오브젝트와 만나면 합체해서 커지게 하기
       4.3 분열 - 상성 관계에 따라 다른 오브젝트와 만나면 분열해서 작아지게 하기
                별 > 원 > 사각형 > 별

    5. 일정 크기 이상, 또는 이하는 사라지도록 한다.

    6. 각 오브젝트를 회전 시킨다.

        CObject
        {
            protected :
                좌표
                이동 스피드
                이동 방향
                타입 ( 원, 별, 사각형 )
            public :
                virtual void Update() = 0;
                virtual void Draw() = 0; // 자기 자신을 그리는 함수
                virtual BOOL Collision() = 0;
             그 외 함수
        };

        CCirlce : public CObject
        {
            private :
                반지름
            public :
                virtual void Update() override;
                virtual void Draw() override;
                virtual BOOL Collision() override;
        }
*/