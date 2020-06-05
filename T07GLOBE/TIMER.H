/* YR4, 04.06.2020 */

#include <time.h>
#include <windows.h>

LONG StartTime, OldTime, PauseTime, OldFPSTime, FrameCount;
DOUBLE GLB_Time;
DOUBLE GLB_DeltaTime;
DOUBLE GLB_FPS;
BOOL GLB_IsPause;

VOID GLB_TimerInit( VOID );
VOID GLB_TimerResponse( VOID );
