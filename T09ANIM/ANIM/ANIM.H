/* FILE NAME: ANIM.H
 * PROGRAMMER: YR4
 * DATE: 09.06.2020
 * PURPOSE: 3D animation project.
 *          Declarations for ANIM module.
 */


#ifndef __ANIM_H_
#define __ANIM_H_

#include "rnd/rnd.h"
#include "snd/snd.h"

#define YR4_MAX_UNITS 2000

#define YR4_UNIT_BASE_FIELDS \
  VOID (*Init)( yr4UNIT *Uni, yr4ANIM *Ani ); \
  VOID (*Close)( yr4UNIT *Uni, yr4ANIM *Ani ); \
  VOID (*Response)( yr4UNIT *Uni, yr4ANIM *Ani ); \
  VOID (*Render)( yr4UNIT *Uni, yr4ANIM *Ani )


typedef struct tagyr4UNIT yr4UNIT;
typedef struct tagyr4ANIM
{
  HWND hWnd;
  HDC hDC;
  INT W, H;

  yr4UNIT *Units[YR4_MAX_UNITS];
  INT NumOfUnits;

  DBL 
    GlobalTime, GlobalDeltaTime,
    Time, DeltaTime,
    FPS;
  BOOL
    IsPause;

  BYTE KeysClick[256], Keys[256], KeysOld[256];

  BYTE
    JBut[32], JButClick[32];
  INT JPov;
  DBL
    JX, JY, JZ, JR;

  INT Mx, My, Mz, Mdx, Mdy, Mdz;
} yr4ANIM;

extern yr4ANIM YR4_Anim;
extern INT YR4_MouseWheel;

struct tagyr4UNIT
{
  YR4_UNIT_BASE_FIELDS;
};

VOID YR4_TimerInit( VOID );
VOID YR4_TimerResponse( VOID );

VOID YR4_AnimClose( VOID );
VOID YR4_AnimRender( VOID );
VOID YR4_AnimAddUnit( yr4UNIT *Uni );
VOID YR4_AnimCopyFrame( VOID );
VOID YR4_AnimEnd( VOID );
VOID YR4_AnimResize( INT w, INT h );
VOID YR4_AnimInit ( HWND hWnd );
yr4UNIT * YR4_AnimUnitCreate( INT Size );
VOID YR4_AnimFlipFullScreen( HWND hWnd );

VOID YR4_AnimInputResponse( VOID );
VOID YR4_AnimInputInit( VOID );

#endif /* __ANIM_H_ */
/* END OF "ANIM.H" FILE */