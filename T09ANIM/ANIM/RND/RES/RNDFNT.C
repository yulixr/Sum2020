/* FILE NAME: RNDFNT.S
 * PROGRAMMER: YR4
 * DATE: 17.06.2020
 * PURPOSE: 3D animation project.
 *          Font file.
 */

#include "../rnd.h"
#include <stdio.h>
#include <string.h>

/* Current font description */

/* Font data */
static yr4FONT YR4_RndFntFont;

/* Font characters primitives */
static yr4PRIM YR4_RndFntChars[256];

/* Font material */
static INT YR4_RndFntMtlNo;

/* Load font from .G3DF file function.
 * ARGUMENTS:
 *   - font file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL YR4_RndFntLoad( CHAR *FileName )
{
  FILE *F;
  INT i;
  DWORD Sign, W, H, *tex;
  yr4VERTEX Chars[256][4];
  yr4MATERIAL mtl;

  if ((F = fopen(FileName, "rb")) == NULL)
   return FALSE;
  fread(&Sign, 4, 1, F);
  if (Sign != *(DWORD *)"G3DF")
  {
    fclose(F);
    return FALSE;
  }
  fread(&YR4_RndFntFont, sizeof(yr4FONT), 1, F);
  fread(&Chars, sizeof(yr4VERTEX), 4 * 256, F);
  fread(&W, 4, 1, F);
  fread(&H, 4, 1, F);

  mtl = YR4_RndMtlGetDef();
  strncpy(mtl.Name, FileName, YR4_STR_MAX - 1);
  if ((tex = malloc(W * H * 4)))
  {
    fread(tex, 4, W * H, F);
    mtl.Tex[0] = YR4_RndTexAddImg(FileName, W, H, 4, tex);
    free(tex);
  }
  mtl.ShdNo = YR4_RndShdAdd("FONT");
  YR4_RndFntMtlNo = YR4_RndMtlAdd(&mtl);

  for (i = 0; i < 256; i++)
  {
    YR4_RndPrimFree(&YR4_RndFntChars[i]);
    YR4_RndPrimCreate(&YR4_RndFntChars[i], Chars[i], 4, NULL, 0, YR4_RND_PRIM_TRISTRIP);
    YR4_RndFntChars[i].MtlNo = YR4_RndFntMtlNo;
  }

  fclose(F);
  return TRUE;
} /* End of 'YR4_RndFntLoad' function */

/* Init font subsystem function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID YR4_RndFntInit( VOID )
{
  YR4_RndFntLoad("BIN/FONTS/aabebas.g3df");
} /* End of 'YR4_RndFntInit' function */

/* Init font subsystem function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID YR4_RndFntClose( VOID )
{
  INT i;

  for (i = 0; i < 256; i++)
    YR4_RndPrimFree(&YR4_RndFntChars[i]);
  memset(YR4_RndFntChars, 0, sizeof(YR4_RndFntChars));
} /* End of 'YR4_RndFntInit' function */

/* Draw string function.
 * ARGUMENTS:
 *   - string to draw:
 *       CHAR *Str;
 * RETURNS: None.
 */
VOID YR4_RndFntDraw( CHAR *Str, VEC Pos, FLT Size, VEC Color )
{
  MATR s = MatrScale(VecSet(Size, Size, 1));
  FLT x = Pos.X;
  INT modes[2];

  glGetIntegerv(GL_POLYGON_MODE, modes);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  YR4_RndShdAddonV0 = Color;
  while (*Str != 0)
  {
    if (*Str == '\n')
      Pos.X = x, Pos.Y -= Size;
    else
      if (YR4_RndFntFont.AdvanceX[(BYTE)*Str] != 0)
      {
        YR4_RndFntChars[(BYTE)*Str].Trans = s;
        YR4_RndPrimDraw(&YR4_RndFntChars[(BYTE)*Str], MatrTranslate(Pos));
        Pos.X += YR4_RndFntFont.AdvanceX[(BYTE)*Str] * Size;
      }
    Str++;
  }
  glPolygonMode(GL_FRONT, modes[0]);
  glPolygonMode(GL_BACK, modes[1]);
} /* End of 'YR4_RndFntDraw' function */


/* END OF 'RNDFNT.C' FILE */
 