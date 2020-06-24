/* FILE NAME: RNDIMG.C
 * PROGRAMMER: YR4
 * DATE: 11.06.2020
 * PURPOSE: 3D animation project.
 *          Image load.
 */

#include "rnd.h"
#include <stdio.h>


BOOL YR4_RndImgCreate( yr4IMAGE *Img, INT W, INT H )
{
  memset(Img, 0, sizeof(yr4IMAGE));

  if ((Img->Pixels = malloc(W * H * 4)) == NULL)
    return FALSE;
  Img->W = W;
  Img->H = H;
  Img->PixelsDW = (DWORD *)Img->Pixels;
  Img->PixelsC = (BYTE (*)[4])Img->Pixels;
  return TRUE;
}
/* Load image function 
 * ARGUMENTS:
 *    -image pointer:
 *        yr4IMAGE *Img;
 *    - Name of image:
 *        CHAR *FileName;
 * RETURNS: BOOL;
 */
BOOL YR4_RndImgLoad( yr4IMAGE *Img, CHAR *FileName )
{
  HBITMAP hBm;
  BITMAP bm;
  BYTE *ptr;
  INT x, y, type = 0, mulx[3] = {1, 3, 4}, rgb[3][3] = {{0, 0, 0}, {0, 1, 2}, {0, 1, 2}};
  memset(Img, 0, sizeof(yr4IMAGE));
  hBm = LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
  if (hBm == NULL)
  {
    FILE *F;

    if ((F = fopen(FileName, "rb")) != NULL)
    {
      INT w = 0, h = 0;

      fread(&w, 2, 1, F);
      fread(&h, 2, 1, F);
      fseek(F, 0, SEEK_END);
      if (ftell(F) == w * h * 4 + 4)
      {
        if (YR4_RndImgCreate(Img, w, h))
        {
          rewind(F);
          fread(Img->Pixels, 4, w * h, F);
        }
      }
      fclose(F);
      return TRUE;
    }
    return FALSE;
  }

  GetObject(hBm, sizeof(bm), &bm);

  if (bm.bmBitsPixel != 8 && bm.bmBitsPixel != 24 && bm.bmBitsPixel != 32)
  {
    DeleteObject(hBm);
    return FALSE;
  }
  if(!YR4_RndImgCreate(Img, bm.bmWidth, bm.bmHeight))
  {
    DeleteObject(hBm);
    return FALSE;
  }

  type = bm.bmBitsPixel == 8 ? 0 : bm.bmBitsPixel == 24 ? 1 : 2;
  ptr = bm.bmBits;
  for (x = 0; x < Img->H; x++)
    for (y = 0; y < Img->W; y++)
    {
      BYTE b = ptr[y * bm.bmWidthBytes + x * mulx[type] + rgb[type][0]],
           g = ptr[y * bm.bmWidthBytes + x * mulx[type] + rgb[type][1]],
           r = ptr[y * bm.bmWidthBytes + x * mulx[type] + rgb[type][2]],
           a = 255;

      Img->Pixels[(y * Img->W + x) * 4 + 0] = b;
      Img->Pixels[(y * Img->W + x) * 4 + 1] = g;
      Img->Pixels[(y * Img->W + x) * 4 + 2] = r;
      Img->Pixels[(y * Img->W + x) * 4 + 3] = a;
    }
  DeleteObject(hBm);  
  return TRUE;
} /* end of YR4_RndImgLoad func */

/* Free image function 
 * ARGUMENTS:
 *    -image pointer:
 *        yr4IMAGE *Img;
 * RETURNS: none;
 */
VOID YR4_RndImgFree( yr4IMAGE *Img )
{
  if (Img->Pixels != NULL)
    free(Img->Pixels);

  memset(Img, 0, sizeof(yr4IMAGE));
} /* end of YR4_RndImgFree func */

/* END OF 'RNDIMG.C' FILE */
