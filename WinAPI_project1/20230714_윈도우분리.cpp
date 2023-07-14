// WinAPI_project1.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "WinAPI_project1.h"
#include <CommCtrl.h>

#define MAX_LOADSTRING 100

HWND hModalessDlg; // 0713
BOOL CALLBACK Dialog_Test1_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

void MakeColumn(HWND hDlg);
void InsertData(HWND hDlg);


// 0714
HWND ChildWnd[2];
LRESULT CALLBACK    ChildWndProc1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildWndProc2(HWND, UINT, WPARAM, LPARAM);


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

// >> : FUNC
void CreateBitmap();
void DrawBitmap(HWND hWnd, HDC hdc);
void DeleteBitmap();
void UpdateFrame(HWND hWnd);
void DrawRectText(HDC hdc);
VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
// << : FUNC

// >> : Double Buffering
HBITMAP hDoubleBufferImage;
void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);
// << : Double Buffering

RECT rectView;


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
            //Update(); // Ÿ�̸Ӱ� �ϴ� ������ ����ȭ����, �ʴ� �������� ���δ�
            //Render();
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
    
    // 0714
    RegisterClassExW(&wcex);

    // split window 1
    wcex.lpfnWndProc = ChildWndProc1;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = _T("Child Window Class 1");
    RegisterClassExW(&wcex); // ������ ���
    // split window 2
    wcex.lpfnWndProc = ChildWndProc2;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = _T("Child Window Class 2");
    RegisterClassExW(&wcex); // ������ ���

    return NULL;
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

    switch (message)
    {
    case WM_CREATE: // �ʱ�ȭ �� ����
        GetClientRect(hWnd, &rectView);
        CreateBitmap();

        // >> : split window
        {
            ChildWnd[0] = CreateWindowEx(WS_EX_CLIENTEDGE, _T("Child Window Class 1"), NULL, WS_CHILD | WS_VISIBLE, 
                0, 0, rectView.right, rectView.bottom/2 -1, hWnd, NULL, hInst, NULL);
            ChildWnd[1] = CreateWindowEx(WS_EX_CLIENTEDGE, _T("Child Window Class 2"), NULL, WS_CHILD | WS_VISIBLE,
                0, rectView.bottom / 2 + 1, rectView.right, rectView.bottom / 2 - 1, hWnd, NULL, hInst, NULL);
        }

        //SetTimer(hWnd, 11, 30, AniProc);
        break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // �޴� ������ ���� �м��մϴ�:
        switch (wmId)
        {
        case ID_COPY_DIALOG:
            // ���̾�α� �ڽ��� ���� �޴�
            //DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog_Test1_Proc);

            // 0713
            hModalessDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog_Test1_Proc);
            ShowWindow(hModalessDlg, SW_SHOW);
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

    /*case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);

        DrawBitmapDoubleBuffering(hWnd, hdc);

        EndPaint(hWnd, &ps);
    }
    break;*/
    case WM_DESTROY:
        //KillTimer(hWnd, 11);
        DeleteBitmap();
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

// ���̾�α�1
BOOL CALLBACK Dialog_Test1_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    // 0710
    static int Check[3], Radio;
    TCHAR hobby[][30] = { _T("����"), _T("���ǰ���"), _T("����") };
    TCHAR sex[][30] = { _T("����"), _T("����") };
    TCHAR output[200];

    // 0712
    static HWND hCombo;
    static int selection;
    TCHAR name[20];

    static HWND hList;
    static int selectionList;



    switch (iMsg)
    {
    case WM_INITDIALOG:
    {
        // 0710
        HWND hBtn = GetDlgItem(hDlg, IDC_PAUSE);
        EnableWindow(hBtn, FALSE);

        CheckRadioButton(hDlg, IDC_RADIO_FEMALE, IDC_RADIO_MALE, IDC_RADIO_FEMALE); // ���� ������ �׷�ȭ, ���� ��ư�� default�� üũ

        // 0712
        hCombo = GetDlgItem(hDlg, IDC_COMBO_LIST);
        hList = GetDlgItem(hDlg, IDC_LIST_NAME);

        // 0713
        MakeColumn(hDlg);

    }
    return 1;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
            // 0713 
        case IDC_BUTTON_INSERT_MEMBER:
            InsertData(hDlg);
            break;

            // 0712 �޺� ��ư, ȸ�� �̸� �� ���
        case IDC_BUTTON_INSERT:
            GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 20);
            if (_tcscmp(name, _T(""))) // ������ �ƴ� ���ڰ� ���� ��
            {
                SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)name);
                SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)name);
            }
            break;
        case IDC_BUTTON_DELETE:
            SendMessage(hCombo, CB_DELETESTRING, selection, 0);
            break;
        case IDC_COMBO_LIST:
            if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                selection = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
            }
            break;
        case IDC_BUTTON_DELETE2:
            SendMessage(hList, LB_DELETESTRING, selectionList, 0);
            break;
        case IDC_LIST_NAME:
            if (HIWORD(wParam) == LBN_SELCHANGE)
            {
                selectionList = SendMessage(hList, LB_GETCURSEL, 0, 0);
            }
            break;

            // üũ ��ư
        case IDC_CHECK_READING:
            Check[0] = 1 - Check[0];
            break;
        case IDC_CHECK_MUSIC:
            Check[1] = 1 - Check[1];
            break;
        case IDC_CHECK_GAME:
            Check[2] = 1 - Check[2];
            break;

            // ���� ��ư
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

            // �ؽ�Ʈ �����ϱ�, �����ϱ�
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

            // ����, ����, ���
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

        // Ȯ��, ��� ��ư
        case IDOK:
            //EndDialog(hDlg, 0);
            DestroyWindow(hDlg);
            hDlg = NULL;
            break;
        case IDC_CANCEL:
            //EndDialog(hDlg, 0);
            DestroyWindow(hDlg);
            hDlg = NULL;
            break;
        }
        break;
    }
    return 0;
}

void MakeColumn(HWND hDlg)
{
    LPCTSTR name[2] = { _T("�̸�"), _T("��ȭ��ȣ") };
    LVCOLUMN lvCol = { 0, };
    HWND hList;

    hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
    lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvCol.fmt = LVCFMT_LEFT;

    for (int i = 0; i < 2; i++)
    {
        lvCol.cx = 90;
        lvCol.iSubItem = i;
        lvCol.pszText = (LPWSTR)name[i];
        SendMessage(hList, LVM_INSERTCOLUMN, (WPARAM)i, (LPARAM)&lvCol);
    }
}

void InsertData(HWND hDlg)
{
    LVITEM item;
    HWND hList;
    LPCTSTR name[20] = { _T("��ö��"), _T("�迵��") };
    LPCTSTR phone[20] = { _T("010-1111-3333"), _T("010-2222-4444") };

    hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);

    for (int i = 0; i < 2; i++)
    {
        item.mask = LVIF_TEXT;
        item.iItem = i;
        item.iSubItem = 0;
        item.pszText = (LPWSTR)name[i];
        ListView_InsertItem(hList, &item);
        ListView_SetItemText(hList, i, 1, (LPWSTR)phone[i]);
    }
}

void CreateBitmap()
{

    // >> : ����
    {
        hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/����.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hBackImage == NULL) // �̹����� ��µ��� ���� ��
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("�̹��� �ε� ����1"), _T("����"), MB_OK);
            return;
        }

        GetObject(hBackImage, sizeof(BITMAP), &bitBack);
    }

    // >> : �ð�
    {
        hTransparentImage = (HBITMAP)LoadImage(NULL, TEXT("images/sigong.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hTransparentImage == NULL) // �̹����� ��µ��� ���� ��
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("�̹��� �ε� ����2"), _T("����"), MB_OK);
            return;
        }

        GetObject(hTransparentImage, sizeof(BITMAP), &bitTransparent);
    }

    // >> : zero_run
    {
        hAniImage = (HBITMAP)LoadImage(NULL, TEXT("images/zero_run.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hAniImage == NULL) // �̹����� ��µ��� ���� ��
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("�̹��� �ε� ����3"), _T("����"), MB_OK);
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

        if (hFrontImage == NULL) // �̹����� ��µ��� ���� ��
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("�̹��� �ε� ����4"), _T("����"), MB_OK);
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

    // >> : ����
    {
        hMemDC = CreateCompatibleDC(hdc); // ���� ����
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);
        bx = bitBack.bmWidth; // ��ü �ʺ�
        by = bitBack.bmHeight; // ��ü ����

        BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY); // �׸� �׸���

        //SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
    }

    // >> : �ð�
    {
        hMemDC = CreateCompatibleDC(hdc); // ���� ����
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hTransparentImage);
        bx = bitTransparent.bmWidth; // ��ü �ʺ�
        by = bitTransparent.bmHeight; // ��ü ����

        //BitBlt(hdc, 100, 150, bx, by, hMemDC, 0, 0, SRCCOPY); // �׸� �׸���
        TransparentBlt(hdc, 150, 150, bx * 2, by * 2, hMemDC, 0, 0, bx, by, RGB(255, 0, 255)); // ����� ��ȫ���� ������� ��

        //SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
    }

    // >> : zero_run
    {
        hMemDC = CreateCompatibleDC(hdc); // ���� ����
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        bx = bitAni.bmWidth / SPRITE_FRAME_COUNT_X; // ��ü �ʺ�
        by = bitAni.bmHeight / SPRITE_FRAME_COUNT_Y; // ��ü ����

        int xStart = curframe * bx;
        int yStart = 0;
        TransparentBlt(hdc, 150, 250, bx, by, hMemDC, xStart, yStart, bx, by, RGB(255, 0, 255)); // ����� ��ȫ���� ������� ��

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
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage); //  �⺻�� ������


    // >> : ����
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // ���� ����
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage);
        bx = bitBack.bmWidth; // ��ü �ʺ�
        by = bitBack.bmHeight; // ��ü ����

        BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY); // �׸� �׸���

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }

    // >> : �ð�
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // ���� ����
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hTransparentImage);
        bx = bitTransparent.bmWidth; // ��ü �ʺ�
        by = bitTransparent.bmHeight; // ��ü ����

        TransparentBlt(hMemDC, 150, 150, bx * 2, by * 2, hMemDC2, 0, 0, bx, by, RGB(255, 0, 255)); // ����� ��ȫ���� ������� ��

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }

    // >> : zero_run
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // ���� ����
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hAniImage);
        bx = bitAni.bmWidth / SPRITE_FRAME_COUNT_X; // ��ü �ʺ�
        by = bitAni.bmHeight / SPRITE_FRAME_COUNT_Y; // ��ü ����

        int xStart = curframe * bx;
        int yStart = 0;

        static int xPos = 0;
        TransparentBlt(hMemDC, 150 + xPos, 250, bx, by, hMemDC2, xStart, yStart, bx, by, RGB(255, 0, 255)); // ����� ��ȫ���� ������� ��
        StretchBlt(hMemDC, 150 + xPos, 300, -bx, by, hMemDC2, xStart, yStart, bx, by, SRCCOPY);

        xPos++;
        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }

    // << : hMemeDC �� �׷��ֱ�

    // >> : front
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // ���� ����
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hFrontImage);
        bx = bitFront.bmWidth; // ��ü �ʺ�
        by = bitFront.bmHeight; // ��ü ����

        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hMemDC2, hBrush);

        Ellipse(hMemDC2, 250, 100, 750, 500);

        SelectObject(hMemDC2, oldBrush);
        DeleteObject(hBrush);

        TransparentBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, bx, by, RGB(255, 0, 255));

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }


    // >> : hdc�� �׷��ֱ�
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
    TCHAR strTest[] = _T("�̹��� ���");
    TextOut(hdc, 10, yPos, strTest, _tcslen(strTest));
}

VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    UpdateFrame(hWnd);
    yPos += 5;
    if (yPos > rectView.bottom) yPos = 0;
}

#define IDC_CHILD1_BTN 2000

LRESULT CALLBACK ChildWndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HWND hBtn;
    static bool bToggle = false;
   
    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 11, 30, AniProc);
        
        hBtn = CreateWindow(_T("button"), _T("OK"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            200, 10, 100, 30, hWnd, (HMENU)IDC_CHILD1_BTN, hInst, NULL);

        break;
    case WM_PAINT:
    {
        HDC hdc;
        PAINTSTRUCT ps;

        hdc = BeginPaint(hWnd, &ps);

        DrawBitmapDoubleBuffering(hWnd, hdc);
        if (bToggle)
            TextOut(hdc, 200, 50, _T("Button Clicked"), 14);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_CHILD1_BTN:
            bToggle = !bToggle;
            break;
        }
        break;
    case WM_DESTROY:
        KillTimer(hWnd, 11);
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK ChildWndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static POINT ptMouse;

    switch (message)
    {
    case WM_CREATE:
        break;
    case WM_COMMAND:
        break;
    case WM_MOUSEMOVE:
        GetCursorPos(&ptMouse);
        InvalidateRect(hWnd, NULL, FALSE);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;

        HDC hdc = BeginPaint(hWnd, &ps);
        TCHAR str[128];
        wsprintf(str, TEXT("WORLD POSITION : (%04d, %04d)"), ptMouse.x, ptMouse.y);
        TextOut(hdc, 10, 30, str, lstrlen(str));

        ScreenToClient(hWnd, &ptMouse);

        wsprintf(str, TEXT("LOCAL POSITION : (%04d, %04d)"), ptMouse.x, ptMouse.y);
        TextOut(hdc, 10, 50, str, lstrlen(str));

        EndPaint(hWnd, &ps);
    }
        break;
    case WM_DESTROY:
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
