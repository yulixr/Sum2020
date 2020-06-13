/* FILE NAME: U_BBALL.C
 * PROGRAMMER: YR4
 * DATE: 09.06.2020
 * PURPOSE: 3D animation project.
 *          Ball creation unit.
 */

#include "../units.h"

typedef struct
{
  YR4_UNIT_BASE_FIELDS;
  VEC Pos;
  DBL Shift, Scale;
  yr4PRIM Ball;
} yr4UNIT_BALL;

/* Bounce ball unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_BALL *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitInit( yr4UNIT_BALL *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimCreateSphere(&Uni->Ball, VecSet(0, 0, 0), 1, 18, 10);
  Uni->Pos = VecMulNum(VecSet(Rand1(), 0, Rand1()), 7); 
  Uni->Scale = 1 + Rand1() * 0.21;
} /* End of 'YR4_UnitInit' function */

/* Bounce ball unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_BALL *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitResponse( yr4UNIT_BALL *Uni, yr4ANIM *Ani )
{
} /* End of 'YR4_UnitResponse' function */

/* Bounce ball unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_BALL *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */           
static VOID YR4_UnitRender( yr4UNIT_BALL *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimDraw(&Uni->Ball, MatrMulMatr3(MatrTranslate(Uni->Pos), 
    MatrTranslate(VecSet(0, 2 * sin(3 * Ani->Time), 0)), 
    MatrScale(VecSet1(Uni->Scale))));
} /* End of 'YR4_UnitRender' function */

/* Unit ball close function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_BALL *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitClose( yr4UNIT_BALL *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimFree(&Uni->Ball);
} /* End of 'YR4_UnitClose' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (yr4UNIT *) pointer to created unit.
 */
yr4UNIT * YR4_UnitCreateBall( VOID )
{
  yr4UNIT_BALL *Uni;

  if ((Uni = (yr4UNIT_BALL *)YR4_AnimUnitCreate(sizeof(yr4UNIT_BALL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)YR4_UnitInit;
  Uni->Response = (VOID *)YR4_UnitResponse;
  Uni->Render = (VOID *)YR4_UnitRender;
  Uni->Close = (VOID *)YR4_UnitClose;

  return (yr4UNIT *)Uni;
} /* End of 'YR4_UnitCreateBall' function */

/* END OF 'U_BBALL.C' FILE */
