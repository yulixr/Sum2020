/* FILE NAME: RNDBASE.C
 * PROGRAMMER: YR4
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          Base functions.
 */

#include "rnd.h"

/* link lib */
#pragma comment(lib, "opengl32")

/* Initialize function.
 * ARGUMENTS:
 *   -Windows handle
 *       HWND hWnd;
 * RETURNS:
 *   VOID.
 */
VOID YR4_RndInit( HWND hWnd )
{
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};
  CHAR *Str;

  YR4_hRndWnd = hWnd; 

  YR4_hRndDC = GetDC(hWnd);

  /* OpenGL initialization */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;

  i = ChoosePixelFormat(YR4_hRndDC, &pfd);
  DescribePixelFormat(YR4_hRndDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(YR4_hRndDC, i, &pfd);

  /* OpenGL setup context */
  YR4_hRndGLRC = wglCreateContext(YR4_hRndDC);
  wglMakeCurrent(YR4_hRndDC, YR4_hRndGLRC);
  
  if (glewInit() != GLEW_OK)
    exit(0);
  if (!(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
    exit(0);

  Str = glGetString(GL_VENDOR);
  Str = glGetString(GL_RENDERER);
  Str = glGetString(GL_VERSION);

  glClearColor(0.30, 0.47, 0.8, 1);
  glEnable(GL_DEPTH_TEST);

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
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(YR4_hRndGLRC);
  
  ReleaseDC(YR4_hRndWnd, YR4_hRndDC);
} /* End of 'YR4_RndClose' function */

/* Copy frame function.
 * ARGUMENTS:
 *   -Memory context handle
 *       HDC hDC;
 * RETURNS:
 *   VOID.
 */
VOID YR4_RndCopyFrame( VOID )
{
  SwapBuffers(YR4_hRndDC);
  //wglSwapLayerBuffers(YR4_hRndDC, WGL_SWAP_MAIN_PLANE); 
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //SelectObject(YR4_hRndDC, GetStockObject(NULL_BRUSH));
  //SelectObject(YR4_hRndDC, GetStockObject(BLACK_PEN));
} /* End of 'YR4_RndStart' function */

VOID YR4_RndEnd( VOID )
{
  glFinish();
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
  /* Set Opengl viewport */
  glViewport(0, 0, W, H);

  YR4_RndFrameH = H;
  YR4_RndFrameW = W;

  YR4_RndProjSet();
} /* End of 'YR4_RndResize' function */

/* END OF 'RNDBASE.C' FILE */
