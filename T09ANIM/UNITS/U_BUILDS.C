                          /* FILE NAME: U_TEST.C
 * PROGRAMMER: YR4
 * DATE: 13.06.2020
 * PURPOSE: 3D animation project.
 *          Test.
 */

#include "../units.h"

/* Grid unit type */
typedef struct
{
  YR4_UNIT_BASE_FIELDS;
  yr4PRIMS Pan, Rock;
  VEC Trans[10];
} yr4UNIT_PANEL;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_PANEL *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitInit( yr4UNIT_PANEL *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimsLoad(&Uni->Pan, "BIN/MODELS/wood.g3dm");

} /* End of 'YR4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_PANEL *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitClose( yr4UNIT_PANEL *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimsFree(&Uni->Pan);
} /* End of 'YR4_UnitClose' function */

/* Unit inter frame events handle functio
n.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_PANEL *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitResponse( yr4UNIT_PANEL *Uni, yr4ANIM *Ani )
{ 

} /* End of 'YR4_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_PANEL *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitRender( yr4UNIT_PANEL *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimsDraw(&Uni->Pan, MatrMulMatr3(MatrTranslate(VecSet(-50, -4, -100)), MatrRotateY(30), MatrScale(VecSet1(0.4))));
  YR4_RndPrimsDraw(&Uni->Pan, MatrMulMatr3(MatrTranslate(VecSet(165, -15, -130)), MatrRotateY(-30), MatrScale(VecSet1(0.4))));
  YR4_RndPrimsDraw(&Uni->Pan, MatrMulMatr3(MatrTranslate(VecSet(-45, -21, -160)), MatrRotateY(90), MatrScale(VecSet1(0.4))));
  
} /* End of 'YR4_UnitRender' function */

/* Cow unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (yr4UNIT *) pointer to created unit.
 */
yr4UNIT * YR4_UnitCreatePanel( VOID )
{
  yr4UNIT *Uni;

  /* Memory allocation */
  if ((Uni = YR4_AnimUnitCreate(sizeof(yr4UNIT_PANEL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)YR4_UnitInit;
  Uni->Close = (VOID *)YR4_UnitClose;
  Uni->Response = (VOID *)YR4_UnitResponse;
  Uni->Render = (VOID *)YR4_UnitRender;
  return Uni;
} /* End of 'YR4_AnimUnitCreate' function */

/* END OF 'U_GRID.C' FILE */