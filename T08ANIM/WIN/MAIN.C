/* FILE NAME: MAIN.C
 * PROGRAMMER: YR4
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project. 
 *          WinAPI startup module.
 */

#include <time.h>

#include "../def.h"
#include "../anim/rnd/rnd.h"

#define WND_CLASS_NAME "My Class Name"

/* Forward declaration */
LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT CmdShow )
{
  HWND hWnd;
  MSG msg;
  WNDCLASS wc;

  SetDbgMemHooks();

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
  hWnd = CreateWindow(WND_CLASS_NAME, "T08ANIM", WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
    NULL, NULL, hInstance, NULL);

  ShowWindow(hWnd, CmdShow);
  
  /* Message loop */
  while (TRUE)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
      SendMessage(hWnd, WM_TIMER, 47, 0);

  return 0;
} /* End of 'WinMain' func */

/* Main window handle func */
LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  PAINTSTRUCT ps;
  HDC hDC;
  static yr4PRIM Pr;
  static yr4PRIM Pr1;
  static yr4PRIM Pr2;
  static yr4PRIM Pr3;
  static yr4PRIM Pr4;
  static yr4PRIM Pr5;
  LONG t = clock();
  

  switch(Msg)
  {
  case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + 2 * GetSystemMetrics(SM_CYBORDER);
    return 0;
  case WM_CREATE:
    YR4_RndInit(hWnd);
    YR4_RndCamSet(VecSet(22, 14, 20), VecSet(0, 0, 0), VecSet(0, 1, 0));
    SetTimer(hWnd, 30, 60, NULL);

    YR4_RndPrimCreateSphere(&Pr, VecSet(0, 7, 0), 2, 20, 10);
    YR4_RndPrimLoad(&Pr1, "cow.obj");
    YR4_RndPrimLoad(&Pr2, "Door.obj");
    YR4_RndPrimLoad(&Pr3, "table.obj");
    YR4_RndPrimLoad(&Pr4, "cat.obj");
    YR4_RndPrimLoad(&Pr5, "deer.obj");
    //YR4_RndPrimCreateThor(&Pr1, VecSet(0, 0, 0), 7, 3, 38, 19);
    
    return 0;
  case WM_SIZE:
    /* Obtain new window width and height */
    YR4_RndResize(LOWORD(lParam), HIWORD(lParam));

    SendMessage(hWnd, WM_TIMER, 47, 0);
    return 0;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    return 0;
  case WM_TIMER:
    YR4_RndStart();
    YR4_RndPrimDraw(&Pr, MatrMulMatr(MatrRotateY(30 * t / 2000.0), MatrTranslate(VecSet(6, sin(5 * t / 2000.0) / 1.5, 13))));
    //YR4_RndPrimDraw(&Pr1, MatrMulMatr(MatrRotateY(-30), MatrTranslate(VecSet(sin(t / 1000.0) * 4, sin(7 * t / 2000.0), sin(t / 1000.0) * 4))));
    YR4_RndPrimDraw(&Pr1, MatrMulMatr(MatrTranslate(VecSet(-10, fabs(sin(t * 1.5 / 1000.0)) * 6, -15)), MatrRotateY(-t * 40 / 1000.0)));
    YR4_RndPrimDraw(&Pr2, MatrMulMatr(MatrTranslate(VecSet(3, 0, -10)), MatrRotateY(70)));
    YR4_RndPrimDraw(&Pr3, MatrMulMatr3(MatrScale(VecSet1(0.039)), MatrRotateY(20), MatrTranslate(VecSet(5, 0, -5))));
    YR4_RndPrimDraw(&Pr4, MatrMulMatr3(MatrScale(VecSet1(0.018)), MatrTranslate(VecSet(5, 0, -15)), MatrRotateY(-t * 30 / 500.0)));
    YR4_RndPrimDraw(&Pr5, MatrMulMatr3(MatrRotateY(t * 30 / 1000.0), MatrScale(VecSet1(0.004)), MatrTranslate(VecSet(8.3, 4, -0.5))));
    //YR4_RndPrimDraw(&Pr1, MatrRotateY(30 * t / 2000.0));
    YR4_RndEnd();

    hDC = GetDC(hWnd);
    YR4_RndCopyFrame(hDC);
    ReleaseDC(hWnd, hDC);
    //InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    YR4_RndCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_CLOSE:
    if(MessageBox(hWnd, "Are you sure you want to close?", "Close", 
        MB_YESNO | MB_ICONQUESTION) == IDYES)
      DestroyWindow(hWnd);
    return 0;
  case WM_DESTROY:
    YR4_RndPrimFree(&Pr);
    YR4_RndPrimFree(&Pr1);
    YR4_RndPrimFree(&Pr2);
    YR4_RndPrimFree(&Pr3);
    YR4_RndPrimFree(&Pr4);
    YR4_RndPrimFree(&Pr5);
    YR4_RndClose();
    KillTimer(hWnd, 30);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}/* End of 'WinFunc' func */


/* END OF 'MAIN.C' FILE */