// OK
#include "lista.h"

typedef struct
{
	int id;
	
	char c;
} inf;

TLG AlocCelula(void* ae, size_t d)
{
	TLG aux = (TLG)malloc(sizeof(TCelulaG));

	if(!aux)
	{
		printf("Error at malloc()!!!\n");

		return NULL;
	}

	aux->info = malloc(d);

	if(!aux->info)
	{
		printf("Error at malloc()!!!\n");

		free(aux);

		return NULL;
	}

	memcpy(aux->info, ae, d);
	
	aux->urm = NULL;

	return aux;
}


void print(TLG l)
{
	TLG p = l;
	inf* aux;
	while(p != NULL)
	{
		aux = p->info;

		printf("%c", aux->c);	

		p = p -> urm;
	}

	printf("\n");
}


int InserareS(ALG l, void* ae, size_t d)
{
	TLG aux = AlocCelula(ae, d);

	if(!aux)
	{
		printf("Error at AlocCelula()!!!\n");

		return -1;
	}

	aux->urm = *l;

	*l = aux;
		
	return 0;
}


void printq(ALG l)
{
	TLG p = *l;

	while(p)
	{
		printf("%c", ((inf*)p->info)->c);

		p = p->urm;
	}

	printf("\n");
}


int InserareQ(ALG ultim, void* ae, size_t d, ALG l)
{
	TLG aux;

	aux = AlocCelula(ae, d);
	
	if(!aux)
	{
		printf("Error at AlocCelula()!!!\n");

		return -1;
	}

	if(*ultim)
	{
		(*ultim)->urm = aux;

		(*ultim) = (*ultim)->urm;
	}
	else
	{
		*l = aux;

		*ultim = aux;
	}

	return 0;
}


void* Sterge(ALG l, size_t d)
{
	TLG aux = *l;

	if(!aux)
	{
//		printf("Lista este vida in Sterge()!!!\n");

		return NULL;
	}

	if(aux->urm)
	{
		*l = (*l)->urm;

		aux->urm = NULL;
	}
	else
	{
		aux = AlocCelula(aux->info, d);
		
		free((*l)->info);
		free(*l);

		*l = NULL;
		l = NULL;
	}

	return aux->info;
}
