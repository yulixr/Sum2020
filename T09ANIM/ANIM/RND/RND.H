/* FILE NAME: RND.H
 * PROGRAMMER: YR4
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          Declarations for RND module.
 */

#ifndef __RND_H_
#define __RND_H_

#define GLEW_STATIC
#include "glew.h"

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
extern HDC YR4_hRndDC;
extern INT YR4_RndFrameW, YR4_RndFrameH;
extern HGLRC YR4_hRndGLRC;

typedef struct tagyr4VERTEX
{
  VEC P; /* Vertex position */
  VEC2 T; /* Vertex texture coord */
  VEC N; /* Vertex normal coord */
  VEC4 C; /* Vertex color */
} yr4VERTEX;

typedef struct tagyr4PRIM
{
  INT
    VA, VBuf,  /* Opengl vertex array and buffer */
    Ibuf;      /* Opengl index buffer */  
  INT NumOfElements; /* Number of elements vericles */
  MATR Trans; /* Additional transformation matrix */
} yr4PRIM;

VOID YR4_RndInit( HWND hWnd );
VOID YR4_RndClose( VOID );

VOID YR4_RndStart( VOID );
VOID YR4_RndEnd( VOID );

VOID YR4_RndCopyFrame( VOID );
VOID YR4_RndResize( INT W, INT H );

VOID YR4_RndCamSet(VEC Loc, VEC At, VEC Up1);
VOID YR4_RndProjSet( VOID );

VOID YR4_RndPrimFree( yr4PRIM *Pr );
VOID YR4_RndPrimCreate( yr4PRIM *Pr, yr4VERTEX *V, INT NoofV, INT *I, INT NoofI );
VOID YR4_RndPrimDraw( yr4PRIM *Pr, MATR World );
BOOL YR4_RndPrimCreateSphere( yr4PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH );
BOOL YR4_RndPrimCreateThor( yr4PRIM *Pr, VEC C, DBL R, DBL r, INT SplitW, INT SplitH );
BOOL YR4_RndPrimLoad( yr4PRIM *Pr, CHAR *FileName );

#endif
/* END OF 'RND.H' FILE */