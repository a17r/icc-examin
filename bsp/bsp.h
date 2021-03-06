/* bsp.h: header file for BSP tree algorithm
 * Copyright (c) Norman Chin 
 */
#ifndef _BSP_INCLUDED
#define _BSP_INCLUDED

#include <stdio.h>		
#include <stdlib.h>		/* exit() */
#include <assert.h>		/* assert() */
#include <math.h>		/* fabs() */
#include <stdint.h>		/* MAXINT */
#include "GGems.h"

#ifdef __cplusplus
extern "C" {
namespace icc_examin_ns
{
#endif /* __cplusplus */

typedef struct { float rr,gg,bb,aa; } COLOR;
typedef struct { float xx,yy,zz; } POINT;
typedef struct { float aa,bb,cc,dd; } PLANE;

typedef struct vertexTag {
   float xx,yy,zz;		/**< vertex position */
   COLOR color;			/* color of face */
   struct vertexTag *vnext;	/**< pointer to next vertex in CCW order */
} VERTEX;
#define NULL_VERTEX ((VERTEX *) NULL)

typedef struct faceTag {
   VERTEX *vhead;		/* head of list of vertices */
   PLANE plane;			/* plane equation of face */
   struct faceTag *fnext;	/* pointer to next face */
  int group;                       /* group id of the source compound before splitting */
} FACE;
#define NULL_FACE ((FACE *) NULL)

typedef enum {PARTITION_NODE= 'p', IN_NODE= 'i', OUT_NODE= 'o'} NODE_TYPE; 

typedef struct partitionnodeTag {
   FACE *sameDir, *oppDir;	/* pointers to faces embedded in node */

   struct bspnodeTag *negativeSide, *positiveSide; /* "-" & "+" branches */
} PARTITIONNODE;
#define NULL_PARTITIONNODE ((PARTITIONNODE *) NULL)

typedef struct bspnodeTag {
   NODE_TYPE kind;		/* kind of BSP node */

   PARTITIONNODE *node; /* if kind == (IN_NODE || OUT_NODE) then NULL */
} BSPNODE;
#define NULL_BSPNODE ((BSPNODE *) NULL)


#ifdef __APPLE__
/* ku.b for ICC Examin original value was 0.0000076 */
#define TOLER 0.000076
#else
#define TOLER 0.000076
#endif
#define IS_EQ(a,b) ((fabs((double)(a)-(b)) >= (double) TOLER) ? 0 : 1)
typedef enum {NEGATIVE= -1, ZERO= 0, POSITIVE= 1} SIGN;
#define FSIGN(f) (((f) < -TOLER) ? NEGATIVE : ((f) > TOLER ? POSITIVE : ZERO))

/* external functions */
BSPNODE *BSPconstructTree(FACE **faceList);
bsp_boolean BSPisViewerInPositiveSideOfFace(const FACE * face,const POINT*position);
void BSPtraverseTreeAndRender(const BSPNODE *bspNode,const POINT *position, int back_face);
void BSPfreeTree(BSPNODE **bspNode);

bsp_boolean BSPdidViewerCollideWithScene(const POINT *from, const POINT *to,
				     const BSPNODE *bspTree);

VERTEX *allocVertex(float xx,float yy,float zz,COLOR *color);
FACE *allocFace(VERTEX *vlist,const PLANE *plane);
void appendVertex(VERTEX **vhead,VERTEX **vtail,VERTEX *vertex);
void appendFace(FACE **fhead,FACE **ftail,FACE *face);
void freeVertexList(VERTEX **vlist);
void freeFaceList(FACE **flist);

int  computePlane(float xx0,float yy0,float zz0,float xx1,float yy1,float zz1,
		  float xx2,float yy2,float zz2, PLANE *plane);

SIGN anyEdgeIntersectWithPlane(float x1, float y1, float z1,
			       float x2, float y2, float z2,
			       const PLANE *plane,
			       float *ixx, float *iyy, float *izz);
void BSPpartitionFaceListWithPlane(const PLANE *plane,FACE **faceList,
				   FACE **faceNeg, FACE **facePos,
				   FACE **faceSameDir, FACE **faceOppDir);
typedef void (*drawFaceListF_t)(FILE *, const FACE *faceList);
extern drawFaceListF_t drawFaceList;

char *MYMALLOC(unsigned num);
void MYFREE(char *ptr);
long MYMEMORYCOUNT(void);

#ifdef __cplusplus
} /* extern "C" */
} /* namespace icc_examin_ns */
#endif /* __cplusplus */

#endif  /* _BSP_INCLUDED */
