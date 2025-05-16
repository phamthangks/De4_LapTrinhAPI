// De4.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "De4.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DE4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DE4));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DE4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDR_MENU1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, TEXT("Thang-221230998"), WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hdc;
    static POINT point, pt[4], p[10000];
    static HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
    static HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    static COLORREF colorNen = RGB(255, 255, 255), colorVien = RGB(0, 0, 0);
    static int Hinh, xLeft, yTop, xRight, yBotton, m = 60, s = 0, width, height, stylePen = PS_SOLID, styleBrush = -1;
    static TCHAR leftTime[20];
    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, 1000, NULL);
        break;
    case WM_SIZE:
        width = LOWORD(lParam);
        height = HIWORD(lParam);
        break;
    case WM_TIMER:
        if (m == 0 && s == 0)
        {
            KillTimer(hWnd, 1); // Dừng khi hết giờ
        }
        else
        {
            if (s == 0)
            {
                m--;
                s = 59;
            }
            else
            {
                s--;
            }
        }

        wsprintfW(leftTime, L"Time: %02d:%02d", m, s);
        hdc = GetDC(hWnd);
        SetTextColor(hdc, RGB(255, 0, 0));
        TextOut(hdc, width - 120, height - 20, leftTime, 20);
        ReleaseDC(hWnd, hdc);
        break;
    case WM_LBUTTONDOWN:
        xLeft = LOWORD(lParam);
        yTop = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:
        xRight = LOWORD(lParam);
        yBotton = HIWORD(lParam);

        hdc = GetDC(hWnd);
        hPen = CreatePen(stylePen, 1, colorVien);
        if (styleBrush == HS_HORIZONTAL || styleBrush == HS_VERTICAL || styleBrush == HS_DIAGCROSS)
            hBrush = CreateHatchBrush(styleBrush, colorNen);
        else
            hBrush = CreateSolidBrush(colorNen);

        SelectObject(hdc, hPen);
        SelectObject(hdc, hBrush);

        if (Hinh == ID_HINH_THOI)
        {
            pt[0].x = xRight - (xRight - xLeft) / 2;
            pt[0].y = yTop;
            pt[1].x = xRight;
            pt[1].y = yBotton - (yBotton - yTop) / 2;
            pt[2].x = xRight - (xRight - xLeft) / 2;;
            pt[2].y = yBotton;
            pt[3].x = xLeft;
            pt[3].y = yBotton - (yBotton - yTop) / 2;
            Polygon(hdc, pt, 4);
        }
        if (Hinh == ID_HINH_CN)
        {
            Rectangle(hdc, xLeft, yTop, xRight, yBotton);
            /*int side = min(abs(xRight - xLeft), abs(yBotton - yTop));
            Rectangle(hdc, xLeft, yTop, xLeft + side, yTop + side);*/
        }
        if (Hinh == ID_HINH_ELLIPSE)
        {
            Ellipse(hdc, xLeft, yTop, xRight, yBotton);
        }
        if (Hinh == ID_HINH_TAMGIAC)
        {
            pt[0].x = xRight - (xRight - xLeft) / 2;
            pt[0].y = yTop;
            pt[1].x = xRight;
            pt[1].y = yBotton;
            pt[2].x = xLeft;
            pt[2].y = yBotton;
            Polygon(hdc, pt, 3);
        }
        if (Hinh == ID_HINH_TGV)
        {
            pt[0].x = xLeft;
            pt[0].y = yTop;
            pt[1].x = xRight;
            pt[1].y = yBotton;
            pt[2].x = xLeft;
            pt[2].y = yBotton;
            Polygon(hdc, pt, 3);
        }
        if (Hinh == ID_DUONGTHANG)
        {
            MoveToEx(hdc, xLeft, yTop, NULL);
            LineTo(hdc, xRight, yBotton);
        }
        if (Hinh == ID_HINH_CHORD)
        {
            int centerX = (xLeft + xRight) / 2;
            int centerY = (yTop + yBotton) / 2;
            int radiusX = (xRight - xLeft) / 2;
            int radiusY = (yBotton - yTop) / 2;

            // Điểm bắt đầu và kết thúc nằm chéo góc 45 độ
            int startX = centerX - radiusX / 2;
            int startY = centerY - radiusY / 2;
            int endX = centerX + radiusX / 2;
            int endY = centerY + radiusY / 2;

            Chord(hdc, xLeft, yTop, xRight, yBotton, startX, startY, endX, endY);
        }

        if (Hinh == ID_HINH_QUAT_PIE)
        {
            // Tọa độ hình chữ nhật bao quanh hình elip
            int xL = min(xLeft, xRight);
            int xR = max(xLeft, xRight);
            int yT = min(yTop, yBotton);
            int yB = max(yTop, yBotton);

            // Tính trung điểm để xác định bán kính
            int centerX = (xL + xR) / 2;
            int centerY = (yT + yB) / 2;

            // Điểm bắt đầu cung tròn (trên giữa)
            int xStart = centerX;
            int yStart = yT;

            // Điểm kết thúc cung tròn (trái giữa)
            int xEnd = xL;
            int yEnd = centerY;

            Pie(hdc, xL, yT, xR, yB, xStart, yStart, xEnd, yEnd);
        }


        if (Hinh == ID_HINH_CUNG)
        {
            int centerX = (xLeft + xRight) / 2;
            int centerY = (yTop + yBotton) / 2;
            int radiusX = (xRight - xLeft) / 2;
            int radiusY = (yBotton - yTop) / 2;

            // Điểm bắt đầu và kết thúc nằm chéo góc 45 độ
            int startX = centerX - radiusX / 2;
            int startY = centerY - radiusY / 2;
            int endX = centerX + radiusX / 2;
            int endY = centerY + radiusY / 2;

            Arc(hdc, xLeft, yTop, xRight, yBotton, startX, startY, endX, endY);
        }
        if (Hinh == ID_HINH_CN_BOGOC)
        {
            int xCorner = (xRight - xLeft) / 5;
            int yCorner = (yBotton - yTop) / 5;
            RoundRect(hdc, xLeft, yTop, xRight, yBotton, xCorner, yCorner);
        }
        ReleaseDC(hWnd, hdc);
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_Mau_XanhLa:
                colorNen = RGB(0, 255, 0);
                break;
            case ID_Mau_Vang:
                colorNen = RGB(255, 255, 0);
                break;
            case ID_Mau_Do:
                colorNen = RGB(255, 0, 0);
                break;
            case ID_VIEN_XanhLa:
                colorVien = RGB(0, 255, 0); 
                break;
            case ID_VIEN_Vang: 
                colorVien = RGB(255, 255, 0); 
                break;
            case ID_VIEN_DO:
                colorVien = RGB(255, 0, 0);
                break;
            case ID_HINH_THOI:
            case ID_HINH_CN:
            case ID_HINH_ELLIPSE:
            case ID_DUONGTHANG:
            case ID_HINH_TAMGIAC:
            case ID_HINH_TGV:
            case ID_HINH_CHORD:
            case ID_HINH_QUAT_PIE:
            case ID_HINH_CN_BOGOC:
            case ID_HINH_CUNG:
                Hinh = wmId;
                break;
            case ID_KV_DOT:
                stylePen = PS_DOT;
                break;
            case ID_KV_DASH:
                stylePen = PS_DASH;
                break;
            case ID_KV_SOLD:
                stylePen = PS_SOLID;
                break;
            case ID_KN_HORIZONTAL:
                styleBrush = HS_HORIZONTAL;
                break;
            case ID_KN_VERTICAL:
                styleBrush = HS_VERTICAL;
                break;
            case ID_KN_DIAGCROSS:
                styleBrush = HS_DIAGCROSS;
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
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
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

// Message handler for about box.
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
