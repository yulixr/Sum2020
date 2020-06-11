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
 *   -vertex array:
 *      yr4VERTEX *V;
 *   -index array:
 *      INT *I;
 *   -Vertex and index arrays size:
 *       INT NoofV, NoofI;
 * RETURNS:
 *   VOID.
 */
VOID YR4_RndPrimCreate( yr4PRIM *Pr, yr4VERTEX *V, INT NoofV, INT *I, INT NoofI )
{
  memset(Pr, 0, sizeof(yr4PRIM));

  if (V != NULL)
  {
    glGenBuffers(1, &Pr->VBuf);
    glGenVertexArrays(1, &Pr->VA);

    /* active vertex array */
    glBindVertexArray(Pr->VA);

    /* active vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);

    /* fill data */
    glBufferData(GL_ARRAY_BUFFER, sizeof(yr4VERTEX) * NoofV, V, GL_STATIC_DRAW);
    
    /* set data order */
    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(yr4VERTEX),
                        (VOID *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(yr4VERTEX),
                        (VOID *)(sizeof(VEC)));
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(yr4VERTEX),
                        (VOID *)(sizeof(VEC) + sizeof(VEC2)));
    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(yr4VERTEX),
                        (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2)));
  
    /* enable layouts */
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    /* disable vertex array */
    glBindVertexArray(0);
  }

  if (I != 0)
  {
    glGenBuffers(1, &Pr->Ibuf);
    /* active index buffer */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->Ibuf);

    /* fill data */
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NoofI, I, GL_STATIC_DRAW);
    
    Pr->NumOfElements = NoofI;
  }
  else
    Pr->NumOfElements = NoofV;
  Pr->Trans = MatrIdentity();
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
  if (Pr->VA != 0)
  {
    glBindVertexArray(Pr->VA);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &Pr->VBuf);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &Pr->VA);
  }
  if (Pr->Ibuf != 0)
    glDeleteBuffers(1, &Pr->Ibuf);
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
  MATR M = MatrMulMatr3(Pr->Trans, World, YR4_RndMatrVP);

  glLoadMatrixf(M.M[0]);

  /* Draw all triangles */
  if (Pr->Ibuf != 0)
  {
    glBindVertexArray(Pr->VA);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->Ibuf);
    glDrawElements(GL_TRIANGLES, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
  }
  else
  {
    glBindVertexArray(Pr->VA);
    glDrawArrays(GL_TRIANGLES, 0, Pr->NumOfElements);
    glBindVertexArray(0);
  }
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
  INT i, j, m, n, noofv, noofi, size;
  DOUBLE t, p;
  yr4VERTEX *V;
  INT *Ind;

  memset(Pr, 0, sizeof(yr4PRIM));

  noofv = SplitW * SplitH;
  noofi = (SplitW - 1) * 2 * (SplitH - 1) * 3; 
  size = sizeof(yr4VERTEX) * noofv + sizeof(INT) * noofi;

  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + noofv);

  for (i = 0, t = 0, m = 0; i < SplitH; i++, t += PI / (SplitH - 1))
    for (j = 0, p = 0; j < SplitW; j++, p += 2 * PI / (SplitW - 1))
       V[m++].P = (VecSet(C.X + R * cos(p) * sin(t),
                              C.Y + R * cos(t),
                              C.Z + R * sin(p) * sin(t)));

  for (i = 0, m = 0, n = 0; i < SplitH - 1; i++, m++)
    for (j = 0; j < SplitW - 1; j++, m++)
    {
      Ind[n++] = m;
      Ind[n++] = m + 1;
      Ind[n++] = m + SplitW;

      Ind[n++] = m + SplitW;
      Ind[n++] = m + 1;
      Ind[n++] = m + SplitW + 1;
    }
  YR4_RndPrimCreate(Pr, V, noofv, Ind, noofi);
  free(V);
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
  INT i, j, m, n, noofv, noofi, size;
  DOUBLE t, p;
  yr4VERTEX *V;
  INT *Ind;

  memset(Pr, 0, sizeof(yr4PRIM));

  noofv = SplitW * SplitH;
  noofi = (SplitW - 1) * 2 * (SplitH - 1) * 3; 
  size = sizeof(yr4VERTEX) * noofv + sizeof(INT) * noofi;

  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + noofv);

  for (i = 0, t = -PI, m = 0; i < SplitH; i++, t += 2 * PI / (SplitH - 1))
    for (j = 0, p = 0; j < SplitW; j++, p += 2 * PI / (SplitW - 1))
       V[m++].P = (VecSet(C.X + (R + r * cos(t)) * cos(p),
                              C.Y + r * sin(t),
                              C.Z + (R + r * cos(t)) * sin(p)));

  for (i = 0, m = 0, n = 0; i < SplitH - 1; i++, m++)
    for (j = 0; j < SplitW - 1; j++, m++)
    {
      Ind[n++] = m;
      Ind[n++] = m + 1;
      Ind[n++] = m + SplitW;

      Ind[n++] = m + SplitW;
      Ind[n++] = m + 1;
      Ind[n++] = m + SplitW + 1;
    }
  YR4_RndPrimCreate(Pr, V, noofv, Ind, noofi);
  free(V);
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
  yr4VERTEX *V;
  INT *Ind;
  INT nv = 0, nf = 0, size;
  
  memset(Pr, 0, sizeof(yr4PRIM));

  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;
  
  /* Vertex and facet count */
  while (fgets(Buf, sizeof(Buf), F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      nf++;
  
  size = sizeof(yr4VERTEX) * nv + sizeof(INT) * (nf * 3);

  if ((V = malloc(size)) == NULL)
  {
    fclose(F);
    return FALSE;
  }

  memset(V, 0, size);
  Ind = (INT *)(V + nv);

  /* Load geometry data */
  rewind(F);
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf), F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;
      sscanf(Buf + 2, "%lf %lf %lf", &x, &y, &z);
      V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n1, n2, n3;

      sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3) == 3 ||
      sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
      sscanf(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
      sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3;

      Ind[nf++] = n1 - 1;
      Ind[nf++] = n2 - 1;
      Ind[nf++] = n3 - 1;
    }

  fclose(F);
  YR4_RndPrimCreate(Pr, V, nv, Ind, nf);
  free(V);
  return TRUE;
} /* end of 'YR4_RndPrimLoad' func */

/* END OF 'RNDPRIM.C' FILE */