/* FILE NAME: ANIM.C
 * PROGRAMMER: YR4
 * DATE: 09.06.2020
 * PURPOSE: 3D animation project.
 *          Animation module.
 */
#include "anim.h"

yr4ANIM YR4_Anim;

VOID YR4_AnimInit( HWND hWnd )
{
  memset(&YR4_Anim, 0, sizeof(yr4ANIM));

  YR4_Anim.hWnd = hWnd;
  YR4_RndInit(hWnd);
  YR4_Anim.hDC = YR4_hRndDC;

  YR4_TimerInit();
  YR4_AnimInputInit();
}

VOID YR4_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < YR4_Anim.NumOfUnits; i++)
  {
    YR4_Anim.Units[i]->Close(YR4_Anim.Units[i], &YR4_Anim);
    free(YR4_Anim.Units[i]);
    YR4_Anim.Units[i] = NULL;
  }
  YR4_Anim.NumOfUnits = 0;
  YR4_RndClose();
}

VOID YR4_AnimRender( VOID )
{
  INT i;
  YR4_AnimInputResponse();
  YR4_TimerResponse();

  for (i = 0; i < YR4_Anim.NumOfUnits; i++)
    YR4_Anim.Units[i]->Response(YR4_Anim.Units[i], &YR4_Anim);

  YR4_RndStart();
  for (i = 0; i < YR4_Anim.NumOfUnits; i++)
    YR4_Anim.Units[i]->Render (YR4_Anim.Units[i], &YR4_Anim);
  YR4_RndEnd();
}

VOID YR4_AnimAddUnit( yr4UNIT *Uni )
{
  if (YR4_Anim.NumOfUnits < YR4_MAX_UNITS)
    YR4_Anim.Units[YR4_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &YR4_Anim); 
}

VOID YR4_AnimCopyFrame( VOID )
{
  YR4_RndCopyFrame();
}

VOID YR4_AnimEnd( VOID )
{

}

VOID YR4_AnimResize( INT w, INT h )
{
  YR4_Anim.H = h;
  YR4_Anim.W = w;
  YR4_RndResize(w, h);
}

VOID YR4_AnimFlipFullScreen( HWND hWnd )
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
  IsFullScreen = !IsFullScreen;
}

/* END OF 'ANIM.C' FILE */