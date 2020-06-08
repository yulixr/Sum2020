/* FILE NAME: RND.H
 * PROGRAMMER: YR4
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          Declarations for RND module.
 */

#ifndef __RND_H_
#define __RND_H_

#include "../../def.h"

extern DBL
  YR4_RndProjSize,
  YR4_RndProjDist,
  YR4_RndProjFarClip;

extern MATR
  YR4_RndMatrView,
  YR4_RndMatrProj,
  YR4_RndMatrVP;

extern HWND YR4_hRndWnd;
extern HDC YR4_hRndDCFrame;
extern HBITMAP YR4_hRndBmFrame;
extern INT YR4_RndFrameW, YR4_RndFrameH;


typedef struct tagyr4VERTEX
{
  VEC P; /* Vertex position */
} yr4VERTEX;

typedef struct tagyr4PRIM
{
  yr4VERTEX *V; /* Vertex attributes array */
  INT NumOfV; /* Number of vericles */

  INT *I; /* Index array */
  INT NumOfI; /* Number of indices */

  MATR Trans; /* Additional transformation matrix */
} yr4PRIM;

VOID YR4_RndInit( HWND hWnd );
VOID YR4_RndClose( VOID );

VOID YR4_RndStart( VOID );
VOID YR4_RndEnd( VOID );

VOID YR4_RndCopyFrame( HDC hDC );
VOID YR4_RndResize( INT W, INT H );

VOID YR4_RndCamSet(VEC Loc, VEC At, VEC Up1);
VOID YR4_RndProjSet( VOID );

VOID YR4_RndPrimFree( yr4PRIM *Pr );
BOOL YR4_RndPrimCreate( yr4PRIM *Pr, INT NoofV, INT NoofI );
VOID YR4_RndPrimDraw( yr4PRIM *Pr, MATR World );
BOOL YR4_RndPrimCreateSphere( yr4PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH );

#endif
/* END OF 'RND.H' FILE */