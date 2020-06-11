/* FILE NAME: UNIT.C
 * PROGRAMMER: YR4
 * DATE: 09.06.2020
 * PURPOSE: 3D animation project.
 *          Base unit functions.
 */

#include "../units.h"
/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitInit( yr4UNIT *Uni, yr4ANIM *Ani )
{
} /* End of 'YR4_UnitInit' function */
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitClose( yr4UNIT *Uni, yr4ANIM *Ani )
{
} /* End of 'YR4_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitResponse( yr4UNIT *Uni, yr4ANIM *Ani )
{
} /* End of 'YR4_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitRender( yr4UNIT *Uni, yr4ANIM *Ani )
{
} /* End of 'YR4_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (yr4UNIT *) pointer to created unit.
 */
yr4UNIT * YR4_AnimUnitCreate( INT Size )
{
  yr4UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(yr4UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);

  /* Setup unit methods */
  Uni->Init = YR4_UnitInit;
  Uni->Close = YR4_UnitClose;
  Uni->Response = YR4_UnitResponse;
  Uni->Render = YR4_UnitRender;

  return Uni;
} /* End of 'YR4_AnimUnitCreate' function */

/* END OF 'UNIT.C' FILE */
