/* FILE NAME: T05DET.C
   PROGRAMMER: YR4
   DATE: 03.01.2020
   PURPOSE: Count matrix determinant
*/

#include <windows.h>
#include <stdio.h>

#define MAX 10
DOUBLE A[MAX][MAX];
INT N;
DOUBLE Det;
INT P[MAX];
BOOL IsParity = 1;

/* swap func */
VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;
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


/* Count Determinant func */
VOID Store( VOID )
{
  INT i;
  DOUBLE prod;
  
  for (i = 0, prod = 1; i < N; i++)
    prod *= A[i][P[i]];
  Det += (IsParity ? 1 : -1) * prod;
} /* End Store func */

/* Count permutations and parity func */
VOID Go( INT Pos )
{
  INT i, x;
  BOOL SaveParity;

  if (Pos == N)
    Store();
  else
  {
    SaveParity = IsParity;
    Go(Pos + 1);
    for (i = Pos + 1; i < MAX; i++)
    {
      /* Put in Pos element i*/
      Swap(&P[Pos], &P[i]);
      IsParity = !IsParity;
      Go(Pos + 1);
    }
    x = P[Pos];
    for (i = Pos + 1; i < MAX; i++)
      P[i - 1] = P[i];
    P[MAX - 1] = x;
    IsParity = SaveParity;
  }
} /* end go func */


/* main function */
VOID main( VOID )
{
  int i;
  
  /* filling the array */
  for(i = 0; i < MAX; i++)
    P[i] = i;
  LoadMatrix("m3.txt");
  Go(0);
  printf("Determinant is %f\n", Det);
} /*end of main func */

/* END OF THE PROGRAMM */
