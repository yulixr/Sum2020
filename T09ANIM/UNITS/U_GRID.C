/* FILE NAME: U_GRID.C
 * PROGRAMMER: YR4
 * DATE: 09.06.2020
 * PURPOSE: 3D animation project.
 *          Hight map creation unit.
 */

#include "../units.h"
#define GRID_W 300
#define GRID_H 300

/* Grid unit type */
typedef struct
{
  YR4_UNIT_BASE_FIELDS;
  yr4PRIM Grid;
  yr4PRIMS City;
} yr4UNIT_GRID;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_GRID *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitInit( yr4UNIT_GRID *Uni, yr4ANIM *Ani )
{
  INT i, j;
  yr4VERTEX *V;
  yr4IMAGE img;
  INT k = 14;
  
  yr4MATERIAL mtl = YR4_RndMaterials[0];
  
  if (YR4_RndImgLoad(&img, "mount.bmp"))
  {
    if ((V = malloc(sizeof(yr4VERTEX) * img.W * img.H)) != NULL)
    {
      for (i = 0; i < img.H; i++)
        for (j = 0; j < img.W; j++)
        {
          INT c = img.PixelsC[i * img.W + j][1];

          V[i * img.W + j].P = VecSet(j - img.W / 2, 50 * c / 255.9, img.H / 2 - i);
          V[i * img.W + j].C = Vec4Set(1, 1, 1, 1);
          V[i * img.W + j].T.X = j / (img.W - 1.0);
          V[i * img.W + j].T.Y = i / (img.H - 1.0);
        }
        YR4_RndPrimCreateFromGrid(&Uni->Grid, V, img.W, img.H, TRUE);
        free(V);
    }
   YR4_RndImgFree(&img);
  }
  mtl = YR4_RndMtlGetDef();
  mtl.Tex[0] = YR4_RndTexAdd("mnt.bmp");
  Uni->Grid.MtlNo = YR4_RndMtlAdd(&mtl);  
} /* End of 'YR4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_GRID *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitClose( yr4UNIT_GRID *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimFree(&Uni->Grid);
} /* End of 'YR4_UnitClose' function */


/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_GRID *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitResponse( yr4UNIT_GRID *Uni, yr4ANIM *Ani )
{ 
} /* End of 'YR4_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_GRID *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitRender( yr4UNIT_GRID *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimDraw(&Uni->Grid, MatrMulMatr(MatrTranslate(VecSet(-5, -30, -5)), 
    MatrScale(VecSet1(0.4))));
} /* End of 'YR4_UnitRender' function */

/* Cow unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (yr4UNIT *) pointer to created unit.
 */
yr4UNIT * YR4_UnitCreateGrid( VOID )
{
  yr4UNIT *Uni;

  /* Memory allocation */
  if ((Uni = YR4_AnimUnitCreate(sizeof(yr4UNIT_GRID))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)YR4_UnitInit;
  Uni->Close = (VOID *)YR4_UnitClose;
  Uni->Response = (VOID *)YR4_UnitResponse;
  Uni->Render = (VOID *)YR4_UnitRender;
  return Uni;
} /* End of 'YR4_AnimUnitCreate' function */

/* END OF 'U_GRID.C' FILE */