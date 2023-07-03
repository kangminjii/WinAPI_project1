//// WinAPI_project1.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
////
//#define _CRT_SECURE_NO_WARNINGS
//#include "framework.h"
//#include "WinAPI_project1.h"
//#include <cmath>
//#include "Circle.h"
//#include "Square.h"
//#include <time.h>
//
//#define MAX_LOADSTRING 100
//
//// ���� ����:
//HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
//WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
//WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
//
//// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//
//
//int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//    _In_opt_ HINSTANCE hPrevInstance,
//    _In_ LPWSTR    lpCmdLine,
//    _In_ int       nCmdShow)
//{
//    UNREFERENCED_PARAMETER(hPrevInstance);
//    UNREFERENCED_PARAMETER(lpCmdLine);
//
//    // TODO: ���⿡ �ڵ带 �Է��մϴ�.
//
//    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
//    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//    LoadStringW(hInstance, IDC_WINAPIPROJECT1, szWindowClass, MAX_LOADSTRING);
//    MyRegisterClass(hInstance);
//
//    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
//    if (!InitInstance(hInstance, nCmdShow))
//    {
//        return FALSE;
//    }
//
//    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIPROJECT1));
//
//    MSG msg;
//
//    // �⺻ �޽��� �����Դϴ�:
//    while (GetMessage(&msg, nullptr, 0, 0))
//    {
//        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//        {
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//    }
//
//    return (int)msg.wParam;
//}
//
//
////
////  �Լ�: MyRegisterClass()
////
////  �뵵: â Ŭ������ ����մϴ�.
////
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//    WNDCLASSEXW wcex;
//
//    wcex.cbSize = sizeof(WNDCLASSEX);
//
//    wcex.style = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc = WndProc;
//    wcex.cbClsExtra = 0;
//    wcex.cbWndExtra = 0;
//    wcex.hInstance = hInstance;
//    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIPROJECT1));
//    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
//    wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(220, 255, 100));
//    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPIPROJECT1);
//    wcex.lpszClassName = szWindowClass;
//    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//    return RegisterClassExW(&wcex);
//}
//
////
////   �Լ�: InitInstance(HINSTANCE, int)
////
////   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
////
////   �ּ�:
////
////        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
////        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
////
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.
//
//    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//        300, 300, 800, 800, nullptr, nullptr, hInstance, nullptr);
//
//    if (!hWnd)
//    {
//        return FALSE;
//    }
//
//    ShowWindow(hWnd, nCmdShow);
//    UpdateWindow(hWnd);
//
//    return TRUE;
//}
//
////
////  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  �뵵: �� â�� �޽����� ó���մϴ�.
////
////  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
////  WM_PAINT    - �� â�� �׸��ϴ�.
////  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
////
////
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    PAINTSTRUCT ps;
//    HDC hdc;
//    srand(time(NULL));
//
//    static Circle c[100];
//    static Square s[100];
//    static RECT rectView;
//    static int count;
//    static int random = rand() % 2;
//
//    switch (message)
//    {
//    case WM_CREATE: // �ʱ�ȭ �� ����
//    {
//        count = 0;
//        GetClientRect(hWnd, &rectView); // ������â ũ�Ⱚ�� rectView�� ������
//        SetTimer(hWnd, 1, 100, NULL);
//    }
//    break;
//
//    case WM_TIMER: // Ÿ�̸� �̺�Ʈ, Ÿ�̸Ӵ� ���� �ٻ��� �������� �� �۵���
//    {
//        for (int i = 0; i < count; i++)
//        {
//            c[i].Update(rectView);
//            s[i].Update(rectView);
//        }
//
//        InvalidateRect(hWnd, NULL, TRUE);
//    }
//    break;
//
//    case WM_KEYDOWN: // ������ �߻�
//    {
//    }
//    break;
//
//    case WM_KEYUP: // ������ ���� �߻�
//    {
//    }
//    break;
//
//    case WM_COMMAND:
//    {
//        int wmId = LOWORD(wParam);
//        // �޴� ������ ���� �м��մϴ�:
//        switch (wmId)
//        {
//        case IDM_ABOUT:
//            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//            break;
//        case IDM_EXIT:
//            DestroyWindow(hWnd);
//            break;
//        default:
//            return DefWindowProc(hWnd, message, wParam, lParam);
//        }
//    }
//    break;
//
//    case WM_CHAR:
//    {
//    }
//    break;
//
//    case WM_LBUTTONDOWN: // ���콺 Ŭ����
//    {
//        c[count++].SetPosition(LOWORD(lParam), HIWORD(lParam));
//        s[count++].SetPosition(LOWORD(lParam), HIWORD(lParam));
//
//        InvalidateRect(hWnd, NULL, TRUE);
//    }
//    break;
//
//    case WM_LBUTTONUP: // ���콺 Ŭ������ ����
//    {
//    }
//    break;
//
//    case WM_MOUSEMOVE:
//    {
//    }
//    break;
//
//    case WM_PAINT:
//    {
//        hdc = BeginPaint(hWnd, &ps);
//       
//        if (random == 0)
//        {
//            for (int i = 0; i < count; i++)
//                c[i].Draw(hdc);
//        }
//        else if (random == 1)
//        {
//            for (int i = 0; i < count; i++)
//                s[i].Draw(hdc);
//        }
//
//       
//        EndPaint(hWnd, &ps);
//    }
//    break;
//    case WM_DESTROY:
//        KillTimer(hWnd, 1);
//
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
//
//// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}
//
///*
//Q2.
//    1. Ŭ���̾�Ʈ ������ ���콺 Ŭ��, �� ��ġ�� ���� ����
//        �⺻���� �� ����
//        1.1 �������� �簢��, ��, ���� �����ǵ��� �Ѵ�.
//
//    2. ������ �������� �̵� / Ŭ���̾�Ʈ �ܰ����� �ݻ�
//    3. Ŭ������ ����
//        �簢��/���� ���� ������ �۵��ϵ��� �Ѵ�.
//
//    4. �ٸ� ������Ʈ���� ���� ����
//        ��� ���� 1�� �ݻ�, 2�� ��ü, 3�� �п��� Ű ����
//       4.1 �ݻ� - �ٸ� ������Ʈ�� �ε����� ƨ���
//       4.2 ��ü - �� ���迡 ���� �ٸ� ������Ʈ�� ������ ��ü�ؼ� Ŀ���� �ϱ�
//       4.3 �п� - �� ���迡 ���� �ٸ� ������Ʈ�� ������ �п��ؼ� �۾����� �ϱ�
//                �� > �� > �簢�� > ��
//
//    5. ���� ũ�� �̻�, �Ǵ� ���ϴ� ��������� �Ѵ�.
//
//    6. �� ������Ʈ�� ȸ�� ��Ų��.
//
//        CObject
//        {
//            protected :
//                ��ǥ
//                �̵� ���ǵ�
//                �̵� ����
//                Ÿ�� ( ��, ��, �簢�� )
//            public :
//                virtual void Update() = 0;
//                virtual void Draw() = 0; // �ڱ� �ڽ��� �׸��� �Լ�
//                virtual BOOL Collision() = 0;
//            // �� �� �Լ�
//        };
//
//        CCirlce : public CObject
//        {
//            private :
//                ������
//            public :
//                virtual void Update() override;
//                virtual void Draw() override;
//                virtual BOOL Collision() override;
//        }
//*/