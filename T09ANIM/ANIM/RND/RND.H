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
#include "res/rndres.h"

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
extern VEC YR4_RndCamLoc;
typedef struct tagyr4VERTEX
{
  VEC P; /* Vertex position */
  VEC2 T; /* Vertex texture coord */
  VEC N; /* Vertex normal coord */
  VEC4 C; /* Vertex color */
} yr4VERTEX;

typedef enum tagyr4PRIM_TYPE
{
  YR4_RND_PRIM_TRIMESH, /* Array of triangles */
  YR4_RND_PRIM_TRISTRIP, /* Array of stripped triangles */
  YR4_RND_PRIM_LINES,
  YR4_RND_PRIM_POINTS, /* Array of points */
} yr4PRIM_TYPE;

typedef struct tagyr4PRIM
{
  yr4PRIM_TYPE Type;
  INT
    VA, VBuf,  /* Opengl vertex array and buffer */
    Ibuf;      /* Opengl index buffer */  
  INT NumOfElements; /* Number of elements vericles */
  MATR Trans; /* Additional transformation matrix */
  INT MtlNo; /* Material number in material array */
} yr4PRIM;

VOID YR4_RndInit( HWND hWnd );
VOID YR4_RndClose( VOID );

VOID YR4_RndStart( VOID );
VOID YR4_RndEnd( VOID );

VOID YR4_RndCopyFrame( VOID );
VOID YR4_RndResize( INT W, INT H );

VOID YR4_RndCamSet(VEC Loc, VEC At, VEC Up1);
VOID YR4_RndProjSet( VOID );

/********** prim handle ************/
VOID YR4_RndPrimFree( yr4PRIM *Pr );
VOID YR4_RndPrimCreate( yr4PRIM *Pr, yr4VERTEX *V, INT NoofV, INT *I, INT NoofI, yr4PRIM_TYPE Type );
VOID YR4_RndPrimDraw( yr4PRIM *Pr, MATR World );
BOOL YR4_RndPrimCreateSphere( yr4PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH );
BOOL YR4_RndPrimCreateThor( yr4PRIM *Pr, VEC C, DBL R, DBL r, INT SplitW, INT SplitH );
BOOL YR4_RndPrimLoad( yr4PRIM *Pr, CHAR *FileName );
BOOL YR4_RndPrimCreateFromGrid( yr4PRIM *Pr, yr4VERTEX *V, INT W, INT H, BOOL IsNormalsNeed );

/******** image handle ************/
typedef struct tagyr4IMAGE
{
  /* Image size */
  INT W, H;

  DWORD *PixelsDW;
  BYTE (*PixelsC)[4];
  BYTE *Pixels;
} yr4IMAGE;

BOOL YR4_RndImgLoad( yr4IMAGE *Img, CHAR *FileName );
VOID YR4_RndImgFree( yr4IMAGE *Img );
BOOL YR4_RndImgCreate( yr4IMAGE *Img, INT W, INT H );

/******** prims handle **********/
typedef struct tagyr4PRIMS
{
  INT NumOfPrims; /* Number of primitives in array */  
  yr4PRIM *Prims; /* Array of primitives */
  MATR Trans;     /* Common transformation matrix */
} yr4PRIMS;

BOOL YR4_RndPrimsLoad( yr4PRIMS *Prs, CHAR *FileName );
VOID YR4_RndPrimsDraw( yr4PRIMS *Prs, MATR World );
VOID YR4_RndPrimsFree( yr4PRIMS *Prs );
BOOL YR4_RndPrimsCreate( yr4PRIMS *Prs, INT NumOfPrims );

#endif
/* END OF 'RND.H' FILE */