/* FILE NAME: INPUT.C
 * PROGRAMMER: YR4
 * DATE: 09.06.2020
 * PURPOSE: 3D animation project.
 *          Input mouse, keyboard, joystick.
 */

#include "anim.h"

/* Keyboard initialization.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID YR4_AnimKeyboardInit( VOID )
{
  memset(YR4_Anim.Keys, 0, 256);
  memset(YR4_Anim.KeysOld, 0, 256);
  memset(YR4_Anim.KeysClick, 0, 256);
} /* end of func */

/* Keyboard response.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID YR4_AnimKeyboardResponse( VOID )
{
  INT i;

  GetKeyboardState(YR4_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    YR4_Anim.Keys[i] >>= 7;
    YR4_Anim.KeysClick[i] = YR4_Anim.Keys[i] && !YR4_Anim.KeysOld[i];  
  }
  memcpy(YR4_Anim.KeysOld, YR4_Anim.Keys, 256);
} /* end of func */

/* Mouse initialization.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID YR4_AnimMouseInit( VOID )
{
  YR4_Anim.Mx = 0;
  YR4_Anim.My = 0;
  YR4_Anim.Mz = 0;
  YR4_Anim.Mdx = 0;
  YR4_Anim.Mdy = 0; 
  YR4_Anim.Mdz = 0;
} /* end of func */

/* Mouse response.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID YR4_AnimMouseResponse( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(YR4_Anim.hWnd, &pt);

  YR4_Anim.Mdx = pt.x - YR4_Anim.Mx;
  YR4_Anim.Mdy = pt.y - YR4_Anim.My;
  YR4_Anim.Mdz = YR4_MouseWheel;
  YR4_Anim.Mz += YR4_MouseWheel;
  YR4_MouseWheel = 0;
  YR4_Anim.Mx = pt.x;
  YR4_Anim.My = pt.y;
} /* end of func */

/* Full initialization.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID YR4_AnimInputInit( VOID )
{
  YR4_AnimMouseInit();
  YR4_AnimKeyboardInit();
} /* end of func */

/* Full response.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID YR4_AnimInputResponse( VOID )
{
  YR4_AnimMouseResponse();
  YR4_AnimKeyboardResponse();
} /* end of func */

/* END OF 'INPUT.C' FILE */
