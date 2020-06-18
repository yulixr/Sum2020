/* FILE NAME: U_VIRUS.C
 * PROGRAMMER: YR4
 * DATE: 18.06.2020
 * PURPOSE: 3D animation project.
 *          Test.
 */

#include "../units.h"

/* Virus unit type */
typedef struct
{
  YR4_UNIT_BASE_FIELDS;
  yr4PRIMS Vi;
  VEC Pos;
  FLT Scale;
} yr4UNIT_VIRUS;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_VIRUS *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitInit( yr4UNIT_VIRUS *Uni, yr4ANIM *Ani )
{
  yr4MATERIAL mtl;
  INT k = (INT)(Rand0() * 15);
  YR4_RndPrimsLoad(&Uni->Vi, "BIN/MODELS/virus.g3dm");
  mtl = YR4_RndMaterials[0];
  //mtl.Tex[0] = YR4_RndTexAdd("sars.bmp");
  mtl.Ka = MatLib[k].Ka;
  mtl.Kd = MatLib[k].Kd;
  mtl.Ks = MatLib[k].Ks;
  mtl.Ph = MatLib[k].Ph;
  Uni->Vi.Prims->MtlNo = YR4_RndMtlAdd(&mtl); 
  Uni->Pos = VecMulNum(VecSet(Rand1() * 15, Rand0() * 5, Rand1() * 14), 7);
  Uni->Scale = 2 + Rand0() * 4;
} /* End of 'YR4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_VIRUS *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitClose( yr4UNIT_VIRUS *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimsFree(&Uni->Vi);
} /* End of 'YR4_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_VIRUS *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitResponse( yr4UNIT_VIRUS *Uni, yr4ANIM *Ani )
{ 

} /* End of 'YR4_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       yr4UNIT_VIRUS *Uni;
 *   - animation context:
 *       yr4ANIM *Ani;
 * RETURNS: None.
 */
static VOID YR4_UnitRender( yr4UNIT_VIRUS *Uni, yr4ANIM *Ani )
{
  YR4_RndPrimsDraw(&Uni->Vi, MatrMulMatr4(MatrScale(VecSet1(Uni->Scale)), MatrTranslate(Uni->Pos), 
    MatrRotateY(Ani->Time * 4), MatrTranslate(VecSet(0, 2 * sin(Ani->Time * 2), 0))));
} /* End of 'YR4_UnitRender' function */

/* Cow unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (yr4UNIT *) pointer to created unit.
 */
yr4UNIT * YR4_UnitCreateVirus( VOID )
{
  yr4UNIT *Uni;

  /* Memory allocation */
  if ((Uni = YR4_AnimUnitCreate(sizeof(yr4UNIT_VIRUS))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)YR4_UnitInit;
  Uni->Close = (VOID *)YR4_UnitClose;
  Uni->Response = (VOID *)YR4_UnitResponse;
  Uni->Render = (VOID *)YR4_UnitRender;
  return Uni;
} /* End of 'YR4_AnimUnitCreate' function */

/* END OF 'U_GRID.C' FILE */