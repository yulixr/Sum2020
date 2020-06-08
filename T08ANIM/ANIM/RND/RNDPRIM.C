/* FILE NAME: RNDPRIM.C
 * PROGRAMMER: YR4
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          Primitives.
 */

#include "rnd.h"
#include <string.h>

/* Create prim structure.
 * ARGUMENTS:
 *   -Prim structure:
 *       yr4PRIM *Pr;
 *   -Number of verticles and indicies:
 *       INT NoofV, NoofI;
 * RETURNS:
 *   BOOL.
 */
BOOL YR4_RndPrimCreate( yr4PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;

  memset(Pr, 0, sizeof(yr4PRIM));

  size = sizeof(yr4VERTEX) * NoofV + sizeof(INT) * NoofI;
  
  Pr->V = malloc(size);
  if (Pr->V == NULL)
    return FALSE;

  memset(Pr->V, 0, size);
  Pr->I = (INT *)(Pr->V + NoofV);

  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;

  Pr->Trans = MatrIdentity();
  return TRUE;
} /* end of YR4_RndPrimCreate func */

/* Free Prim structure.
 * ARGUMENTS:
 *   -Prim structure:
 *       yr4PRIM *Pr;
 * RETURNS:
 *   VOID.
 */
VOID YR4_RndPrimFree( yr4PRIM *Pr )
{
  if (Pr->V != NULL)
    free(Pr->V);
  memset(Pr, 0, sizeof(yr4PRIM));
} /* end of YR4_RndPrimFree func */

/* Draw prim structure.
 * ARGUMENTS:
 *   -Prim structure:
 *       yr4PRIM *Pr;
 *   -Matrix:
 *       MATR World;
 * RETURNS:
 *   VOID.
 */
VOID YR4_RndPrimDraw( yr4PRIM *Pr, MATR World )
{
  INT i;
  POINT *pnts; /* vertex projections */
  MATR M = MatrMulMatr3(Pr->Trans, World, YR4_RndMatrVP);

  /* Allocate memory for projections */
  pnts = malloc(sizeof(POINT) * Pr->NumOfV);
  if (pnts == NULL)
      return;

  /* Project all vertices */
  for (i = 0; i < Pr->NumOfV; i++)
  {
    /* Convert from World to NDC */
    VEC p = VecMulMatr(Pr->V[i].P, M);

    /* Convert NDC to frame (viewport) */
    pnts[i].x = (INT)((p.X + 1) * YR4_RndFrameW / 2);
    pnts[i].y = (INT)((-p.Y + 1) * YR4_RndFrameH / 2);
  }

  /* Draw all triangles */
  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    MoveToEx(YR4_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y, NULL);
    
    LineTo(YR4_hRndDCFrame, pnts[Pr->I[i + 1]].x, pnts[Pr->I[i + 1]].y);
    LineTo(YR4_hRndDCFrame, pnts[Pr->I[i + 2]].x, pnts[Pr->I[i + 2]].y);
    LineTo(YR4_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y);
    /*POINT p[3];

    p[0] = pnts[Pr->I[i]];
    p[1] = pnts[Pr->I[i + 1]];
    p[2] = pnts[Pr->I[i + 2]];

    Polygon(YR4_hRndDCFrame, p, 3);*/
  }
  free(pnts);
} /* End of 'YR4_RndPrimDraw' function */

/* Create sphere prim structure.
 * ARGUMENTS:
 *   -Prim structure:
 *       yr4PRIM *Pr;
 *   -Vector (position):
 *       VEC C;
 *   - Radius:
 *       DBL R;
 *   - WIdth and height:
 *       INT SplitW, SplitH;
 * RETURNS:
 *   BOOL.
 */
BOOL YR4_RndPrimCreateSphere( yr4PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH )
{
  INT i, j, m, n;
  DOUBLE t, p;

  if(!YR4_RndPrimCreate(Pr, SplitW * SplitH, (SplitW - 1) * 2 * (SplitH - 1) * 3))
    return FALSE;

  for (i = 0, t = 0, m = 0; i < SplitH; i++, t += PI / (SplitH - 1))
    for (j = 0, p = 0; j < SplitW; j++, p += 2 * PI / (SplitW - 1))
       Pr->V[m++].P = (VecSet(C.X + R * cos(p) * sin(t),
                              C.Y + R * cos(t),
                              C.Z + R * sin(p) * sin(t)));

  for (i = 0, m = 0, n = 0; i < SplitH - 1; i++, m++)
    for (j = 0; j < SplitW - 1; j++, m++)
    {
      Pr->I[n++] = m;
      Pr->I[n++] = m + 1;
      Pr->I[n++] = m + SplitW;

      Pr->I[n++] = m + SplitW;
      Pr->I[n++] = m + 1;
      Pr->I[n++] = m + SplitW + 1;
    }
  return TRUE;
} /* end of 'YR4_RndPrimCreateSphere' func */

/* Create thor prim structure.
 * ARGUMENTS:
 *   -Prim structure:
 *       yr4PRIM *Pr;
 *   -Vector (position):
 *       VEC C;
 *   - Radiuses:
 *       DBL R, r;
 *   - WIdth and height:
 *       INT SplitW, SplitH;
 * RETURNS:
 *   BOOL.
 */
BOOL YR4_RndPrimCreateThor( yr4PRIM *Pr, VEC C, DBL R, DBL r, INT SplitW, INT SplitH )
{
  INT i, j, m, n;
  DOUBLE t, p;

  if(!YR4_RndPrimCreate(Pr, SplitW * SplitH, (SplitW - 1) * 2 * (SplitH - 1) * 3))
    return FALSE;

  for (i = 0, t = -PI, m = 0; i < SplitH; i++, t += 2 * PI / (SplitH - 1))
    for (j = 0, p = 0; j < SplitW; j++, p += 2 * PI / (SplitW - 1))
       Pr->V[m++].P = (VecSet(C.X + (R + r * cos(t)) * cos(p),
                              C.Y + r * sin(t),
                              C.Z + (R + r * cos(t)) * sin(p)));

  for (i = 0, m = 0, n = 0; i < SplitH - 1; i++, m++)
    for (j = 0; j < SplitW - 1; j++, m++)
    {
      Pr->I[n++] = m;
      Pr->I[n++] = m + 1;
      Pr->I[n++] = m + SplitW;

      Pr->I[n++] = m + SplitW;
      Pr->I[n++] = m + 1;
      Pr->I[n++] = m + SplitW + 1;
    }
  return TRUE;
} /* end of 'YR4_RndPrimCreateThor' func */

#include <stdio.h>
/* Load model.
 * ARGUMENTS:
 *   -Prim structure:
 *       yr4PRIM *Pr;
 *   -File name:
 *       CHAR *FileName;
 * RETURNS:
 *   BOOL.
 */
BOOL YR4_RndPrimLoad( yr4PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  static CHAR Buf[1000];
  INT nv = 0, nf = 0;
  
  memset(Pr, 0, sizeof(yr4PRIM));

  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;
  
  /* Vertex and facet count */
  while (fgets(Buf, sizeof(Buf), F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      nf++;

  if (!YR4_RndPrimCreate(Pr, nv, nf * 3))
  {
    fclose(F);
    return FALSE;
  }
  
  /* Load geometry data */
  rewind(F);
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf), F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;
      sscanf(Buf + 2, "%lf %lf %lf", &x, &y, &z);
      Pr->V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n1, n2, n3;

      sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3) == 3 ||
      sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
      sscanf(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
      sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3;

      Pr->I[nf++] = n1 - 1;
      Pr->I[nf++] = n2 - 1;
      Pr->I[nf++] = n3 - 1;
    }

  fclose(F);
  return TRUE;
} /* end of 'YR4_RndPrimLoad' func */

/* END OF 'RNDPRIM.C' FILE */