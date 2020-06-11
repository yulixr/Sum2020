/* FILE NAME: RNDDATA.C
 * PROGRAMMER: YR4
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          Base definitions.
 */

#include "rnd.h"

HWND YR4_hRndWnd; /* Work window handle */
HDC YR4_hRndDC; /* Work window device conext */
INT YR4_RndFrameW, YR4_RndFrameH; /* Work window size */
HGLRC YR4_hRndGLRC; /* OpenGL context */

DBL
  YR4_RndProjSize,  /* Project plane fit square */
  YR4_RndProjDist,  /* Distance to project plane from viewer (near) */
  YR4_RndProjFarClip;  /* Distance to project far clip plane (far) */

MATR
  YR4_RndMatrView, /* View coordinate system matrix */
  YR4_RndMatrProj, /* Projection coordinate system matrix */
  YR4_RndMatrVP;   /* Stored (View * Proj) matrix */

/* END OF 'RNDDATA.C' FILE */