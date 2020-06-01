/* Raksina Yulia, 01.06.2020 */
#include <windows.h>
#include <stdlib.h>

#define WND_CLASS_NAME "My Class Name"

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

/* Main window handle func */
LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  POINT pt;
  HPEN hPen, hOldPen;
  static INT w, h;
  
  switch(Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 1002, NULL);
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    return 0;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    return 0;
  case WM_TIMER:
    //InvalidateRect(hWnd, NULL, TRUE);
    return 0;
  case WM_LBUTTONDOWN:
  case WM_MOUSEMOVE:
    hDC = GetDC(hWnd);
    if (wParam & MK_LBUTTON)
      Ellipse(hDC, LOWORD(lParam) - 30, HIWORD(lParam) - 30, LOWORD(lParam) + 30, HIWORD(lParam) + 30);
    ReleaseDC(hWnd, hDC);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);

    SelectObject(hDC, GetStockObject(DC_BRUSH));
    SelectObject(hDC, GetStockObject(NULL_PEN));

   // SetDCBrushColor(hDC, RGB(rand() % 256, rand() % 256, rand() % 256));
    SetDCBrushColor(hDC, RGB(0, 255, 0));
    //Ellipse(hDC, rand() % 1024, rand() % 900, rand() % 1024, rand() % 900);
    Ellipse(hDC, 0, 0, w + 1, h + 1);

    MoveToEx(hWnd, w / 2, h / 2, NULL);

    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    hPen = CreatePen(PS_SOLID, 8, RGB(255, 0, 0));

    hOldPen = SelectObject(hDC, hPen);

    SetDCPenColor(hDC, RGB(0, 0, 0));
    LineTo(hDC, pt.x, pt.y);

    SelectObject(hDC, hOldPen);
    DeleteObject(hPen);

    EndPaint(hWnd, &ps);
    return 0;
  case WM_CLOSE:
    if(MessageBox(hWnd, "Are you sure you want to close?", "Close", 
        MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION) == IDYES)
      DestroyWindow(hWnd);
    return 0;
  case WM_DESTROY:
    PostMessage(hWnd, WM_QUIT, 0, 0);
    KillTimer(hWnd, 30);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}/* End of 'WinFunc' func */

/* END OF 'T01FWIN.C' FILE */