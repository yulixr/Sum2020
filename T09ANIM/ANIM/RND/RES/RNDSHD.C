/* FILE NAME: RNDSHD.C
 * PROGRAMMER: YR4
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          Shaders loading file.
 */

#include "../rnd.h"
#include <string.h>
#include <stdio.h>

INT YR4_RndShaderSize;
yr4SHADER YR4_RndShaders[YR4_MAX_SHADERS];

/* Load text from file function
 * ARGUMENTS:
 *  -file name:
 *    CHAR *FileName;
 * RETURNS:
 * (CHAR *) load text.
 */
static CHAR * YR4_RndShdLoadTextFromFile( CHAR *FileName )
{
  FILE *F;
  CHAR *txt;
  INT flen;

  /* Open file */
  if ((F = fopen(FileName, "rb")) == NULL)
    return NULL;

  /* Obtain file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);

  /* Allocate memory for file text */
  rewind(F);
  if ((txt = malloc(flen + 1)) == NULL)
  {
    fclose(F);
    return NULL;
  }
  /* Load text from file */
  memset(txt, 0, flen + 1);
  fread(txt, 1, flen, F);
  fclose(F);
  return txt;
} /* end of 'YR4_RndShdLoadTextFromFile' func */ 

/* Store log to file func.
 * ARGUMENTS:
 *   - message file prefix, shader name and text:
 *       CHAR *Prefix, *PartName, *Text;
 * RETURNS: none.
 */
static VOID YR4_RndShdLog( CHAR *Prefix, CHAR *PartName, CHAR *Text )
{
  FILE *F;

  if ((F = fopen("BIN/SHADERS/YR4{30}SHD.LOG", "a")) == NULL)
    return;
  fprintf(F, "%s/%s.GLSL\n%s\n", Prefix, PartName, Text);
  fclose(F);
} /* end of YR4_RndShdLog func */

/* Load shaders func
 * ARGUMENTS:
 *    -Shader prefix name:
 *       CHAR *ShaderFileNamePrefix
 * RETURNS: INT.
 */
INT YR4_RndShdLoad( CHAR *ShaderFileNamePrefix )
{
  struct
  {
    CHAR *Name; /* Name of shader */
    INT Type; /* Shader type */
    INT Id; /* Shader Id created by OpenGL */
  } shd[] = 
  {
    {"VERT", GL_VERTEX_SHADER},
    {"FRAG", GL_FRAGMENT_SHADER},
    {"GEOM", GL_GEOMETRY_SHADER}
  };
  INT prg, i, res, NoofS = sizeof(shd) / sizeof(shd[0]);
  CHAR *txt;
  BOOL is_ok = TRUE;
  static CHAR Buf[1000];

  for (i = 0; i < NoofS; i++)
  {
    /* build file name */
    sprintf(Buf, "BIN/SHADERS/%s/%s.GLSL", ShaderFileNamePrefix, shd[i].Name);
    txt = YR4_RndShdLoadTextFromFile(Buf);

    if (shd[i].Type != GL_VERTEX_SHADER && shd[i].Type != GL_FRAGMENT_SHADER &&
      txt == NULL)
    {
      continue;
    }
    /* load shader text */
    if (txt == NULL)
    {
      YR4_RndShdLog(ShaderFileNamePrefix, shd[i].Name, "Error load file");
      is_ok = FALSE;
      break;
    }
    /* create shader */
    if ((shd[i].Id = glCreateShader(shd[i].Type)) == 0)
    {
      YR4_RndShdLog(ShaderFileNamePrefix, shd[i].Name, "Error create shader");
      free(txt);
      is_ok = FALSE;
      break;
    }
    /* attach shader text to shader */
    glShaderSource(shd[i].Id, 1, &txt, NULL);
    free(txt);

    /* compile shader */
    glCompileShader(shd[i].Id);
    glGetShaderiv(shd[i].Id, GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(shd[i].Id, sizeof(Buf), &res, Buf);
      YR4_RndShdLog(ShaderFileNamePrefix, shd[i].Name, Buf);
      is_ok = FALSE;
      break;
    }
  }

  /* Create shader program */
  if (is_ok)
  {
    if ((prg = glCreateProgram()) == 0)
    {
      YR4_RndShdLog(ShaderFileNamePrefix, "PROG", "Error create programm");
      is_ok = FALSE;
    }
    else
    {
      /* Attach shaders to prog */
      for (i = 0; i < NoofS; i++)
        if (shd[i].Id != 0)
          glAttachShader(prg, shd[i].Id);
      /* Link shader program */
      glLinkProgram(prg);
      glGetProgramiv(prg, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(prg, sizeof(Buf), &res, Buf);
        YR4_RndShdLog(ShaderFileNamePrefix, "PROG", Buf);
        is_ok = FALSE;
      }
    }
  }

  if (!is_ok)
  {
    for (i = 0; i < NoofS; i++)
      if (shd[i].Id != 0)
      {
        if (prg)
          glDetachShader(prg, shd[i].Id);
        glDeleteShader(shd[i].Id);
      }
      if (prg)
        glDeleteProgram(prg);
      prg = 0;
  }
  return prg;
} /* end of YR4_RndShdLoad func */

/* Delete shaders func
 * ARGUMENTS:
 *    -Programm id:
 *         INT ProgId.
 * RETURNS: none.
 */
VOID YR4_RndShdDelete( INT ProgId )
{
  INT shdrs[5], n, i;

  if (ProgId == 0)
    return;

  glGetAttachedShaders(ProgId, 5, &n, shdrs);
  for (i = 0; i < n; i++)
  {
    glDetachShader(ProgId, shdrs[i]);
    glDeleteShader(shdrs[i]);
  }
  glDeleteProgram(ProgId);
} /* end of YR4_RndShdDelete func */

/* Add shaders func
 * ARGUMENTS:
 *    -Shader prefix:
 *       CHAR *ShaderFileName.
 * RETURNS: INT.
 */
INT YR4_RndShdAdd( CHAR *ShaderFileName )
{
  if (YR4_RndShaderSize >= YR4_MAX_SHADERS)
    return 0;

  strncpy(YR4_RndShaders[YR4_RndShaderSize].Name,
    ShaderFileName, YR4_STR_MAX - 1);
  YR4_RndShaders[YR4_RndShaderSize].ProgId = 
    YR4_RndShdLoad(ShaderFileName);

  return YR4_RndShaderSize++;
}

/* INIT shaders func
 * ARGUMENTS: none.
 * RETURNS: none.
 */
VOID YR4_RndShdInit( VOID )
{
  YR4_RndShaderSize = 0;
  YR4_RndShdAdd("DEFAULT");
}

/* Update shaders func
 * ARGUMENTS: none.
 * RETURNS: none.
 */
VOID YR4_RndShdUpdate( VOID )
{
  INT i;
  
  for (i = 0; i < YR4_RndShaderSize; i++)
  {
    YR4_RndShdDelete(YR4_RndShaders[i].ProgId);
    YR4_RndShaders[i].ProgId = 
      YR4_RndShdLoad(YR4_RndShaders[i].Name);
  }
}

/* Close shaders func
 * ARGUMENTS: none.
 * RETURNS: none.
 */
VOID YR4_RndShdClose( VOID )
{
  INT i;

  for (i = 0; i < YR4_RndShaderSize; i++)
    YR4_RndShdDelete(YR4_RndShaders[i].ProgId);
  YR4_RndShaderSize = 0;
}

/* END OF 'RNDSHD.C' FILE */ 