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
  if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;
  if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['W'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['S'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  Uni->Dist += Ani->GlobalDeltaTime * (-2.5 * Ani->Mdz + 8 * (1 + Ani->Keys[VK_SHIFT] * 30) * (Ani->Keys[VK_NEXT] - Ani->Keys[VK_PRIOR]));
  Uni->Azimuth += Ani->GlobalDeltaTime * (-30 * Ani->Keys[VK_LBUTTON] * Ani->Mdx + 50 * (Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT]));
  Uni->Elevator += Ani->GlobalDeltaTime * (-30 * Ani->Keys[VK_LBUTTON] * Ani->Mdy + 47 * (Ani->Keys[VK_DOWN] - Ani->Keys[VK_UP]));
  Uni->Dist += Ani->GlobalDeltaTime * 6 * (Ani->Keys[VK_SPACE] - Ani->Keys[VK_TAB]);

  if (Uni->Elevator > 89.99)
    Uni->Elevator = 89.99;
  else if (Uni->Elevator < -89.99)
    Uni->Elevator = -89.99;

  if (Uni->Dist < 0.0002)
    Uni->Dist = 0.0002;
  if (Ani->IsPause)
  YR4_RndCamSet(PointTransform(VecSet(0, 0, Uni->Dist),
                  MatrMulMatr(MatrRotateX(Uni->Elevator),
                              MatrRotateY(Uni->Azimuth))),
                VecSet(0, 0, 0),
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
  INT n[10], i;

  MATR m = MatrOrtho(0, Ani->W - 1, Ani->H - 1, 0, -1, 1);

  static CHAR Buf[10][100];

  n[0] = sprintf(Buf[0], "FPS: %.3f", Ani->FPS);
  n[1] = sprintf(Buf[1], "Renderer: %s", glGetString(GL_RENDERER));
  n[2] = sprintf(Buf[2], "Vendor: %s", glGetString(GL_VENDOR));
  n[3] = sprintf(Buf[3], "Version: %s", glGetString(GL_VERSION));
  n[4] = sprintf(Buf[4], "GLSL ver: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glUseProgram(0);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glLoadMatrixf(m.M[0]);
  glListBase(102);

  for (i = 0; i < 5; i++)
  {
    glRasterPos2d(10, 47 * (i + 1));
    glColor3d(0.07, 0.01, 0.13);
    glCallLists(n[i], GL_UNSIGNED_BYTE, Buf[i]);

    glRasterPos3d(10 + 3, 47 * (i + 1) + 3, -0.1);
    glColor3d(0.93, 0.85, 1);
    glCallLists(n[i], GL_UNSIGNED_BYTE, Buf[i]);
  }
  glPopAttrib();  

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
