/* FILE NAME: T03CLOCK.C
   PROGRAMMER: YR4
   DATE: 02.01.2020
   PURPOSE: Clock
*/
#include <windows.h>
#include <stdlib.h>
#include <math.h>

#define WND_CLASS_NAME "My Class Name"
#define MPI 3.14159265358

/* Forward declaration */
LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/* The main programm func */
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT CmdShow )
{
  HWND hWnd;
  MSG msg;
  WNDCLASS wc;

  /* Fill window class structure */
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpszClassName = WND_CLASS_NAME;
  wc.lpszMenuName = NULL;
  wc.lpfnWndProc = WinFunc;

  /* Register window class */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "Error", MB_OK | MB_ICONERROR);
    return 0;
  }

  /* Window creation */
  hWnd = CreateWindow(WND_CLASS_NAME, "Practice", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
    NULL, NULL, hInstance, NULL);

  ShowWindow(hWnd, CmdShow);
  
  /* Message loop */
  while (GetMessage(&msg, NULL, 0, 0))
    DispatchMessage(&msg);

  return 0;
} /* End of 'WinMain' func */

/* Toggle window fullscreen mode function */
VOID FlipFullScreen( HWND hWnd )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRect;

  if (!IsFullScreen)
  {
    HMONITOR hmon;
    MONITORINFO moninfo;
    RECT rc;

    /* Goto fullscreen mode */
    GetWindowRect(hWnd, &SaveRect);

    /* Get nearest monitor */
    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    /* Get monitor information */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, &moninfo);

    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);
    SetWindowPos(hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  else
  {
    /* Restore window size and position */
    SetWindowPos(hWnd, HWND_TOP,
      SaveRect.left, SaveRect.top,
      SaveRect.right - SaveRect.left, SaveRect.bottom - SaveRect.top,
      SWP_NOOWNERZORDER);
  }
} /* End of 'FlipFullScreen' function */

/* DrawHand func */
VOID DrawHand( HDC hDC, INT X0, INT Y0, DOUBLE a, INT L, INT W, INT R, INT G, INT B )
{ 
  HPEN hPenOld;
  HBRUSH hBrOld;
  INT i;

  POINT pnts[] = 
  {
    {0, L}, {W, 0}, {W / 2, - W / 3}, {2 * W / 3, -(2 * W / 3)}, {0, -L / 4}, {-2 * W / 3, -(2 * W / 3)}, {- W / 2, - W / 3}, {-W, 0}
  }, pnts1[sizeof(pnts) / sizeof(pnts[0])];

  for (i = 0; i < sizeof(pnts) / sizeof(pnts[0]); i++)
  {
    pnts1[i].x = X0 + pnts[i].x * cos(a) + pnts[i].y * sin(a) ;
    pnts1[i].y = Y0 - (pnts[i].y * cos(a) - pnts[i].x * sin(a));
  }
  
  hPenOld = SelectObject(hDC, GetStockObject(NULL_PEN));
  hBrOld = SelectObject(hDC, GetStockObject(DC_BRUSH));

  SetDCBrushColor(hDC, RGB(R, G, B));

  Polygon(hDC, pnts1, sizeof(pnts) / sizeof(pnts[0])); 

  SelectObject(hDC, hPenOld);
  SelectObject(hDC, hBrOld);
} /* end Drawhand func */

/* Main window handle func */
LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  POINT pt;
  HPEN hPen, hPenOld;
  BITMAP bm, bm1;
  SYSTEMTIME st;
  HFONT hFnt, hOldFnt;
  static INT w, h;
  static HDC hMemDC, hMemDCImage, hMemDCSprite;
  static HBITMAP hBm, hBmImage, hBmAnd, hBmXor;
  static char *wd[] = {
    "sun", "mon", "tue", "wed", "thu", "fri", "sat" 
  };
  INT r, i;
  RECT rc;
  CHAR Buf[102];
  
  switch(Msg)
  {
  case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + 2 * GetSystemMetrics(SM_CYBORDER);
    return 0;
  case WM_CREATE:
    SetTimer(hWnd, 0, 10, NULL);
    hBmImage = LoadImage(NULL, "cl.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hBmAnd = LoadImage(NULL, "ruand.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hBmXor = LoadImage(NULL, "ruxor.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    hMemDCImage = CreateCompatibleDC(hDC);
    hMemDCSprite = CreateCompatibleDC(hDC);
    SelectObject(hMemDCImage, hBmImage);
    ReleaseDC(hWnd, hDC);
    hBm = NULL;
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, w, h);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_SYSKEYDOWN:
    if (wParam == VK_RETURN)
      FlipFullScreen(hWnd);
    return 0;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    return 0;
  case WM_TIMER:
    GetLocalTime(&st);
    /* cleaning background */
    SelectObject(hMemDC, GetStockObject(WHITE_BRUSH));
    SelectObject(hMemDC, GetStockObject(NULL_PEN));
    Rectangle(hMemDC, 0, 0, w + 1, h + 1); 

    /* drawing clockface */ 
    r = (w < h ? w : h);
    GetObject(hBmImage, sizeof(BITMAP), &bm); 
    SetStretchBltMode(hMemDC, COLORONCOLOR);
    StretchBlt(hMemDC, w/2 - r/2, h/2 - r/2, r, r, hMemDCImage, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
    
    /* seconds hand */
    hPen = CreatePen(PS_SOLID, 3, RGB(100, 0, 255));
    hPenOld = SelectObject(hMemDC, hPen);   
    DrawHand(hMemDC, w / 2, h / 2, (st.wSecond + st.wMilliseconds / 1000.0) * 2 * MPI / 60.0,  r * 0.36, 16, 50, 100, 90); 
    DeleteObject(hPen); 

    /* minute hand */
    hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 60));
    hPenOld = SelectObject(hMemDC, hPen);
    DrawHand(hMemDC, w / 2, h / 2, (st.wMinute + st.wSecond / 60.0) * 2 * MPI / 60.0,  r * 0.26, 10, 0, 130, 160); 
    DeleteObject(hPen);

    /* hour hand */
    hPen = CreatePen(PS_SOLID, 3, RGB(255, 100, 0));
    hPenOld = SelectObject(hMemDC, hPen);
    DrawHand(hMemDC, w / 2, h / 2, (st.wHour % 12 + st.wMinute / 60.0) * 2 * MPI / 12.0,  r * 0.19, 11, 60, 80, 160); 
    DeleteObject(hPen);
   
    /* Output text */
    hFnt = CreateFont(r/8, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, RUSSIAN_CHARSET, 
      OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_MODERN | VARIABLE_PITCH, "Mistral"); 
    hOldFnt = SelectObject(hMemDC, hFnt);

    i = wsprintf(Buf, "%02i.%02i.%i\n(%s)", st.wDay, st.wMonth, st.wYear, wd[st.wDayOfWeek]);
    SetBkMode(hMemDC, TRANSPARENT);
    SetTextColor(hMemDC, RGB(50, 56, 125));

    rc.left = 0;
    rc.right = w;
    rc.top = 3 * h / 4;
    rc.bottom = h;
    DrawText(hMemDC, Buf, i, &rc, DT_CENTER | DT_VCENTER);

    /* Draw sprite */
    GetObject(hBmAnd, sizeof(BITMAP), &bm1);
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    SelectObject(hMemDCSprite, hBmAnd);
    BitBlt(hMemDC, pt.x - bm1.bmWidth / 2, pt.y - bm1.bmHeight / 2, bm1.bmWidth, bm1.bmHeight, hMemDCSprite, 0, 0, SRCAND);
    SelectObject(hMemDCSprite, hBmXor);
    BitBlt(hMemDC, pt.x - bm1.bmWidth / 2, pt.y - bm1.bmHeight / 2, bm1.bmWidth, bm1.bmHeight, hMemDCSprite, 0, 0, SRCINVERT);
    /* sent repaint msg */
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    /* copy frame to window */
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_CLOSE:
    if(MessageBox(hWnd, "Are you sure you want to close?", "Close", 
        MB_YESNO | MB_ICONQUESTION) == IDYES)
      DestroyWindow(hWnd);
    return 0;
  case WM_DESTROY:
    if (hBm != NULL)
      DeleteObject(hBm);
    DeleteDC(hMemDC);
    DeleteObject(hBmImage);
    DeleteDC(hMemDCImage);

    PostMessage(hWnd, WM_QUIT, 0, 0);
    KillTimer(hWnd, 30);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}/* End of 'WinFunc' func */

/* END OF 'T01FWIN.C' FILE */