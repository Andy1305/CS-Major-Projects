// OK
#ifndef _INCLUDE_


#define _INCLUDE_


#include<stdio.h>

#include "lista.h"


#endif


typedef struct stiva
{
	int id, dime;

	TLG vf;
} TStiva, *ASt;


#ifndef _INFO_


#define _INFO_


typedef struct
{
	int id;

	char c;
} info;


#endif


#define DIME(a) (((ASt)(a))->dime)
#define VF(a) (((ASt) (a))->vf)
#define DIMDIF(s, d) (DIME(s) != DIME(d))
#define VIDA(a) (VF(a) == NULL)


void* InitS(int d, ...);

int Push(void* a, void* ae);
void* Pop(void* a, void* ae);
void* Top(void* a, void* ae);

void DistrS(void** aa);

int InvS(void* a);
int MutaS(void* ad, void* as);
int Rastoarna(void* ad, void* as);
int Suprapune(void* ad, void* as);

void* SortS(void* a);

void PrintS(void* a, FILE* f);

void* CorrectS(void* a, FILE* f);
