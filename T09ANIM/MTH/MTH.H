/* FILE NAME: MTH.H
 * PROGRAMMER: YR4
 * DATE: 06.06.2020
 * PURPOSE: 3D math implementation module.
 */

#ifndef __MTH_H_
#define __MTH_H_

#include <windows.h>
#include <math.h>

/* Pi math constant */
#define PI 3.14159265358979323846

/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

/* Base float and double types */
typedef double DBL;
typedef float FLT;

/* Random numbers functions */

/* Obtain random number in [0..1] range
 * ARGUMENTS: none
 * RETURNS:
 *    DBL value
 */
__inline DBL Rand0( VOID )
{
  return rand() / (DBL)RAND_MAX;
} /* end of rand0 func */
/* Obtain random number in [-1..1] range
 * ARGUMENTS: none
 * RETURNS:
 *    DBL value
 */
__inline DBL Rand1( VOID)
{
  return 2.0 * rand() / RAND_MAX - 1;
} /* end of rand1 func */

/* Vector structure */
typedef struct tagVEC
{
  FLT X, Y, Z;
} VEC;

/* vector2 structure */
typedef struct tagVEC2
{
  FLT X, Y;
} VEC2;

/* vector4 structure */
typedef struct tagVEC4
{
  FLT X, Y, Z, W;
} VEC4;

/* Matrix structure */
typedef struct tagMATR
{
  FLT M[4][4];
} MATR;

/* Math functions */

__inline FLT Power( FLT a, FLT b )
{
  return pow(a, b);
}
/* Set vector function.
 * ARGUMENTS:
 *   -Coordinates:
 *       FLT X, Y, Z;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSet( FLT X, FLT Y, FLT Z )
{
  VEC v = {X, Y, Z};

  return v;
} /* End of 'VecSet' function */

/* Set vector1 function.
 * ARGUMENTS:
 *   -Coordinates:
 *       FLT X;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSet1( FLT X )
{
  VEC v = {X, X, X};

  return v;
} /* End of 'VecSet' function */

/* Set vector function.
 * ARGUMENTS:
 *   -Coordinates:
 *       FLT X, Y;
 * RETURNS:
 *   (VEC2) result vector.
 */
__inline VEC2 Vec2Set( FLT X, FLT Y )
{
  VEC2 v = {X, Y};

  return v;
} /* End of 'Vec2Set' function */

/* Set vector function.
 * ARGUMENTS:
 *   -Coordinates:
 *       FLT X, Y, Z, W;
 * RETURNS:
 *   (VEC4) result vector.
 */
__inline VEC4 Vec4Set( FLT X, FLT Y, FLT Z, FLT W )
{
  VEC4 v = {X, Y, Z, W};

  return v;
} /* End of 'Vec4Set' function */



/* Add two vectors function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* end of func */

/* Subtraction two vectors function.
 * ARGUMENTS:
 *   - vectors to be subtracted:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} /* end of func */

/* Multiply vector to number func.
 * ARGUMENTS:
 *   - vector to be multiplied:
 *       VEC V1;
 *   - number:
 *       FLT N;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMulNum( VEC V1, FLT N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
} /* end of func */

/* Division vector to number func.
 * ARGUMENTS:
 *   - vector to be devisioned:
 *       VEC V1;
 *   - number:
 *       FLT N;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecDivNum( VEC V1, FLT N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
} /* end of func */

/* Made negativ vector func.
 * ARGUMENTS:
 *   - vector to be negative:
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecNeg( VEC V )             
{
  return VecSet(-V.X, -V.Y, -V.Z);
} /* end of func */

/* Dot product of two vectors func.
 * ARGUMENTS:
 *   - vector to be producted:
 *       VEC V1, V2;
 * RETURNS:
 *   (FLT) result.
 */
__inline FLT VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
} /* end of func */


/* Cross product of two vectors func.
 * ARGUMENTS:
 *   - vector to be producted:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
} /* end of func */

/* Length in square func.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 * RETURNS:
 *   (FLT) length.
 */
__inline FLT VecLen2( VEC V )
{
  return VecDotVec(V, V);
} /* end of func */

/* Length func.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 * RETURNS:
 *   (FLT) length.
 */
__inline FLT VecLen( VEC V )
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
} /* end of func */

/* Normalize vector func.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecNormalize( VEC V )  
{
  FLT len = VecDotVec(V, V);

  if (len != 1 && len != 0)
      len = sqrt(len), V.X /= len, V.Y /= len, V.Z /= len;
  return V;
} /* end of func */

/* transformations functions */

/* Transofrm point using matrix func.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) vector.
 */
__inline VEC PointTransform( VEC V, MATR M )
{
   return VecSet(V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0] + M.M[3][0], 
                 V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1] + M.M[3][1], 
                 V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2] + M.M[3][2]);
} /* end of func */

/* Transofrm vector using matrix func.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) vector.
 */
__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0], 
                V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1], 
                V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2]);
} /* end of func */

/* Multiply vec with matrix func.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) vector.
 */
__inline VEC VecMulMatr( VEC V, MATR M )
{
  FLT w = V.X * M.M[0][3] + V.Y * M.M[1][3] + V.Z * M.M[2][3] + M.M[3][3];
  return VecSet((V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0] + M.M[3][0]) / w, 
                (V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1] + M.M[3][1]) / w,
                (V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2] + M.M[3][2]) / w);
} /* end of func */

/* Matrix functions */

/* helpful macros */
#define MatrMulMatr2(A, B) MatrMulMatr(A, B)
#define MatrMulMatr3(A, B, C) MatrMulMatr(MatrMulMatr(A, B), C)
#define MatrMulMatr4(A, B, C, D) MatrMulMatr(MatrMulMatr(A, B), MatrMulMatr(C, D))

/* Unit matrix definition */ 
static MATR UnitMatrix =
{                  
  {                
    {1, 0, 0, 0},  
    {0, 1, 0, 0}, 
    {0, 0, 1, 0},  
    {0, 0, 0, 1}   
  }                
};

/* Set UnitMatrix func */
__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
} /* end of func */

/* set matrix 4x4 func */
__inline MATR SetMatr(FLT A00, FLT A01, FLT A02, FLT A03,
  FLT A10, FLT A11, FLT A12, FLT A13,
  FLT A20, FLT A21, FLT A22, FLT A23,
  FLT A30, FLT A31, FLT A32, FLT A33)
{
  MATR m;

  m.M[0][0] = A00;
  m.M[0][1] = A01;
  m.M[0][2] = A02;
  m.M[0][3] = A03;
  m.M[1][0] = A10;
  m.M[1][1] = A11;
  m.M[1][2] = A12;
  m.M[1][3] = A13;
  m.M[2][0] = A20;
  m.M[2][1] = A21;
  m.M[2][2] = A22;
  m.M[2][3] = A23;
  m.M[3][0] = A30;
  m.M[3][1] = A31;
  m.M[3][2] = A32;
  m.M[3][3] = A33;

  return m;
} /* end of func */

/* Setting translation matrix func.
 * ARGUMENTS:
 *   - vector:
 *       VEC T;
 * RETURNS:
 *   (MATR) matrix.
 */
__inline MATR MatrTranslate( VEC T )
{
  MATR m =
  {
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {T.X, T.Y, T.Z, 1}
    }
  };

  return m;
} /* end of func */

/* Setting scale matrix func.
 * ARGUMENTS:
 *   - vector:
 *       VEC S;
 * RETURNS:
 *   (MATR) matrix.
 */
__inline MATR MatrScale( VEC S )
{
  MATR m =
  {
    {
      {S.X, 0, 0, 0},
      {0, S.Y, 0, 0},
      {0, 0, S.Z, 0},
      {0, 0, 0, 1}
    }
  };

  return m;
} /* end of func */

/* Setting rotation around X/Y/Z axis func.
 * ARGUMENTS:
 *   -angle in degree
 *      FLT AngleInDegree;
 * RETURNS:
 *   (MATR) matrix.
 */
__inline MATR MatrRotateX( FLT AngleInDegree )
{
   return SetMatr(1, 0, 0, 0,
      0, cos(D2R(AngleInDegree)), sin(D2R(AngleInDegree)), 0,
      0, -sin(D2R(AngleInDegree)), cos(D2R(AngleInDegree)), 0,
      0, 0, 0, 1);
} /* end of func */

__inline MATR MatrRotateY( FLT AngleInDegree )
{
  return SetMatr(cos(D2R(AngleInDegree)), 0, -sin(D2R(AngleInDegree)), 0,
      0, 1, 0, 0,
      sin(D2R(AngleInDegree)), 0, cos(D2R(AngleInDegree)), 0,
      0, 0, 0, 1);
} /* end of func */

__inline MATR MatrRotateZ( FLT AngleInDegree )
{
  return SetMatr(cos(D2R(AngleInDegree)), sin(D2R(AngleInDegree)), 0, 0,
      -sin(D2R(AngleInDegree)), cos(D2R(AngleInDegree)), 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1);
} /* end of func */

/* Rotate vector around axis (by vector) func.
 * ARGUMENTS:
 *   -angle in degree
 *      FLT AngleInDegree;
 *   -vector:
 *      VEC V;
 * RETURNS:
 *   (MATR) matrix.
 */
__inline MATR MatrRotate( FLT AngleInDegree, VEC V )
{
  FLT
    a = D2R(AngleInDegree),
    c = cos(a),
    s = sin(a);
  VEC
    A = VecNormalize(V);
  MATR m =
  {
    {
      {c + A.X * A.X * (1 - c), A.X * A.Y * (1 - c) + A.Z * s, A.X * A.Z * (1 - c) - A.Y * s, 0},
      {A.X * A.Y * (1 - c) - A.Z * s, c + A.Y * A.Y * (1 - c), A.Z * A.Y * (1 - c) + A.X * s, 0},
      {A.X * A.Z * (1 - c) + A.Y * s, A.Y * A.Z * (1 - c) - A.X * s, c + A.Z * A.Z * (1 - c), 0},
      {0, 0, 0, 1}
    }
  };

  return m;
} /* end of func */

/* Transpose matrix func.
 * ARGUMENTS:
 *   - matrix:
 *      MATR M;
 * RETURNS:
 *   (MATR) matrix.
 */
__inline MATR MatrTranspose( MATR M )
{
  MATR M1;

  M1.M[0][0] = M.M[0][0];
  M1.M[0][1] = M.M[1][0];
  M1.M[0][2] = M.M[2][0];
  M1.M[0][3] = M.M[3][0];
  M1.M[1][0] = M.M[0][1];
  M1.M[1][1] = M.M[1][1];
  M1.M[1][2] = M.M[2][1];
  M1.M[1][3] = M.M[3][1];
  M1.M[2][0] = M.M[0][2];
  M1.M[2][1] = M.M[1][2];
  M1.M[2][2] = M.M[2][2];
  M1.M[2][3] = M.M[3][2];
  M1.M[3][0] = M.M[0][3];
  M1.M[3][1] = M.M[1][3];
  M1.M[3][2] = M.M[2][3];
  M1.M[3][3] = M.M[3][3];
  return M1;
} /* end of func */


/* Multiply matrix func.
 * ARGUMENTS:
 *   - matrix:
 *      MATR M1, M2;
 * RETURNS:
 *   (MATR) matrix.
 */
__inline MATR MatrMulMatr( MATR M1, MATR M2 ) 
{
  MATR r;
  INT i, j, k;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.M[i][j] = 0, k = 0; k < 4; k++)
        r.M[i][j] += M1.M[i][k] * M2.M[k][j];
  return r;
} /* end of func */

/* Determination Matrix 3x3 function */
__inline FLT MatrDeterm3x3( FLT A11, FLT A12, FLT A13,
                   FLT A21, FLT A22, FLT A23,
                   FLT A31, FLT A32, FLT A33 )
{
  return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 + 
         A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
} /* end of func */

/* Determination matrix func.
 * ARGUMENTS:
 *   - matrix:
 *      MATR M;
 * RETURNS:
 *   (FLT) result.
 */
__inline FLT MatrDeterm( MATR M )
{
  return
    M.M[0][0] * MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                              M.M[2][1], M.M[2][2], M.M[2][3],
                              M.M[3][1], M.M[3][2], M.M[3][3]) +
    -M.M[0][1] * MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                               M.M[2][0], M.M[2][2], M.M[2][3],
                               M.M[3][0], M.M[3][2], M.M[3][3]) +
    M.M[0][2] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                              M.M[2][0], M.M[2][1], M.M[2][3],
                              M.M[3][0], M.M[3][1], M.M[3][3]) +
    -M.M[0][3] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                               M.M[2][0], M.M[2][1], M.M[2][2],
                               M.M[3][0], M.M[3][1], M.M[3][2]);
} /* end of func */

/* Build inversed matrix func.
 * ARGUMENTS:
 *   - matrix:
 *      MATR M;
 * RETURNS:
 *   (MATR) matrix.
 */
__inline MATR MatrInverse( MATR M )
{
  MATR r;
  FLT det = MatrDeterm(M);

  if (det == 0)
      return UnitMatrix;

  r.M[0][0] = MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                   M.M[2][1], M.M[2][2], M.M[2][3],
                   M.M[3][1], M.M[3][2], M.M[3][3]);

  r.M[1][0] = -MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                             M.M[2][0], M.M[2][2], M.M[2][3],
                             M.M[3][0], M.M[3][2], M.M[3][3]);

  r.M[2][0] = MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                            M.M[2][0], M.M[2][1], M.M[2][3],
                            M.M[3][0], M.M[3][1], M.M[3][3]);

  r.M[3][0] = -MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                             M.M[2][0], M.M[2][1], M.M[2][2],
                             M.M[3][0], M.M[3][1], M.M[3][2]);

  r.M[0][1] = -MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                             M.M[2][1], M.M[2][2], M.M[2][3],
                             M.M[3][1], M.M[3][2], M.M[3][3]);

  r.M[1][1] = MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                            M.M[2][0], M.M[2][2], M.M[2][3],
                            M.M[3][0], M.M[3][2], M.M[3][3]);

  r.M[2][1] = -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                             M.M[2][0], M.M[2][1], M.M[2][3],
                             M.M[3][0], M.M[3][1], M.M[3][3]);

  r.M[3][1] = MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                            M.M[2][0], M.M[2][1], M.M[2][2],
                            M.M[3][0], M.M[3][1], M.M[3][2]);

  r.M[0][2] = MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                            M.M[1][1], M.M[1][2], M.M[1][3],
                            M.M[3][1], M.M[3][2], M.M[3][3]);

  r.M[1][2] = -MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                            M.M[1][0], M.M[1][2], M.M[1][3],
                            M.M[3][0], M.M[3][2], M.M[3][3]);

  r.M[2][2] = MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                            M.M[1][0], M.M[1][1], M.M[1][3],
                            M.M[3][0], M.M[3][1], M.M[3][3]);
      
  r.M[3][2] = -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                             M.M[1][0], M.M[1][1], M.M[1][2],
                             M.M[3][0], M.M[3][1], M.M[3][2]);

  r.M[0][3] = -MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                             M.M[1][1], M.M[1][2], M.M[1][3],
                             M.M[2][1], M.M[2][2], M.M[2][3]);

  r.M[1][3] = MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                            M.M[1][0], M.M[1][2], M.M[1][3],
                            M.M[2][0], M.M[2][2], M.M[2][3]);

  r.M[2][3] = -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                             M.M[2][0], M.M[2][1], M.M[2][3],
                             M.M[3][0], M.M[3][1], M.M[3][3]);

  r.M[3][3] =  MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                             M.M[1][0], M.M[1][1], M.M[1][2],
                             M.M[2][0], M.M[2][1], M.M[2][2]);

  r.M[1][0] /= det;
  r.M[2][0] /= det;
  r.M[3][0] /= det;
  r.M[1][1] /= det;
  r.M[2][1] /= det;
  r.M[3][1] /= det;
  r.M[1][2] /= det;
  r.M[2][2] /= det;
  r.M[3][2] /= det;
  r.M[1][3] /= det;
  r.M[2][3] /= det;
  r.M[3][3] /= det;
  r.M[0][0] /= det;
  r.M[0][1] /= det;
  r.M[0][2] /= det;
  r.M[0][3] /= det;
  return r;

} /* end of func */

/* Matrix look-at viewer setup function.
 * ARGUMENTS:
 *   - viewer position, look-at point, approximate up direction:
 *       VEC Loc, At, Up1;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));
  MATR m =
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };

  return m;
} /* End of 'MatrView' function */

/* Ortho matrix setup function.
 * ARGUMENTS:
 *   - Left, right, botton, top, near, far positions:
 *      FLT L, R, B, T, N, F;
 * RETURNS:
 *    (MATR) result matrix;
 */
__inline MATR MatrOrtho( FLT L, FLT R, FLT B, FLT T, FLT N, FLT F )
{
  MATR m =
  {
    {
      { 2 / (R - L), 0, 0, 0},
      { 0, 2 / (T - B), 0, 0},
      { 0, 0, - 2 / (F - N), 0},
      { - (R + L) / (R - L), - (T + B) / (T - B), - (F + N) / (F - N), 1}
    }
  };

  return m;
} /* End of 'MatrOrtho' function */

/* Frustum matrix setup function.
 * ARGUMENTS:
 *   - Left, right, botton, top, near, far positions:
 *      FLT L, R, B, T, N, F;
 * RETURNS:
 *    (MATR) result matrix;
 */
__inline MATR MatrFrustum( FLT L, FLT R, FLT B, FLT T, FLT N, FLT F )
{
  MATR m =
  {
    {
      { 2 * N / (R - L), 0, 0, 0},
      { 0, 2 * N / (T - B), 0, 0},
      { (R + L) / (R - L), (T + B) / (T - B), -(F + N) / (F - N), -1},
      { 0, 0, -2 * N * F / (F - N), 0}
    }
  };

  return m;
} /* End of 'MatrFrustum' function */

#endif /* __MTH_H_ */

/* END OF 'MTH.H' FILE */
