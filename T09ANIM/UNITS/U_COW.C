/* FILE NAME: U_COW.C
 * PROGRAMMER: YR4
 * DATE: 09.06.2020
 * PURPOSE: 3D animation project.
 *          Cow creation unit.
 */

#include "../units.h"

/* Cow unit type */
typedef struct
{
  YR4_UNIT_BASE_FIELDS;
  yr4PRIM Cow;
} yr4UNIT_COW;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_Cow *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitInit( yr4UNIT_COW *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimLoad(&Uni->Cow, "cow.obj");
} /* End of 'YR4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_Cow *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitClose( yr4UNIT_COW *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimFree(&Uni->Cow);
} /* End of 'YR4_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_Cow *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitResponse( yr4UNIT_COW *Uni, yr4ANIM *Ani )
{
} /* End of 'YR4_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_Cow *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitRender( yr4UNIT_COW *Uni, yr4ANIM *Ani )
{
  MATR m;

  m = MatrMulMatr3(MatrScale(VecSet1(0.3)),
                   MatrTranslate(VecSet(-3, 0, 0)),
                   MatrRotateY(-90));
  YR4_RndPrimDraw(&Uni->Cow, m);
} /* End of 'YR4_UnitRender' function */

/* Cow unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (yr4UNIT *) pointer to created unit.
 */
yr4UNIT * YR4_UnitCreateCow( VOID )
{
  yr4UNIT *Uni;

  /* Memory allocation */
  if ((Uni = YR4_AnimUnitCreate(sizeof(yr4UNIT_COW))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)YR4_UnitInit;
  Uni->Close = (VOID *)YR4_UnitClose;
  Uni->Response = (VOID *)YR4_UnitResponse;
  Uni->Render = (VOID *)YR4_UnitRender;
  return Uni;
} /* End of 'YR4_AnimUnitCreate' function */

/* END OF 'U_COW' FILE */
