/* FILE NAME: RNDMTL.C
 * PROGRAMMER: YR4
 * DATE: 13.06.2020
 * PURPOSE: 3D animation project.
 *          Materials file.
 */

#include "../rnd.h"
#include <string.h>

/* Material stock */
yr4MATERIAL YR4_RndMaterials[YR4_MAX_MATERIALS]; /* Array of materials */
INT YR4_RndMaterialsSize;                        /* Materials array store size */

/* Materials support initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID YR4_RndMtlInit( VOID )
{
  yr4MATERIAL mtl;
  INT i;

  strncpy(mtl.Name, "Default", YR4_STR_MAX - 1);

  memset(YR4_RndMaterials, 0, sizeof(YR4_RndMaterials));
  memset(&mtl, 0, sizeof(yr4MATERIAL));
  mtl.Ka = VecSet1(0.1);
  mtl.Kd = VecSet1(0.8);
  mtl.Ks = VecSet1(0.2);
  mtl.Ph = 100;
  mtl.Trans = 1;
  mtl.ShdNo = YR4_RndShdAdd("DEFAULT");
  for (i = 0; i < 8; i++)
    mtl.Tex[i] = -1;
  YR4_RndMaterialsSize = 0;
  YR4_RndMtlAdd(&mtl);
} /* End of 'YR4_RndMtlInit' function */

VOID YR4_RndMtlClose( VOID )
{
  YR4_RndMaterialsSize = 0;
}

/* Add new material to stock function.
 * ARGUMENTS:
 *   - material description structure pointer:
 *       yr4MATERIAL *Mtl;
 * RETURNS:
 *   (INT) added material stock index.
 */
INT YR4_RndMtlAdd( yr4MATERIAL *Mtl )
{
  if (YR4_RndMaterialsSize >= YR4_MAX_MATERIALS)
    return -1;
  YR4_RndMaterials[YR4_RndMaterialsSize] = *Mtl;
  return YR4_RndMaterialsSize++;
} /* End of 'YR4_RndMtlAdd' function */

/* Add new material to stock function.
 * ARGUMENTS:
 *   - material table number:
 *       INT MtlNo;
 * RETURNS:
 *   (INT) applied material shader program Id.
 */
INT YR4_RndMtlApply( INT MtlNo )
{
  INT prg, loc, i;
  yr4MATERIAL *mtl;

  /* Set material pointer */
  if (MtlNo < 0 || MtlNo >= YR4_RndMaterialsSize)
    MtlNo = 0;
  mtl = &YR4_RndMaterials[MtlNo];

  /* Set program Id */
  prg = mtl->ShdNo;
  if (prg < 0 || prg >= YR4_RndShaderSize)
    prg = 0;
  prg = YR4_RndShaders[prg].ProgId;

  glUseProgram(prg);
  if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);
  if ((loc = glGetUniformLocation(prg, "Trans")) != -1)
    glUniform1f(loc, mtl->Trans);

  /* Textures handle */
  for (i = 0; i < 8; i++)
  {
    CHAR tname[] = "IsTexture0";

    /* Set texture presence flag */
    tname[9] = '0' + i;
    if (mtl->Tex[i] != -1)
    {
      if ((loc = glGetUniformLocation(prg, "Texture0")) != -1)
        glUniform1f(loc, 0);
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, YR4_RndTextures[mtl->Tex[i]].TexId);
    }
    if ((loc = glGetUniformLocation(prg, tname)) != -1)
      glUniform1i(loc, mtl->Tex[i] != -1);
  }      
  return prg;
} /* End of 'YR4_RndMtlApply' function */

/* END OF 'RNDMTL.C' FILE */