/* FILE NAME: RNDBASE.C
 * PROGRAMMER: YR4
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          Base functions.
 */

#include "rnd.h"


/* Initialize function.
 * ARGUMENTS:
 *   -Windows handle
 *       HWND hWnd;
 * RETURNS:
 *   VOID.
 */
VOID YR4_RndInit( HWND hWnd )
{
  HDC hDC;

  YR4_hRndWnd = hWnd;

  hDC = GetDC(hWnd);
  YR4_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(hWnd, hDC);
  YR4_hRndBmFrame = NULL;

  YR4_RndFrameH = 100;
  YR4_RndFrameW = 100;

  YR4_RndProjSize = YR4_RndProjDist = 0.1;
  YR4_RndProjFarClip = 30;

} /* End 'YR4_RndInit' function */

/* Close function.
 * ARGUMENTS:
 *   -VOID
 * RETURNS:
 *   VOID.
 */
VOID YR4_RndClose( VOID )
{
  DeleteObject(YR4_hRndBmFrame);
  DeleteDC(YR4_hRndDCFrame);
} /* End of 'YR4_RndClose' function */

/* Copy frame function.
 * ARGUMENTS:
 *   -Memory context handle
 *       HDC hDC;
 * RETURNS:
 *   VOID.
 */
VOID YR4_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, YR4_RndFrameW, YR4_RndFrameH, 
    YR4_hRndDCFrame, 0, 0, SRCCOPY); 
} /* End of function */

/* Set camera function.
 * ARGUMENTS:
 *   - Position of camera:
 *       VEC Loc, At, Up;
 * RETURNS:
 *   VOID.
 */
VOID YR4_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  YR4_RndMatrView = MatrView(Loc, At, Up);
  YR4_RndMatrVP = MatrMulMatr(YR4_RndMatrView, YR4_RndMatrProj);
} /* End of 'YR4_RndCamSet' function */

/* Start drawing function.
 * ARGUMENTS:
 *   - VOID
 * RETURNS:
 *   VOID.
 */
VOID YR4_RndStart( VOID )
{
  SelectObject(YR4_hRndDCFrame, YR4_hRndBmFrame);
  SelectObject(YR4_hRndDCFrame, GetStockObject(WHITE_BRUSH));
  Rectangle(YR4_hRndDCFrame, 0,0 , YR4_RndFrameW + 1, YR4_RndFrameH + 1);
  SelectObject(YR4_hRndDCFrame, GetStockObject(DC_BRUSH));
  SelectObject(YR4_hRndDCFrame, GetStockObject(BLACK_PEN));
} /* End of 'YR4_RndStart' function */

VOID YR4_RndEnd( VOID )
{
}

/* Set project function.
 * ARGUMENTS:
 *   - VOID
 * RETURNS:
 *   VOID.
 */
VOID YR4_RndProjSet( VOID )
{
  DBL rx, ry;

  rx = ry = YR4_RndProjSize / 2;

  if (YR4_RndFrameW > YR4_RndFrameH)
    rx *= (DBL)YR4_RndFrameW / YR4_RndFrameH;
  else
    ry *= (DBL)YR4_RndFrameH / YR4_RndFrameW;

  YR4_RndMatrProj = 
    MatrFrustum(-rx, rx, -ry, ry,
               YR4_RndProjDist, YR4_RndProjFarClip);
  YR4_RndMatrVP = MatrMulMatr(YR4_RndMatrView, YR4_RndMatrProj);
} /* End of 'YR4_RndProjSet' function */

/* Resize function.
 * ARGUMENTS:
 *   -Weight and height:
 *       INT W, H;
 * RETURNS:
 *   VOID.
 */
 VOID YR4_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(YR4_hRndWnd);

  if (YR4_hRndBmFrame != NULL)
    DeleteObject(YR4_hRndBmFrame);

  YR4_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(YR4_hRndWnd, hDC);
  SelectObject(YR4_hRndDCFrame, YR4_hRndBmFrame);

  YR4_RndFrameH = H;
  YR4_RndFrameW = W;

  YR4_RndProjSet();
} /* End of 'YR4_RndResize' function */

/* END OF 'RNDBASE.C' FILE */
