/* FILE NAME: TIMER.C
 * PROGRAMMER: YR4
 * DATE: 09.06.2020
 * PURPOSE: 3D animation project.
 *          Timer implementation.
 */

#include "anim.h"

static UINT64
    StartTime, 
    OldTime, 
    PauseTime, 
    OldFPSTime,
    TimePerSec,
    FrameCount;

VOID YR4_TimerInit( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldFPSTime = t.QuadPart;
  FrameCount = 0;
  YR4_Anim.IsPause = FALSE;
  YR4_Anim.FPS = 30.0;
  PauseTime = 0;
}

VOID YR4_TimerResponse( VOID )
{
  LARGE_INTEGER t;
  QueryPerformanceCounter(&t);

  YR4_Anim.GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  YR4_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (YR4_Anim.IsPause)
  {
    YR4_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    YR4_Anim.DeltaTime = YR4_Anim.GlobalDeltaTime;
    YR4_Anim.Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCount++;
  if (t.QuadPart - OldFPSTime > TimePerSec)
  {
    YR4_Anim.FPS = FrameCount * TimePerSec / (DBL)(t.QuadPart - OldFPSTime);
    OldFPSTime = t.QuadPart;
    FrameCount = 0;
  }
  OldTime = t.QuadPart;
}
/* END OF "TIMER.C" FILE */
