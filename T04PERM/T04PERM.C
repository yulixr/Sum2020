/* FILE NAME: T04PERM.C
   PROGRAMMER: YR4
   DATE: 02.01.2020
   PURPOSE: Permutations and parity
*/

#include <windows.h>
#include <stdio.h>

/* base array */
#define MAX 5
INT P[MAX];

BOOL IsParity = 1;

/* swap func */
VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;
  *A = *B;
  *B = tmp;
} /* end swap func */

/* Store permutation to log file function */
VOID Store( VOID )
{
  FILE *F;
  INT i;

  if((F = fopen("perm.txt", "a")) == NULL)
    return;

  for (i = 0; i < MAX - 1; i++)
    fprintf(F, "%d,", P[i]);
  fprintf(F, "%d – parity: %s\n", P[MAX - 1], IsParity ? "even" : "odd");

  fclose(F);
} /* End Store func */

/* Count permutations and parity func */
VOID Go( INT Pos )
{
  INT i, x;
  BOOL SaveParity;

  if (Pos == MAX)
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
    P[i] = i + 1;
  Go(0);
} /*end of main func */

/* END OF THE PROGRAMM */
