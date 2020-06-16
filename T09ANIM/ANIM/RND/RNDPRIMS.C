/* FILE NAME: RNDPRIMS.S
 * PROGRAMMER: YR4
 * DATE: 13.06.2020
 * PURPOSE: 3D animation project.
 *          Prims file.
 */
#include "rnd.h"
#include "res/rndres.h"
#include <string.h>
#include <stdio.h>

/* Create array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       yr4PRIMS *Prs;
 *   - number of primitives to be add:
 *       INT NumOfPrims;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL YR4_RndPrimsCreate( yr4PRIMS *Prs, INT NumOfPrims )
{
  memset(Prs, 0, sizeof(yr4PRIMS));

  if ((Prs->Prims = malloc(sizeof(yr4PRIM) * NumOfPrims)) == NULL)
    return FALSE;
  memset(Prs->Prims, 0, sizeof(yr4PRIM) * NumOfPrims);
  Prs->NumOfPrims = NumOfPrims;
  Prs->Trans = MatrIdentity();
  return TRUE;
} /* End of 'YR4_RndPrimsCreate' function */

/* Delete array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       yr4PRIMS *Prs;
 * RETURNS: None.
 */
VOID YR4_RndPrimsFree( yr4PRIMS *Prs )
{
  if (Prs->Prims != NULL)
    free(Prs->Prims);
  memset(Prs, 0, sizeof(yr4PRIMS));
} /* End of 'YR4_RndPrimsFree' function */

/* Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       yr4PRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID YR4_RndPrimsDraw( yr4PRIMS *Prs, MATR World )
{
  INT i;
    /* Draw all nontransparent primitives */
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (YR4_RndMtlGet(Prs->Prims[i].MtlNo)->Trans == 1)
      YR4_RndPrimDraw(&Prs->Prims[i], World);

  /* Draw all transparent primitives */
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (YR4_RndMtlGet(Prs->Prims[i].MtlNo)->Trans != 1)
      YR4_RndPrimDraw(&Prs->Prims[i], World);
  glCullFace(GL_BACK);
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (YR4_RndMtlGet(Prs->Prims[i].MtlNo)->Trans != 1)
      YR4_RndPrimDraw(&Prs->Prims[i], World);
  glDisable(GL_CULL_FACE);

} /* End of 'YR4_RndPrimsDraw' function */


/* Load array of primitives from G3DM file function.
 * ARGUMENTS:
 *   - primitive collection pointer:
 *       yr4PRIMS *Prs;
 *   - file name to load from:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL YR4_RndPrimsLoad( yr4PRIMS *Prs, CHAR *FileName )
{
  BYTE *mem, *ptr;
  INT flen, p, t, m;
  FILE *F;
  DWORD Sign; /* == "G3DM" */
  INT NumOfPrims;
  INT NumOfMaterials;
  INT NumOfTextures;
  struct tagG3DMMTL
  {
    CHAR Name[300]; /* Material name */
    /* Illumination coefficients */
    VEC Ka, Kd, Ks;     /* Ambient, diffuse, specular coefficients */
    FLT Ph;             /* Phong power coefficient – shininess */
    FLT Trans;          /* Transparency factor */
    DWORD Tex[8];       /* Texture references 
                        * (8 time: texture number in G3DM file, -1 if no texture) */
    /* Shader information */
    CHAR ShaderString[300]; /* Additional shader information */
    DWORD Shader;       /* Shader number (uses after load into memory) */
  } *mtls;


  memset(Prs, 0, sizeof(yr4PRIMS));

  /* Open file */
  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;

  /* Obtain file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);
  rewind(F);

  /* Allocate memory and load whole file to memory */
  if ((mem = malloc(flen)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  fread(mem, 1, flen, F);
  fclose(F);

  ptr = mem;

  Sign = *(DWORD *)ptr, ptr += 4;
  if (Sign != *(DWORD *)"G3DM")
  {
    free(mem);
    return FALSE;
  }
  NumOfPrims = *(DWORD *)ptr, ptr += 4;
  NumOfMaterials = *(DWORD *)ptr, ptr += 4;
  NumOfTextures = *(DWORD *)ptr, ptr += 4;

  if (!YR4_RndPrimsCreate(Prs, NumOfPrims))
  {
    free(mem);
    return FALSE;
  }

  /* Primitives */
  for (p = 0; p < NumOfPrims; p++)
  {
    DWORD NumOfVertexes;
    DWORD NumOfFacetIndexes;  /* num of facets * 3 */
    DWORD MtlNo;              /* Material number in table below (in material section) */
    yr4VERTEX *V;
    INT *Ind;

    NumOfVertexes = *(DWORD *)ptr, ptr += 4;
    NumOfFacetIndexes = *(DWORD *)ptr, ptr += 4;
    MtlNo = *(DWORD *)ptr, ptr += 4;
    V = (yr4VERTEX *)ptr, ptr += sizeof(yr4VERTEX) * NumOfVertexes;
    Ind = (INT *)ptr, ptr += sizeof(INT) * NumOfFacetIndexes;
    YR4_RndPrimCreate(&Prs->Prims[p],
       V, NumOfVertexes, Ind, NumOfFacetIndexes, YR4_RND_PRIM_TRIMESH);
    Prs->Prims[p].MtlNo = MtlNo + YR4_RndMaterialsSize;
  }

  /* Materials */
  mtls = (struct tagG3DMMTL *)ptr, ptr += sizeof(struct tagG3DMMTL) * NumOfMaterials;
  for (m = 0; m < NumOfMaterials; m++)
  {
    INT i;
    yr4MATERIAL mtl = YR4_RndMtlGetDef();

    strncpy(mtl.Name, mtls[m].Name, YR4_STR_MAX - 1);
    mtl.Ka = mtls[m].Ka;
    mtl.Kd = mtls[m].Kd;
    mtl.Ks = mtls[m].Ks;
    mtl.Ph = mtls[m].Ph;
    mtl.Trans = mtls[m].Trans;
    for (i = 0; i < 8; i++)
      mtl.Tex[i] = (mtls[m].Tex[i] == -1 ? -1 : mtls[m].Tex[i] + YR4_RndTexturesSize);
    YR4_RndMtlAdd(&mtl);
  }
  /* Textures */
  for (t = 0; t < NumOfTextures; t++)
  {
    struct
    {
      CHAR Name[300]; /* Texture name */
      DWORD W, H;     /* Texture image size in pixels */
      DWORD C;        /* Texture image components (1-mono, 3-bgr or 4-bgra) */
    } *tex = (VOID *)ptr;

    ptr += sizeof(*tex);
    YR4_RndTexAddImg(tex->Name, tex->W, tex->H, tex->C, ptr);
    ptr += tex->W * tex->H * tex->C;
  }

  free(mem);
  return TRUE;
} /* End of 'YR4_RndPrimsLoad' function */

/* END OF 'RNDPRIMS.C' FILE */