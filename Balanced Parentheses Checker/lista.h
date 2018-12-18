// OK
#ifndef _INCLUDE_


#define _INCLUDE_


#include<stdio.h>


#endif


typedef struct celulag
{
	void* info;

	struct celulag* urm;
}TCelulaG, *TLG, **ALG;


TLG AlocCelula(void* ae, size_t d);

int InserareS(ALG l, void* ae, size_t d);
int InserareQ(ALG ultim, void* ae, size_t d, ALG l);

void* Sterge(ALG l, size_t d);
