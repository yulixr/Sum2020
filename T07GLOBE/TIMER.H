/* YR4, 04.06.2020 */

#include <time.h>
#include <windows.h>

/* global timer variables */
extern DOUBLE GLB_Time;
extern DOUBLE GLB_DeltaTime;
extern DOUBLE GLB_FPS;
extern BOOL GLB_IsPause;

VOID GLB_TimerInit( VOID );
VOID GLB_TimerResponse( VOID );
