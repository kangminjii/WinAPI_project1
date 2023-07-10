// WinAPI_project1.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "WinAPI_project1.h"

// >> : GDI+
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;

ULONG_PTR g_GdiToken;

void Gdi_Init();
void Gdi_Draw(HDC hdc);
void Gdi_End();

// << :

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

RECT rectView;

#define MAX_LOADSTRING 100


// : ��ȭ����
BOOL CALLBACK Dialog_Test1_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);


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

    Gdi_Init();
    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
    if (!InitInstance(hInstance, nCmdShow))
    {
        Gdi_End();
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIPROJECT1));

    MSG msg;

    
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    //while (true)
    //{
    //    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    //    {
    //        if (msg.message == WM_QUIT)
    //        {
    //            break;
    //        }
    //        else
    //        {
    //            TranslateMessage(&msg);
    //            DispatchMessage(&msg);
    //        }
    //    }
    //    else
    //    {
    //        //Update(); // Ÿ�̸Ӱ� �ϴ� ������ ����ȭ����, �ʴ� �������� ���δ�
    //        //Render();
    //    }
    //}
   
    Gdi_End();

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
    wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255,255,255));
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

    enum { CIRCLE, RECTANGLE, STAR, NONE };
    static int selectedMenu = NONE;

    switch (message)
    {
    case WM_CREATE: // �ʱ�ȭ �� ����
        GetClientRect(hWnd, &rectView);
        SetTimer(hWnd, 1111, 30, NULL);

        break;
    case WM_KEYDOWN: // ������ �߻�
    {
    }
    break;
   
    case WM_TIMER: // Ÿ�̸� �̺�Ʈ, Ÿ�̸Ӵ� ���� �ٻ��� �������� �� �۵���
    {
        InvalidateRect(hWnd, NULL, FALSE);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // �޴� ������ ���� �м��մϴ�:
        switch (wmId)
        {
        case ID_COPY_DIALOG:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog_Test1_Proc);

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
    
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);

        Gdi_Draw(hdc);

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

BOOL CALLBACK Dialog_Test1_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static int Check[3], Radio;
    TCHAR hobby[][30] = { _T("����"), _T("���ǰ���"), _T("����") };
    TCHAR sex[][30] = { _T("����"), _T("����") };
    TCHAR output[200];

    switch (iMsg)
    {
    case WM_INITDIALOG:
    {
        HWND hBtn = GetDlgItem(hDlg, IDC_PAUSE);
        EnableWindow(hBtn, FALSE);

        CheckRadioButton(hDlg, IDC_RADIO_FEMALE, IDC_RADIO_MALE, IDC_RADIO_FEMALE); // ���� ������ �׷�ȭ, ���� ��ư�� default�� üũ

    }
    return 1;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_CHECK_READING:
            Check[0] = 1 - Check[0];
            break;
        case IDC_CHECK_MUSIC:
            Check[1] = 1 - Check[1];
            break;
        case IDC_CHECK_GAME:
            Check[2] = 1 - Check[2];
            break;

        case IDC_RADIO_FEMALE:
            Radio = 0;
            break;
        case IDC_RADIO_MALE:
            Radio = 1;
            break;
        case IDC_BUTTON_OUTPUT:
            _stprintf_s(output,
                _T("������ ��̴� %s %s %s �Դϴ�.\r\n")
                _T("������ ������ %s �Դϴ�."),
                Check[0] ? hobby[0] : _T(""),
                Check[1] ? hobby[1] : _T(""),
                Check[2] ? hobby[2] : _T(""),
                sex[Radio]);
            SetDlgItemText(hDlg, IDC_EDIT_OUTPUT, output);
            break;



         // �����ϱ�, �����ϱ�
        case IDC_BUTTON_COPY:
        {
            TCHAR str[100];
            GetDlgItemText(hDlg, IDC_EDIT_INPUT, str, 100);
            SetDlgItemText(hDlg, IDC_EDIT_COPY, str);
        }
            break;
        case IDC_BUTTON_CLEAR:
            SetDlgItemText(hDlg, IDC_EDIT_INPUT, _T(""));
            SetDlgItemText(hDlg, IDC_EDIT_COPY, _T(""));
            break;

            

        case IDC_START:
        {
            HDC hdc = GetDC(hDlg);
            SetDlgItemText(hDlg, IDC_TEXT, _T("Start"));
            ReleaseDC(hDlg, hdc);

            HWND hBtn = GetDlgItem(hDlg, IDC_START);
            EnableWindow(hBtn, FALSE);

            hBtn = GetDlgItem(hDlg, IDC_PAUSE);
            EnableWindow(hBtn, TRUE);
        }
        break;
        case IDC_PAUSE:
        {
            HDC hdc = GetDC(hDlg);
            SetDlgItemText(hDlg, IDC_TEXT, _T("Pause"));
            ReleaseDC(hDlg, hdc);

            HWND hBtn = GetDlgItem(hDlg, IDC_PAUSE);
            EnableWindow(hBtn, FALSE);

            hBtn = GetDlgItem(hDlg, IDC_START);
            EnableWindow(hBtn, TRUE);
        }
        break;
        case IDC_BUTTON_PRINT:
        {
            HDC hdc = GetDC(hDlg);
            TextOut(hdc, 0, 0, _T("Print"), 5);

            SetDlgItemText(hDlg, IDC_TEXT, _T("Print"));

            ReleaseDC(hDlg, hdc);
        }
        break;
        case IDOK:
            EndDialog(hDlg, 0);
            break;
        case IDC_CANCEL:
            EndDialog(hDlg, 0);
            break;
        }
        break;
    }
    return 0;
}

void Gdi_Init()
{
    GdiplusStartupInput gpsi;
    GdiplusStartup(&g_GdiToken, &gpsi, NULL);
}

void Gdi_Draw(HDC hdc)
{
    Graphics graphics(hdc);

    // : text
    SolidBrush brush(Color(255, 255, 0, 0));
    FontFamily fontFamily(L"Times New Roman");
    Font font(&fontFamily, 24, FontStyleRegular, UnitPixel);
    PointF pointF(10.0f, 20.0f);
    graphics.DrawString(L"Hello GDI+!!", -1, &font, pointF, &brush);

    // : line
    Pen pen(Color(128, 255,0,0));
    graphics.DrawLine(&pen, 0, 0, 200, 100);

    // : image
    Image img((WCHAR*)L"images/gom2.png");
    int w = img.GetWidth();
    int h = img.GetHeight();
    graphics.DrawImage(&img, 300, 100, w, h);

    // : ani create
    hAniImage = (HBITMAP)LoadImage(NULL, TEXT("images/zero_run.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (hAniImage == NULL) // �̹����� ��µ��� ���� ��
    {
        DWORD dwError = GetLastError();
        MessageBox(NULL, _T("�̹��� �ε� ����3"), _T("����"), MB_OK);
        return;
    }
    GetObject(hAniImage, sizeof(BITMAP), &bitAni);
    RUN_FRAME_MAX = bitAni.bmWidth / SPRITE_SIZE_X - 1;
    RUN_FRAME_MIN = 2;
    curframe = RUN_FRAME_MIN;

    SPRITE_FRAME_COUNT_X = bitAni.bmWidth / SPRITE_SIZE_X;
    SPRITE_FRAME_COUNT_Y = bitAni.bmHeight / SPRITE_SIZE_Y;

    // : ani
    Image img2((WCHAR*)L"images/zero_run.png");
    w = img2.GetWidth() / SPRITE_FRAME_COUNT_X;
    h = img2.GetHeight() / SPRITE_FRAME_COUNT_Y;
    int xStart = curframe * w;
    int yStart = 0;

    ImageAttributes imgAttr0;
    imgAttr0.SetColorKey(Color(245, 0, 245), Color(255,0,255));
    graphics.DrawImage(&img2, Rect(400, 100, w, h), xStart, yStart, w, h, UnitPixel, &imgAttr0);

    // >> : alpha rect
    brush.SetColor(Color(128, 255, 0, 0));
    graphics.FillRectangle(&brush, 100, 100, 200, 300);

    // >> : rotation
    Image* pImg = nullptr;
    pImg = Image::FromFile((WCHAR*)L"images/gom2.png");
    int xPos = 400;
    int yPos = 200;
    if (pImg)
    {
        w = pImg->GetWidth();
        h = pImg->GetHeight();

        Gdiplus::Matrix mat;
        static int rot = 0;
        mat.RotateAt((rot % 360), Gdiplus::PointF(xPos + (float)(w / 2), yPos + (float)(h / 2)));

        graphics.SetTransform(&mat);
        graphics.DrawImage(pImg, xPos, yPos, w, h);
        rot += 10;

        mat.Reset();
        graphics.SetTransform(&mat);
    }

    ImageAttributes imgAttr;
    imgAttr.SetColorKey(Color(240, 0, 240), Color(255, 10, 255));
    xPos = 500;
    graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPoint, &imgAttr);
    graphics.DrawImage(pImg, xPos + 50, yPos, w, h);

    if (pImg)
    {
        REAL transparency = 0.5f;
        ColorMatrix colorMatrix =
        {
            1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, transparency, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f
        };
        imgAttr.SetColorMatrix(&colorMatrix);
        xPos = 600;
        graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPoint, &imgAttr);


        ColorMatrix grayMatrix =
        {
            0.3f, 0.3f, 0.3f, 0.0f, 0.0f,
            0.6f, 0.6f, 0.6f, 0.0f, 0.0f,
            0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f
        };
        imgAttr.SetColorMatrix(&grayMatrix);
        xPos = 700;
        graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPoint, &imgAttr);


        xPos = 100;
        pImg->RotateFlip(RotateNoneFlipX);
        graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPoint, &imgAttr);


        delete pImg;
    }
    DeleteObject(hAniImage);
}

static int yPos = 0;
VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    curframe++;
    if (curframe > RUN_FRAME_MAX)
        curframe = RUN_FRAME_MIN;

    InvalidateRect(hWnd, NULL, FALSE);

    yPos += 5;
    if (yPos > rectView.bottom) yPos = 0;
}

void Gdi_End()
{
    GdiplusShutdown(g_GdiToken);
}