/* FILE NAME: RNDRES.H
 * PROGRAMMER: YR4
 * DATE: 13.06.2020
 * PURPOSE: 3D animation project.
 *          Declarations for Resources module.
 */

#ifndef __RNDRES_H_
#define __RNDRES_H_

#include "../../../def.h"

#define YR4_STR_MAX 100

/******** shader handle ************/
#define YR4_MAX_SHADERS 30

typedef struct tagyr4SHADER
{
  CHAR Name[YR4_STR_MAX];
  INT ProgId;
} yr4SHADER;

extern INT YR4_RndShaderSize;
extern yr4SHADER YR4_RndShaders[YR4_MAX_SHADERS];

INT YR4_RndShdLoad( CHAR *ShaderFileNamePrefix );
VOID YR4_RndShdDelete( INT ProgId );
INT YR4_RndShdAdd( CHAR *ShaderFileName );
VOID YR4_RndShdInit( VOID );
VOID YR4_RndShdUpdate( VOID );
VOID YR4_RndShdClose( VOID );

/******** texture handle **********/

#define YR4_MAX_TEXTURES 300
typedef struct tagyr4TEXTURE
{
  CHAR Name[YR4_STR_MAX]; /* Name */
  INT W, H;               /* Size */
  UINT TexId;             /* Opengl id */
} yr4TEXTURE;

extern yr4TEXTURE YR4_RndTextures[YR4_MAX_TEXTURES];
extern INT YR4_RndTexturesSize;

VOID YR4_RndTexInit( VOID );
VOID YR4_RndTexClose( VOID );
INT YR4_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, DWORD *Bits );
INT YR4_RndTexAdd( CHAR *FileName );

/******** material handle *********/
#define YR4_MAX_MATERIALS 350

typedef struct tagyr4MATERIAL
{
  CHAR Name[YR4_STR_MAX]; /* Name */

  VEC Ka, Kd, Ks; /* lightning coeffs */
  FLT Ph;    /* Phong coeff */
  FLT Trans; /* Transparency factor */
  INT Tex[8];     /* texture reference */

  CHAR ShaderStr[YR4_STR_MAX]; 
  INT ShdNo;                   /* shader reference */
} yr4MATERIAL;

extern yr4MATERIAL YR4_RndMaterials[YR4_MAX_MATERIALS];
extern INT YR4_RndMaterialsSize;

INT YR4_RndMtlAdd( yr4MATERIAL *Mtl );
VOID YR4_RndMtlInit( VOID );
INT YR4_RndMtlApply( INT MtlNo );
VOID YR4_RndMtlClose( VOID );
yr4MATERIAL * YR4_RndMtlGet( INT MtlNo );
yr4MATERIAL YR4_RndMtlGetDef( VOID );

static struct
{
  CHAR *Name;
  VEC Ka, Kd, Ks;
  FLT Ph;
} MatLib[] =
{
  {"Black Plastic", {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},               32},
  {"Brass",         {0.329412,0.223529,0.027451}, {0.780392,0.568627,0.113725}, {0.992157,0.941176,0.807843}, 27.8974},
  {"Bronze",        {0.2125,0.1275,0.054},       {0.714,0.4284,0.18144},       {0.393548,0.271906,0.166721},  25.6},
  {"Chrome",        {0.25, 0.25, 0.25},          {0.4, 0.4, 0.4},              {0.774597, 0.774597, 0.774597}, 76.8},
  {"Copper",        {0.19125,0.0735,0.0225},     {0.7038,0.27048,0.0828},      {0.256777,0.137622,0.086014},  12.8},
  {"Gold",          {0.24725,0.1995,0.0745},     {0.75164,0.60648,0.22648},    {0.628281,0.555802,0.366065},  51.2},
  {"Peweter",       {0.10588,0.058824,0.113725}, {0.427451,0.470588,0.541176}, {0.3333,0.3333,0.521569},      9.84615},
  {"Silver",        {0.19225,0.19225,0.19225},   {0.50754,0.50754,0.50754},    {0.508273,0.508273,0.508273},  51.2},
  {"Polished Silver", {0.23125,0.23125,0.23125}, {0.2775,0.2775,0.2775},       {0.773911,0.773911,0.773911},  89.6},
  {"Turquoise",     {0.1, 0.18725, 0.1745},      {0.396, 0.74151, 0.69102},    {0.297254, 0.30829, 0.306678}, 12.8},
  {"Ruby",          {0.1745, 0.01175, 0.01175},  {0.61424, 0.04136, 0.04136},  {0.727811, 0.626959, 0.626959}, 76.8},
  {"Polished Gold", {0.24725, 0.2245, 0.0645},   {0.34615, 0.3143, 0.0903},    {0.797357, 0.723991, 0.208006}, 83.2},
  {"Polished Bronze", {0.25, 0.148, 0.06475},    {0.4, 0.2368, 0.1036},        {0.774597, 0.458561, 0.200621}, 76.8},
  {"Polished Copper", {0.2295, 0.08825, 0.0275}, {0.5508, 0.2118, 0.066},      {0.580594, 0.223257, 0.0695701}, 51.2},
  {"Jade",          {0.135, 0.2225, 0.1575},     {0.135, 0.2225, 0.1575},      {0.316228, 0.316228, 0.316228}, 12.8},
  {"Obsidian",      {0.05375, 0.05, 0.06625},    {0.18275, 0.17, 0.22525},     {0.332741, 0.328634, 0.346435}, 38.4},
  {"Pearl",         {0.25, 0.20725, 0.20725},    {1.0, 0.829, 0.829},          {0.296648, 0.296648, 0.296648}, 11.264},
  {"Emerald",       {0.0215, 0.1745, 0.0215},    {0.07568, 0.61424, 0.07568},  {0.633, 0.727811, 0.633},       76.8},
  {"Black Plastic", {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},                32.0},
  {"Black Rubber",  {0.02, 0.02, 0.02},          {0.01, 0.01, 0.01},           {0.4, 0.4, 0.4},                10.0},
};
#define MAT_N (sizeof(MatLib) / sizeof(MatLib[0]))

/****** resource handle ******/
VOID YR4_RndResInit( VOID );
VOID YR4_RndResClose( VOID );


#endif
/* END OF 'RNDRES.H' FILE */