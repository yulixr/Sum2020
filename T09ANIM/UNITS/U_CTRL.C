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
  HFONT hFnt, hFntOld;
  Uni->Speed = 6;
  Uni->AngleSpeed = 20;
  Uni->CamLoc = VecSet(0, 8, 8);
  hFnt = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, RUSSIAN_CHARSET, 
      OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_MODERN | VARIABLE_PITCH, "Mistral"); 

  hFntOld  = SelectObject(Ani->hDC, hFnt);
  wglUseFontBitmaps (Ani->hDC, 0, 256, 102);
  SelectObject(Ani->hDC, hFntOld);
  DeleteObject(hFnt);
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
  if (Ani->KeysClick['W'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (Ani->KeysClick['S'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  Uni->CamLoc = VecAddVec(Uni->CamLoc, 
    VecMulNum(VecNormalize(VecSubVec(VecSet(0, 0, 0), Uni->CamLoc)),
    Ani->GlobalDeltaTime * (Uni->Speed / 1.8) * Ani->Mdz));

  Uni->CamLoc = 
    VecAddVec(Uni->CamLoc, VecMulNum(VecNormalize(VecSubVec(VecSet(0, 0, 0), Uni->CamLoc)), Ani->GlobalDeltaTime * Uni->Speed *
    (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN])));
  
  Uni->CamLoc = 
    VecAddVec(Uni->CamLoc, VecMulNum(VecSet(1, 0, 0), Ani->GlobalDeltaTime * Uni->Speed *
    (Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT])));
  
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
  INT n;
  static CHAR Buf[100];
  MATR m = MatrOrtho(0, Ani->W - 1, Ani->H - 1, 0, -1, 1);
  n = sprintf(Buf, "FPS: %.3f", YR4_Anim.FPS);

 glLoadMatrixf(m.M[0]);
 glRasterPos2d(5 , 50);
 glListBase(102);
 glColor3d(0.01, 0.14, 0.21);
 glCallLists(n, GL_UNSIGNED_BYTE, Buf);
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
