/* FILE NAME: RNDTEX.C
 * PROGRAMMER: YR4
 * DATE: 13.06.2020
 * PURPOSE: 3D animation project.
 *          Textures file.
 */

#include "../rnd.h"
#include <string.h>

yr4TEXTURE YR4_RndTextures[YR4_MAX_TEXTURES];
INT YR4_RndTexturesSize;

/* Textures support initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID YR4_RndTexInit( VOID )
{
  memset(YR4_RndTextures, 0, sizeof(YR4_RndTextures));
  YR4_RndTexturesSize = 0;
} /* End of 'YR4_RndTexInit' function */

/* Textures support deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID YR4_RndTexClose( VOID )
{
  INT i;

  for (i = 0; i < YR4_RndTexturesSize; i++)
    glDeleteTextures(1, &YR4_RndTextures[i].TexId);
  memset(YR4_RndTextures, 0, sizeof(YR4_RndTextures));
  YR4_RndTexturesSize = 0;
} /* End of 'YR4_RndTexClose' function */

/* Add texture image to stock function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture size in pixels:
 *       INT W, H;
 *   - pointer to image pixel colors:
 *       DWORD *Bits;
 * RETURNS:
 *   (INT) add texture stock index.
 */
INT YR4_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, DWORD *Bits )
{
  if (YR4_RndTexturesSize >= YR4_MAX_TEXTURES)
    return -1;
  /* Allocate texture space */
  strncpy(YR4_RndTextures[YR4_RndTexturesSize].Name, Name, YR4_STR_MAX - 1);
  YR4_RndTextures[YR4_RndTexturesSize].W = W;
  YR4_RndTextures[YR4_RndTexturesSize].H = H;
  glGenTextures(1, &YR4_RndTextures[YR4_RndTexturesSize].TexId);
  
  glBindTexture(GL_TEXTURE_2D, YR4_RndTextures[YR4_RndTexturesSize].TexId);

  glTexImage2D(GL_TEXTURE_2D, 0, C, W, H, 0,
    C == 3 ? GL_BGR : C == 4 ? GL_BGRA : GL_LUMINANCE,
    GL_UNSIGNED_BYTE, Bits);
  glGenerateMipmap(GL_TEXTURE_2D);
  /* Upload texture */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);
  return YR4_RndTexturesSize++;
} /* End of 'YR4_RndTexAddImg' function */

INT YR4_RndTexAdd( CHAR *FileName )
{
  INT n;
  yr4IMAGE img;

  if (!YR4_RndImgLoad(&img, FileName))
    return -1;
  n = YR4_RndTexAddImg(FileName, img.W, img.H, 4, img.Pixels);
  YR4_RndImgFree(&img);
  return n;
}

/* Add new texture to texture store system by OpenGL format function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture size:
 *       INT W, H;
 *   - OpenGL data type:
 *       INT GLType;
 * RETURNS:
 *   (INT) added texture table number.
 */
INT YR4_RndTexAddFmt( CHAR *Name, INT W, INT H, INT GLType )
{
  INT w, h, fmt;
 // PFNGLTEXSTORAGE2DPROC abc = (PFNGLTEXSTORAGE2DPROC)wglGetProcAddress("glTexStorage2D");
  VOID *ptr;
 // PFNGLTEXTURESTORAGE2DPROC abc1 = (PFNGLTEXTURESTORAGE2DPROC)wglGetProcAddress("glTextureStorage2D");

  /* Check for free space */
  if (YR4_RndTexturesSize >= YR4_MAX_TEXTURES)
    return -1;

  strncpy(YR4_RndTextures[YR4_RndTexturesSize].Name, Name, YR4_STR_MAX - 1);
  YR4_RndTextures[YR4_RndTexturesSize].W = W;
  YR4_RndTextures[YR4_RndTexturesSize].H = H;
  glGenTextures(1, &YR4_RndTextures[YR4_RndTexturesSize].TexId);

  glBindTexture(GL_TEXTURE_2D, YR4_RndTextures[YR4_RndTexturesSize].TexId);
  /*
  ptr = malloc(W * H * 4);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, W, H, 0, GL_DEPTH_COMPONENT, GL_FLOAT, ptr);
  free(ptr);   */
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, W, H);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, YR4_RndTextures[YR4_RndTexturesSize].TexId, 0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &fmt);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  return YR4_RndTexturesSize++;
} /* End of 'YR4_RndTexAddFmt' function */


/* END OF 'RNDTEX.C' FILE */