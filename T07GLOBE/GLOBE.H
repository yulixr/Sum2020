/* YR4, 04.06.2020 */

#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include "MTH.H"

typedef double DBL;

#define GLOBE_W (25 * 2)
#define GLOBE_H (11 * 2)

VOID GlobeSet( DBL Xc, DBL Yc, DBL R );
VOID GlobeDraw( HDC hDC );
VEC VecRotateZ( VEC V, DBL Angle );
VEC VecRotateX( VEC V, DBL Angle );
VEC VecRotateY( VEC V, DBL Angle );
