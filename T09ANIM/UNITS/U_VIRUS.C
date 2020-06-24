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
  VEC Trans[120];
  VEC Scale[120]; 
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
  INT k = 10, i;
  YR4_RndPrimsLoad(&Uni->Vi, "BIN/MODELS/virus.g3dm");
  mtl = YR4_RndMaterials[0];
  mtl.Ka = MatLib[k].Ka;
  mtl.Kd = MatLib[k].Kd;
  mtl.Ks = MatLib[k].Ks;
  mtl.Ph = MatLib[k].Ph;
  mtl.ShdNo = YR4_RndShdAdd("VIRUS");
  Uni->Vi.Prims->MtlNo = YR4_RndMtlAdd(&mtl); 
  srand(30);
  for (i = 0; i < 35; i++)
  {
    Uni->Trans[i] = VecSet(Rand1() * 85, 8 + Rand0() * 30, Rand1() * 85);
    Uni->Scale[i] = VecSet1(2 + Rand0() * 4);
  }
   Uni->Vi.Prims[0].InstanceCnt = 35;
  // Uni->Pos = VecMulNum(VecSet(Rand1() * 15, Rand0() * 5, Rand1() * 14), 7);
  //Uni->Speed = 4 * Rand0() + 1.5;   
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

  INT id, loc;

  id = Uni->Vi.Prims[0].MtlNo;
  id = YR4_RndMaterials[id].ShdNo;
  id = YR4_RndShaders[id].ProgId;
  glUseProgram(id);

  if ((loc = glGetUniformLocation(id, "Trans[0]")) != -1)
    glUniform3fv(loc, 120, &Uni->Trans[0].X);
  if ((loc = glGetUniformLocation(id, "Scale[0]")) != -1)
    glUniform3fv(loc, 120, &Uni->Scale[0].X);
 
  YR4_RndPrimsDraw(&Uni->Vi, MatrIdentity());  
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