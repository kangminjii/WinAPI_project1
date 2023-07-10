// WinAPI_project1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "WinAPI_project1.h"

#define MAX_LOADSTRING 100
#define timer_ID_1 11
#define timer_ID_2 12

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// >> : BITMAP
#pragma comment(lib, "msimg32.lib")

HBITMAP hBackImage;
BITMAP  bitBack;

HBITMAP hFrontImage;
BITMAP  bitFront;

HBITMAP hTransparentImage;
BITMAP  bitTransparent;
// << : BITMAP

// >> : ANI
HBITMAP hAniImage;
BITMAP bitAni;
const int SPRITE_SIZE_X = 57;
const int SPRITE_SIZE_Y = 52;

int RUN_FRAME_MAX = 0;
int RUN_FRAME_MIN = 0;
int curframe = RUN_FRAME_MIN;

int SPRITE_FRAME_COUNT_X = 0;
int SPRITE_FRAME_COUNT_Y = 0;
// << : ANI

// >> : Text
RECT rectView;
// << : Text

// >> : FUNC
void CreateBitmap();
void DrawBitmap(HWND hWnd, HDC hdc);
void DeleteBitmap();
void UpdateFrame(HWND hWnd);
void DrawRectText(HDC hdc);
VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

void Update();
void Render();
// << : FUNC

// >> : Double Buffering
HBITMAP hDoubleBufferImage;
void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);
// << : Double Buffering


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
    /*while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }*/

    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            //Update(); // 타이머가 하는 역할을 정교화시켜, 초당 프레임을 높인다
            //Render();
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
        300, 100, 1000, 1000, nullptr, nullptr, hInstance, nullptr);

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


    switch (message)
    {
    case WM_SIZE: // 창 크기를 변경할때마다 호출됨
        GetClientRect(hWnd, &rectView);
        break;
    case WM_CREATE: // 초기화 값 세팅
        ptCurPos.x = 0;
        ptCurPos.y = 0;
        GetClientRect(hWnd, &rectView);
        CreateBitmap();
        SetTimer(hWnd, timer_ID_2, 30, AniProc);
        break;
    case WM_TIMER: // 타이머 이벤트, 타이머는 일이 바쁘지 않을때만 잘 작동됨
    {
        if (wParam == timer_ID_1)
        {
            ptCurPos.x += 20;
            InvalidateRect(hWnd, NULL, TRUE);
        }
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
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);

       // DrawBitmap(hWnd, hdc);
        DrawBitmapDoubleBuffering(hWnd, hdc);
        DrawRectText(hdc); // 이미지 이후에 텍스트가 출력되도록

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        KillTimer(hWnd, timer_ID_1);
        DeleteBitmap();
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

void CreateBitmap()
{

    // >> : 수지
    {
        hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/수지.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hBackImage == NULL) // 이미지가 출력되지 않을 때
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("이미지 로드 에러1"), _T("에러"), MB_OK);
            return;
        }

        GetObject(hBackImage, sizeof(BITMAP), &bitBack);
    }

    // >> : 시공
    {
        hTransparentImage = (HBITMAP)LoadImage(NULL, TEXT("images/sigong.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hTransparentImage == NULL) // 이미지가 출력되지 않을 때
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("이미지 로드 에러2"), _T("에러"), MB_OK);
            return;
        }

        GetObject(hTransparentImage, sizeof(BITMAP), &bitTransparent);
    }

    // >> : zero_run
    {
        hAniImage = (HBITMAP)LoadImage(NULL, TEXT("images/zero_run.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hAniImage == NULL) // 이미지가 출력되지 않을 때
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("이미지 로드 에러3"), _T("에러"), MB_OK);
            return;
        }

        GetObject(hAniImage, sizeof(BITMAP), &bitAni);

        // :
        RUN_FRAME_MAX = bitAni.bmWidth / SPRITE_SIZE_X - 1;
        RUN_FRAME_MIN = 2;
        curframe = RUN_FRAME_MIN;

        SPRITE_FRAME_COUNT_X = bitAni.bmWidth / SPRITE_SIZE_X;
        SPRITE_FRAME_COUNT_Y = bitAni.bmHeight / SPRITE_SIZE_Y;
    }

    // >> : background
    {
        hFrontImage = (HBITMAP)LoadImage(NULL, TEXT("images/Background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hFrontImage == NULL) // 이미지가 출력되지 않을 때
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("이미지 로드 에러4"), _T("에러"), MB_OK);
            return;
        }

        GetObject(hFrontImage, sizeof(BITMAP), &bitFront);
    }
}

void DrawBitmap(HWND hWnd, HDC hdc)
{
    HDC hMemDC;
    HBITMAP hOldBitmap;
    int bx, by;

    // >> : 수지
    {
        hMemDC = CreateCompatibleDC(hdc); // 같은 포맷
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);
        bx = bitBack.bmWidth; // 전체 너비
        by = bitBack.bmHeight; // 전체 높이

        BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY); // 그림 그리기

        //SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
    }

    // >> : 시공
    {
        hMemDC = CreateCompatibleDC(hdc); // 같은 포맷
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hTransparentImage);
        bx = bitTransparent.bmWidth; // 전체 너비
        by = bitTransparent.bmHeight; // 전체 높이

        //BitBlt(hdc, 100, 150, bx, by, hMemDC, 0, 0, SRCCOPY); // 그림 그리기
        TransparentBlt(hdc, 150, 150, bx * 2, by * 2, hMemDC, 0, 0, bx, by, RGB(255, 0, 255)); // 배경의 분홍색만 사라지게 함

        //SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
    }

    // >> : zero_run
    {
        hMemDC = CreateCompatibleDC(hdc); // 같은 포맷
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        bx = bitAni.bmWidth / SPRITE_FRAME_COUNT_X; // 전체 너비
        by = bitAni.bmHeight / SPRITE_FRAME_COUNT_Y; // 전체 높이

        int xStart = curframe * bx;
        int yStart = 0;
        TransparentBlt(hdc, 150, 250, bx, by, hMemDC, xStart, yStart, bx, by, RGB(255, 0, 255)); // 배경의 분홍색만 사라지게 함

        SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
    }
}

void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
    HDC hMemDC;
    HBITMAP hOldBitmap;
    int bx, by;

    HDC hMemDC2;
    HBITMAP hOldBitmap2;

    hMemDC = CreateCompatibleDC(hdc);
    if (hDoubleBufferImage == NULL)
    {
        hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
    }
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage); //  기본은 검정색


    // >> : 수지
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage);
        bx = bitBack.bmWidth; // 전체 너비
        by = bitBack.bmHeight; // 전체 높이

        BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY); // 그림 그리기

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }

    // >> : 시공
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hTransparentImage);
        bx = bitTransparent.bmWidth; // 전체 너비
        by = bitTransparent.bmHeight; // 전체 높이

        TransparentBlt(hMemDC, 150, 150, bx * 2, by * 2, hMemDC2, 0, 0, bx, by, RGB(255, 0, 255)); // 배경의 분홍색만 사라지게 함

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }

    // >> : zero_run
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hAniImage);
        bx = bitAni.bmWidth / SPRITE_FRAME_COUNT_X; // 전체 너비
        by = bitAni.bmHeight / SPRITE_FRAME_COUNT_Y; // 전체 높이

        int xStart = curframe * bx;
        int yStart = 0;

        static int xPos = 0;
        TransparentBlt(hMemDC, 150 + xPos, 250, bx, by, hMemDC2, xStart, yStart, bx, by, RGB(255, 0, 255)); // 배경의 분홍색만 사라지게 함
        StretchBlt(hMemDC, 150 + xPos, 300, -bx, by, hMemDC2, xStart, yStart, bx, by, SRCCOPY);

        xPos++;
        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }

    // << : hMemeDC 에 그려주기

    // >> : front
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hFrontImage);
        bx = bitFront.bmWidth; // 전체 너비
        by = bitFront.bmHeight; // 전체 높이

        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hMemDC2, hBrush);

        Ellipse(hMemDC2, 250, 100, 750, 500);

        SelectObject(hMemDC2 ,oldBrush);
        DeleteObject(hBrush);

        TransparentBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, bx, by, RGB(255, 0, 255));

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }


    // >> : hdc에 그려주기
    //BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, SRCCOPY);
    TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, rectView.right, rectView.bottom, RGB(255, 0, 255));

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}

void DeleteBitmap()
{
    DeleteObject(hAniImage);
    DeleteObject(hBackImage);
    DeleteObject(hTransparentImage);
}

void UpdateFrame(HWND hWnd)
{
    curframe++;
    if (curframe > RUN_FRAME_MAX)
        curframe = RUN_FRAME_MIN;

    InvalidateRect(hWnd, NULL, FALSE);
}

static int yPos = 0;
void DrawRectText(HDC hdc)
{
    TCHAR strTest[] = _T("이미지 출력");
    TextOut(hdc, 10, yPos, strTest, _tcslen(strTest));
}

VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    UpdateFrame(hWnd);
    yPos += 5;
    if (yPos > rectView.bottom) yPos = 0;
}

void Update()
{
    // : wm_keydown, wm_keyup을 사용하면 반응이 즉각적이지 않음
    if (GetKeyState('A') & 0x8000)
    {

    }

    if (GetKeyState('D') & 0x8000)
    {

    }

    if (GetAsyncKeyState('W') & 0x8000) // 두개의 차이점 찾아보기
    {

    }

    if (GetAsyncKeyState('S') & 0x8000) 
    {

    }
}

void Render()
{
}


/*
Q1. 다음 세가지 게임 중 하나를 선택해서 프로그램을 작성하라.

    1. 스네이크 게임 p.125 참고

    2. 벽돌깨기 게임

    3. 디펜스 게임

    게임 타이틀 출력 -> Press Any Key
        아이디 입력

    본 게임 진행

    게임 결과 출력 -> 점수, 랭킹
        파일 입/출력
*/