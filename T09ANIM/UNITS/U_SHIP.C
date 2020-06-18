/* FILE NAME: U_SHIP.C
 * PROGRAMMER: YR4
 * DATE: 16.06.2020
 * PURPOSE: 3D animation project.
 *          Test.
 */

#include "../units.h"

/* Grid unit type */
typedef struct
{
  YR4_UNIT_BASE_FIELDS;
  yr4PRIMS Pr;
  VEC Pos, CamPos;
  FLT Head;
  FLT Speed;
} yr4UNIT_SHIP;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_SHIP *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitInit( yr4UNIT_SHIP *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimsLoad(&Uni->Pr, "BIN/MODELS/inj.g3dm");
 
  Uni->CamPos = VecSet(20, 10, 13);
  Uni->Pr.Trans = MatrScale(VecSet1(0.06));
} /* End of 'YR4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_SHIP *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitClose( yr4UNIT_SHIP *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimsFree(&Uni->Pr);
} /* End of 'YR4_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_SHIP *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitResponse( yr4UNIT_SHIP *Uni, yr4ANIM *Ani )
{ 
  VEC p;
  FLT t;
  if (!Ani->IsPause && Ani->KeysClick[VK_SPACE])
  {
    Uni->Speed = 0;
    Uni->Pos = VecSet1(0);
    Uni->CamPos = VecSet(20, 10, 13);
  }
  if (Ani->IsPause)
  {
    Ani->DeltaTime = 0;
    Uni->Speed = 0;
  }
  if (!Ani->IsPause)
  {
  Uni->Speed += !Ani->Keys[VK_SHIFT] * (1 + Ani->Keys[VK_CONTROL] * 3) * (Ani->Keys['W'] - Ani->Keys['S']) * 0.04 * Ani->DeltaTime;
  Uni->Head += !Ani->Keys[VK_SHIFT] * (Ani->Keys['A'] - Ani->Keys['D']) * 37 * Ani->DeltaTime;
  Uni->Pos.Y += (Ani->Keys[VK_ADD] - Ani->Keys[VK_SUBTRACT]) * 5 * Ani->DeltaTime;
  Uni->Pos = VecAddVec(Uni->Pos,
    VecMulNum(VectorTransform(VecSet(0, 0, -1), MatrRotateY(Uni->Head)), Uni->Speed));
 
  p = VecAddVec(Uni->Pos, VectorTransform(VecSet(1, 4, 10), MatrRotateY(Uni->Head)));
  Uni->CamPos = VecAddVec(Uni->CamPos, VecMulNum(VecSubVec(p, Uni->CamPos), Ani->DeltaTime));
  YR4_RndCamSet(Uni->CamPos,
    Uni->Pos, VecSet(0, 1, 0));
  }
  p = VecDivNum(VecAddVec(Uni->Pr.Prims[9].MinBB, Uni->Pr.Prims[9].MaxBB), 2);
  Uni->Pr.Prims[9].Trans = Uni->Pr.Prims[7].Trans =
    MatrMulMatr(MatrTranslate(VecSet1(0)), MatrTranslate(VecSet(0, 0, sin(Ani->Time * 6) * 5)));
 

} /* End of 'YR4_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_SHIP *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitRender( yr4UNIT_SHIP *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimsDraw(&Uni->Pr, 
    MatrMulMatr3(MatrRotateY(Uni->Head), MatrRotateZ(Uni->Head / 16.0),
    MatrTranslate(Uni->Pos)));
  /*
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  YR4_RndPrimsDraw(&Uni->Pr, 
    MatrMulMatr(MatrTranslate(VecSet(0, 1, 0)), MatrRotateY(0)));
  glCullFace(GL_BACK);
  YR4_RndPrimsDraw(&Uni->Pr, 
    MatrMulMatr(MatrTranslate(VecSet(0, 1, 0)), MatrRotateY(0)));
  glDisable(GL_CULL_FACE); */
} /* End of 'YR4_UnitRender' function */

/* Cow unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (yr4UNIT *) pointer to created unit.
 */
yr4UNIT * YR4_UnitCreateShip( VOID )
{
  yr4UNIT *Uni;

  /* Memory allocation */
  if ((Uni = YR4_AnimUnitCreate(sizeof(yr4UNIT_SHIP))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)YR4_UnitInit;
  Uni->Close = (VOID *)YR4_UnitClose;
  Uni->Response = (VOID *)YR4_UnitResponse;
  Uni->Render = (VOID *)YR4_UnitRender;
  return Uni;
} /* End of 'YR4_AnimUnitCreate' function */

/* END OF 'U_GRID.C' FILE */