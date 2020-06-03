/* FILE NAME: T06DETG.C
   PROGRAMMER: YR4
   DATE: 03.01.2020
   PURPOSE: Count matrix determinant by Gauss method
*/

#include <windows.h>
#include <stdio.h>
#include <math.h>

#define MAX 10
DOUBLE A[MAX][MAX];
INT N;
DOUBLE Det;

/* swap func */
VOID Swap( DOUBLE *A, DOUBLE *B )
{
  DOUBLE tmp = *A;
  *A = *B;
  *B = tmp;
} /* end swap func */

/* load matrix from file */
BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;
  
  N = 0;
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  fscanf(F, "%d", &N);
  if (N < 0)
    N = 0;
  else if (N > MAX)
    N = MAX;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);

  fclose(F);
  return TRUE;
} /* end loadmatrix func */


/* Count Determinant by Gauss func */
VOID Gauss( VOID )
{
  INT max_row, max_col, i, x, j, y, k;
  DOUBLE coef;

  Det = 1.0;

  for (i = 0; i < N; i++)
  {
    max_col = max_row = i;
    for (x = i; x < N; x++)
      for (y = i; y < N; y++)
        if (fabs(A[x][y]) > fabs(A[max_row][max_col]))
          max_col = x, max_row = y;
    if (A[max_row][max_col] == 0)
    {
      Det = 0;
      break;
    }
    if (max_row != i)
    {
      for (x = i; x < N; x++)
        Swap(&(A[i][x]), &(A[max_row][x]));
      Det = -Det;
    }
    if (max_col != i)
    {
      for (y = 0; y < N; y++)
        Swap(&A[y][i], &A[y][max_col]);
      Det = -Det;
    }
    for (x = i + 1; x < N; x++)
    {
      coef = A[x][i] / A[i][i];
      A[x][i] = 0;
      for (k = i + 1; k < N; k++)
        A[x][k] -= A[i][k] * coef;
    }
  } 
    for (i = 0; i < N; i++)
       Det *= A[i][i];
} /* End Gauss func */



/* main function */
VOID main( VOID )
{
  
  LoadMatrix("m3.txt");
  Gauss();
  printf("Determinant is %f\n", Det);
  getch();
} /*end of main func */

/* END OF THE PROGRAMM */
