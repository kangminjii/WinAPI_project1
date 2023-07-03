// WinAPI_project1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
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
void OutFromFile(TCHAR filename[], HWND hwnd);

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

    //메뉴 클릭시 도형 그리기
    enum {CIRCLE, RECTANGLE, STAR, NONE};
    static int selectMenu = NONE;
  
    //채팅창
    static TCHAR str[10][128];
    static TCHAR first[128];
    static int count, yPos, line;
    static SIZE size;

    //마우스 위치
    static POINT ptMousePos;

    switch (message)
    {
    case WM_CREATE: // 초기화 값 세팅
        count = 0;
        yPos = 200;
        line = 0;
        CreateCaret(hWnd, NULL, 5, 15);
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
        case ID_DRAW_CIRCLE:
            // : 원 그리기
        {
            int temp = selectMenu;
            int ans = MessageBox(hWnd, _T("원 그릴래?"), _T("도형 선택"), MB_YESNOCANCEL);
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
            // : 사각형 그리기
            selectMenu = RECTANGLE;
            InvalidateRgn(hWnd, NULL, TRUE);
            break;

        case ID_DRAW_STAR:
            // : 별 그리기
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
                _stprintf(str, _T("%s 파일을 열겠습니까?"), ofn.lpstrFile);
                MessageBox(hWnd, str, _T("파일 선택"), MB_OK);
                OutFromFile(ofn.lpstrFile, hWnd);
            }
        }
            break;

        case ID_FILESAVE:
        {
            OPENFILENAME ifn;
            TCHAR lpstrFile[100] = _T("");
            TCHAR str[100] = _T("");

            // cout << 파일제목입력:
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
            break;
        case RECTANGLE:
            DrawRectangle(hdc, ptMousePos, 100, 100); // 직사각형
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
Q2. p.150 의 코드를 활용하여 "text.txt" 파일의 내용을 읽어 화면에 표시하는 코드를 작성하라.
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