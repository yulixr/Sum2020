/* FILE NAME: U_CTRL.C
 * PROGRAMMER: YR4
 * DATE: 09.06.2020
 * PURPOSE: 3D animation project.
 *          Control unit.
 */
#include <stdio.h>
#include "../units.h"

/* Control unit type */
typedef struct
{
  YR4_UNIT_BASE_FIELDS;
  INT Speed;
  DBL AngleSpeed;
  VEC CamLoc;
} yr4UNIT_CTRL;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_Text *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitInit( yr4UNIT_CTRL *Uni, yr4ANIM *Ani )
{
  Uni->Speed = 6;
  Uni->AngleSpeed = 20;
  Uni->CamLoc = VecSet(0, 8, 8);
} /* End of 'YR4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_Text *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitClose( yr4UNIT_CTRL *Uni, yr4ANIM *Ani )
{
} /* End of 'YR4_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_Text *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitResponse( yr4UNIT_CTRL *Uni, yr4ANIM *Ani )
{ 
  if (Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;

  Uni->CamLoc = VecAddVec(Uni->CamLoc, 
    VecMulNum(VecNormalize(VecSubVec(VecSet(0, 0, 0), Uni->CamLoc)),
    Ani->GlobalDeltaTime * (Uni->Speed / 4.0) * Ani->Mdz));

  Uni->CamLoc = 
    VecAddVec(Uni->CamLoc, VecMulNum(VecNormalize(VecSubVec(VecSet(0, 0, 0), Uni->CamLoc)), Ani->GlobalDeltaTime * Uni->Speed *
    (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN])));
  
  Uni->CamLoc = PointTransform(Uni->CamLoc, 
    MatrRotateY(Ani->Keys[VK_LBUTTON] * Ani->GlobalDeltaTime * Uni->AngleSpeed * Ani->Mdx)); 
  YR4_RndCamSet(Uni->CamLoc, VecSet(0, 0, 0), VecSet(0, 1, 0));
} /* End of 'YR4_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_Text *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitRender( yr4UNIT_CTRL *Uni, yr4ANIM *Ani )
{  
  static CHAR Buf[100];

  SetTextColor(YR4_hRndDCFrame, RGB(110, 57, 0));
  TextOut(YR4_hRndDCFrame, 8, 18, Buf, sprintf(Buf, "FPS: %.3f", YR4_Anim.FPS));
} /* End of 'YR4_UnitRender' function */

/* Text unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (yr4UNIT *) pointer to created unit.
 */
yr4UNIT * YR4_UnitCreateCtrl( VOID )
{
  yr4UNIT *Uni;

  /* Memory allocation */
  if ((Uni = YR4_AnimUnitCreate(sizeof(yr4UNIT_CTRL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)YR4_UnitInit;
  Uni->Close = (VOID *)YR4_UnitClose;
  Uni->Response = (VOID *)YR4_UnitResponse;
  Uni->Render = (VOID *)YR4_UnitRender;
  return Uni;
}

/* END OF 'U_CTRL.C' FILE */
