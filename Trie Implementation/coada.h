// OK
#ifndef _INCLUDE_


#define _INCLUDE_


#include<stdio.h>

#include "lista.h"


#endif


typedef struct coada
{
	int id, dime;

	TLG ic, sc;
} TCoada, *AQ;


#ifndef _INFO_


#define _INFO_


typedef struct
{
	int id;

	char c;
} info;


#endif


#define DIMEC(a) (((AQ)(a))->dime)

#define IC(a) (((AQ)(a))->ic)
#define SC(a) (((AQ)(a))->sc)

#define DIMDIF(s, d) (DIME(s) != DIME(d))

#define VIDAC(a) (IC(a) == SC(a))


void* InitQ(int d, ...);

int IntrQ(void* a, void* ae);
void* ExtrQ(void* a, void* ae);
int PrimQ(void* a, void* ae);

void DistrQ(void** aa);

void* MutaQ(void* ad, void* as);
int ConcatQ(void* ad, void* as);

void* SortQ(void* a);

void* PrintQ(void* a, FILE* f);

void* CorrectQ(void* a, FILE* f);
