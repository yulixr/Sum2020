/* YR4, 04.06.2020 */

#include <windows.h>
#include <math.h>
#include <stdlib.h>

typedef double DBL;

#define PI 3.14159265358
#define GLOBE_W (25 * 2)
#define GLOBE_H (11 * 2)


typedef struct
{
  DBL X, Y, Z; 
} VEC;

VOID GlobeSet( DBL Xc, DBL Yc, DBL R );
VOID GlobeDraw( HDC hDC );
