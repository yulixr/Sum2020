/* FILE NAME: RNDRES.C
 * PROGRAMMER: YR4
 * DATE: 13.06.2020
 * PURPOSE: 3D animation project.
 *          Textures file.
 */

#include "../rnd.h"


VOID YR4_RndResInit( VOID )
{
  YR4_RndShdInit();
  YR4_RndTexInit();
  YR4_RndMtlInit();
}

VOID YR4_RndResClose( VOID )
{
  YR4_RndShdClose();
  YR4_RndTexClose();
  YR4_RndMtlClose();
}

/* END OF 'RNDRES.C' FILE */
