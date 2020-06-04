/* YR4, 04.06.2020 */
#include "GLOBE.H"
#include "TIMER.H"
#include <time.h>

VEC G[GLOBE_H][GLOBE_W];

/* Store coord syst center */
static INT CenterX, CenterY;

/* Rotate vector around z\y\x axis functions
 * ARGUMENTS:
 *   -vector to rotate
 *      VEC V;
 *   -rotation angle in degrees:
 *      DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector
 */
VEC VecRotateZ( VEC V, DBL Angle )
{
  VEC r;
  
  Angle *= PI / 180; 
  r.X = V.X * cos(Angle) - V.Y * sin(Angle);
  r.Y = V.X * sin(Angle) + V.Y * cos(Angle);
  r.Z = V.Z;

  return r;
}

VEC VecRotateY(VEC V, DOUBLE Angle)
{
    DOUBLE a = Angle * PI / 180, si = sin(a), co = cos(a);
    VEC r;

    r.X = V.X * co - V.Y * si;
    r.Y = V.X * si + V.Y * co;
    r.Z = V.Z;

    return r;
}

VEC VecRotateX(VEC V, DOUBLE Angle)
{
    DOUBLE a = Angle * PI / 180, si = sin(a), co = cos(a);
    VEC r;

    r.Y = V.Y  * co - V.Z * si ;
    r.Z = V.Y * si + V.Z * co;
    r.X = V.X;

    return r;
}

/* Fill geometry func
 * ARGUMENTS:
 *   -Coordinates
 *      DBL Xc, DBL Yc; 
 *   -rotation angle in degrees:
 *      DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector
 */
VOID GlobeSet( DBL Xc, DBL Yc, DBL R )
{
  INT i, j;
  DOUBLE t, p;

  CenterX = Xc, CenterY = Yc;
  for (i = 0, t = 0; i < GLOBE_H; i++, t += PI / (GLOBE_H - 1))
    for (j = 0, p = 0; j < GLOBE_W; j++, p += 2 * PI / (GLOBE_W - 1))
     { 
        G[i][j].X = R * cos(p) * sin(t);
        G[i][j].Y = R * cos(t);
        G[i][j].Z = R * sin(p) * sin(t);
     }
} /* end globeset func */

/* Draw Globe func
 * ARGUMENTS:
 *   -hDC
 *      HDC hDC;
 */
VOID GlobeDraw( HDC hDC )
{
  DBL s = 5, k;
  INT i, j;
  DBL t = (DBL)clock() / CLOCKS_PER_SEC;
  DBL z[GLOBE_H][GLOBE_W];
  static POINT pnt[GLOBE_H][GLOBE_W]; 

  /* initialize structures */
  for (i = 0; i < GLOBE_H; i++)
    for (j = 0; j < GLOBE_W; j++)
    {
       VEC 
         v1 = VecRotateY(G[i][j], 20 * GLB_Time),
         v = VecRotateX(v1, 10 * GLB_Time);
       
       z[i][j] = v.Z;
       pnt[i][j].x = CenterX + (INT)v.X,
       pnt[i][j].y = CenterY - (INT)v.Y; 
    }

  /* draw using dots */
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(0, 0, 0));
  for (i = 0; i < GLOBE_H; i++)
    for (j = 0; j < GLOBE_W; j++)
     if (z[i][j] > 0)
        //Ellipse(hDC, pnt[i][j].x - s, pnt[i][j].y - s, pnt[i][j].x + s, pnt[i][j].y + s); 
  
  /* linear draw */
  /*
  for (i = 0; i < GLOBE_H; i++)
  { 
    MoveToEx(hDC, pnt[i][0].x, pnt[i][0].y, NULL);
    for (j = 1; j < GLOBE_W; j++)
    {       
      LineTo(hDC, pnt[i][j].x, pnt[i][j].y);
    }
  } 
  for (j = 0; j < GLOBE_W; j++)
  { 
    MoveToEx(hDC, pnt[0][j].x, pnt[0][j].y, NULL);
    for (i = 1; i < GLOBE_H; i++)
    {       
      LineTo(hDC, pnt[i][j].x, pnt[i][j].y);
    }
  }*/

  /* polygon draw */
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SelectObject(hDC, GetStockObject(DC_PEN));
  srand(30);
  for (i = 0; i < GLOBE_H - 1; i++)
    for (j = 0; j < GLOBE_W - 1; j++)
      { 
        POINT ps[4];
        ps[0] = pnt[i][j]; 
        ps[1] = pnt[i][j + 1]; 
        ps[2] = pnt[i + 1][j + 1]; 
        ps[3] = pnt[i + 1][j]; 

        k = ((ps[0].x - ps[1].x) * (ps[0].y + ps[1].y) +
             (ps[1].x - ps[2].x) * (ps[1].y + ps[2].y) +
             (ps[2].x - ps[3].x) * (ps[2].y + ps[3].y) +
             (ps[3].x - ps[0].x) * (ps[3].y + ps[0].y));
        if (k >= 0)
        {
        SetDCBrushColor(hDC, RGB(100, 150, 0));
        SetDCPenColor(hDC, RGB(50, 50, 0));
        Polygon(hDC, ps, 4);
        }
      }
} /*end drawglobe func */
