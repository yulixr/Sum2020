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
  DBL
    Dist, /* camera distance from origin */
    Elevator, /* Elevator angle */
    Azimuth; /* Azimuth angle */

  yr4PRIM Axes;
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
  yr4MATERIAL mtl;
  yr4VERTEX V[] = 
  {
    {{0, 0, 0}, {0, 0}, {0, 0, 0}, {1, 0, 0, 1}},
    {{300, 0, 0}, {0, 0}, {0, 0, 0}, {1, 0, 0, 1}},
    {{0, 0, 0}, {0, 0}, {0, 0, 0}, {0, 1, 0, 1}},
    {{0, 300, 0}, {0, 0}, {0, 0, 0}, {0, 1, 0, 1}},
    {{0, 0, 0}, {0, 0}, {0, 0, 0}, {0, 0, 1, 1}},
    {{0, 0, 300}, {0, 0}, {0, 0, 0}, {0, 0, 1, 1}}
  };
  YR4_RndPrimCreate(&Uni->Axes, V, 6, NULL, 0, YR4_RND_PRIM_LINES);
  mtl = YR4_RndMtlGetDef();
  mtl.ShdNo = YR4_RndShdAdd("AXES");
  Uni->Axes.MtlNo = YR4_RndMtlAdd(&mtl);

  Uni->Azimuth = 20;
  Uni->Elevator = 1;
  Uni->Dist = 8;
  //Uni->CamLoc = VecSet(0, 8, 8);
  hFnt = CreateFont(36, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, RUSSIAN_CHARSET, 
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
  FLT Wp, Hp, sx, sy;
  VEC dv;
  if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;
  if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['W'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['S'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  Wp = YR4_RndProjSize;
  Hp = YR4_RndProjSize;

  if (Ani->W >= Ani->H)
    Wp *= (FLT)Ani->W / Ani->H;
  else
    Hp *= (FLT)Ani->H / Ani->W;

  sx = Wp / Ani->W * Uni->Dist / YR4_RndProjDist;
  sy = Hp / Ani->H * Uni->Dist / YR4_RndProjDist;

  dv = VecAddVec(VecMulNum(YR4_RndCamRight, -sx * Ani->Keys[VK_RBUTTON] * Ani->Mdy),
                 VecMulNum(YR4_RndCamUp, sy * Ani->Keys[VK_RBUTTON] * Ani->Mdx));
  YR4_RndCamAt = VecAddVec(YR4_RndCamAt, dv);
  YR4_RndCamLoc = VecAddVec(YR4_RndCamLoc, dv);

  Uni->Dist += Ani->GlobalDeltaTime * (-2.5 * Ani->Mdz + 8 * (1 + Ani->Keys[VK_SHIFT] * 30) * (Ani->Keys[VK_NEXT] - Ani->Keys[VK_PRIOR]));
  Uni->Azimuth += Ani->GlobalDeltaTime * (-26 * Ani->Keys[VK_LBUTTON] * Ani->Mdx + 50 * (Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT]));
  Uni->Elevator += Ani->GlobalDeltaTime * (-26 * Ani->Keys[VK_LBUTTON] * Ani->Mdy + 47 * (Ani->Keys[VK_DOWN] - Ani->Keys[VK_UP]));

  if (Uni->Elevator > 89.99)
    Uni->Elevator = 89.99;
  else if (Uni->Elevator < -89.99)
    Uni->Elevator = -89.99;

  if (Uni->Dist < 0.0002)
    Uni->Dist = 0.0002;
  if (Ani->IsPause)
  YR4_RndCamSet(PointTransform(VecSet(0, 0, Uni->Dist),
                  MatrMulMatr3(MatrRotateX(Uni->Elevator),
                              MatrRotateY(Uni->Azimuth),
                              MatrTranslate(YR4_RndCamAt))),
                YR4_RndCamAt,
                VecSet(0, 1, 0));
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
  MATR m1, m2, m3;
  static CHAR Buf[1000];

  YR4_RndFntDraw("BIG MOUNTAIN", VecSet(-25, 20,-10), 4, VecSet(1, 0, 1)); 
  m1 = YR4_RndMatrView;
  m2 = YR4_RndMatrProj;
  m3 = YR4_RndMatrVP;

  YR4_RndMatrView = MatrIdentity();
  YR4_RndMatrVP = YR4_RndMatrProj = MatrOrtho(0, (Ani->W - 1) / 30.0, -(Ani->H - 1) / 30.0, 0, -1, 1);

  sprintf(Buf,
    "FPS: %.3f\n"
    "Renderer: %s\n"
    "Vendor: %s\n"
    "Version: %s\n"
    "GLSL ver: %s",
    Ani->FPS, glGetString(GL_RENDERER), glGetString(GL_VENDOR), glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
  YR4_RndFntDraw(Buf, VecSet1(0), 1, VecSet1(1));

  YR4_RndMatrView = m1;
  YR4_RndMatrProj = m2;
  YR4_RndMatrVP = m3;

  glLineWidth(4);
  YR4_RndPrimDraw(&Uni->Axes, MatrIdentity());
  glLineWidth(1);
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
