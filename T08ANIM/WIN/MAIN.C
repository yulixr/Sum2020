/* FILE NAME: MAIN.C
 * PROGRAMMER: YR4
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project. 
 *          WinAPI startup module.
 */

#include "../units.h"

#define WND_CLASS_NAME "My Class Name"

INT YR4_MouseWheel;
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
  INT i;

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

  for(i = 0; i < 9; i++)
    YR4_AnimAddUnit(YR4_UnitCreateBall());
  YR4_AnimAddUnit(YR4_UnitCreateCow());
  YR4_AnimAddUnit(YR4_UnitCreateCtrl());
  
  
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

  switch(Msg)
  {
  case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + 2 * GetSystemMetrics(SM_CYBORDER);
    return 0;
  case WM_CREATE:
    YR4_AnimInit(hWnd);
    
    /*YR4_RndInit(hWnd);
    YR4_RndCamSet(VecSet(0, 15, 26), VecSet(0, 0, 0), VecSet(0, 1, 0));
    SetTimer(hWnd, 30, 60, NULL);

    YR4_RndPrimCreateSphere(&Pr, VecSet(0, 7, 0), 1.5, 20, 10);
    YR4_RndPrimLoad(&Pr1, "desk.obj");
    YR4_RndPrimLoad(&Pr2, "notebook.obj");
    YR4_RndPrimLoad(&Pr3, "chair.obj");
    YR4_RndPrimLoad(&Pr4, "cat.obj");
    YR4_RndPrimLoad(&Pr5, "Door.obj"); */
    
    return 0;
  case WM_SIZE:
    /* Obtain new window width and height */
    YR4_AnimResize(LOWORD(lParam), HIWORD(lParam));

    SendMessage(hWnd, WM_TIMER, 47, 0);
    return 0;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    else if (wParam == 'F')
      YR4_AnimFlipFullScreen(hWnd);
    return 0;
  case WM_TIMER:
    /*YR4_RndStart();
    YR4_RndPrimDraw(&Pr, MatrMulMatr(MatrRotateY(30 * t / 2000.0), MatrTranslate(VecSet(3, 3 + sin(5 * t / 2000.0) / 1.5, 2.7))));
    YR4_RndPrimDraw(&Pr1, MatrMulMatr(MatrScale(VecSet1(0.007)), MatrRotateY(180)));
    YR4_RndPrimDraw(&Pr2, MatrMulMatr(MatrRotateY(110), MatrTranslate(VecSet(-4, 7, 0))));
    YR4_RndPrimDraw(&Pr3, MatrMulMatr4(MatrScale(VecSet1(0.07)), MatrRotateX(270), MatrRotateY(t * 20 / 1000.0), MatrTranslate(VecSet(-1, 0, 6))));
    YR4_RndPrimDraw(&Pr4, MatrMulMatr3(MatrScale(VecSet1(0.016)), MatrTranslate(VecSet(5, fabs(sin(t * 2 / 500.0)) * 2 - 3, -12)), MatrRotateY(-t * 30 / 500.0)));
    YR4_RndPrimDraw(&Pr5, MatrMulMatr(MatrTranslate(VecSet(-3, 0, -15)), MatrRotateY(60))); 
    YR4_RndEnd();*/
    YR4_AnimRender();

    /*hDC = GetDC(hWnd);
    YR4_AnimCopyFrame(hDC);
    ReleaseDC(hWnd, hDC);*/
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_LBUTTONDOWN:
    SetCapture(hWnd);
    return 0;
  case WM_LBUTTONUP:
    ReleaseCapture();
    return 0;
  case WM_MOUSEWHEEL:
    YR4_MouseWheel += (SHORT)HIWORD(wParam);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    YR4_AnimCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_CLOSE:
    if(MessageBox(hWnd, "Are you sure you want to close?", "Close", 
        MB_YESNO | MB_ICONQUESTION) == IDYES)
      DestroyWindow(hWnd);
    return 0;
  case WM_DESTROY:
    YR4_AnimClose();
    KillTimer(hWnd, 30);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}/* End of 'WinFunc' func */


/* END OF 'MAIN.C' FILE */