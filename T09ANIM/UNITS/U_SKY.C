/* FILE NAME: U_SKY.C
 * PROGRAMMER: YR4
 * DATE: 13.06.2020
 * PURPOSE: 3D animation project.
 *          Sky.
 */

#include "../units.h"

/* Grid unit type */
typedef struct
{
  YR4_UNIT_BASE_FIELDS;
  yr4PRIM Pr1;
} yr4UNIT_SKY;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_SKY *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitInit( yr4UNIT_SKY *Uni, yr4ANIM *Ani )
{
  yr4MATERIAL mtl;
  
  YR4_RndPrimCreateSphere(&Uni->Pr1, VecSet1(0), 270, 27, 13);
  mtl = YR4_RndMtlGetDef();
  mtl.Tex[0] = YR4_RndTexAdd("sky.bmp");
  mtl.ShdNo = YR4_RndShdAdd("SKY");
  mtl.Kd = VecSet1(0.9);
  Uni->Pr1.MtlNo = YR4_RndMtlAdd(&mtl); 
} /* End of 'YR4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_SKY *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitClose( yr4UNIT_SKY *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimFree(&Uni->Pr1);
} /* End of 'YR4_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_SKY *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitResponse( yr4UNIT_SKY *Uni, yr4ANIM *Ani )
{ 
} /* End of 'YR4_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_SKY *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitRender( yr4UNIT_SKY *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimDraw(&Uni->Pr1, MatrTranslate(VecSet(0, -10, 0)));
} /* End of 'YR4_UnitRender' function */

/* Cow unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (yr4UNIT *) pointer to created unit.
 */
yr4UNIT * YR4_UnitCreateSky( VOID )
{
  yr4UNIT *Uni;

  /* Memory allocation */
  if ((Uni = YR4_AnimUnitCreate(sizeof(yr4UNIT_SKY))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)YR4_UnitInit;
  Uni->Close = (VOID *)YR4_UnitClose;
  Uni->Response = (VOID *)YR4_UnitResponse;
  Uni->Render = (VOID *)YR4_UnitRender;
  return Uni;
} /* End of 'YR4_AnimUnitCreate' function */

/* END OF 'U_GRID.C' FILE */