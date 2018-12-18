#ifndef _INCLUDE_


#define _INCLUDE_


#include<stdio.h>


#endif


#include "coada.h"


#ifndef _FUNCTIONS_


#define _FUNCTIONS_


int min(int a, int b)
{
	return (a - b) ? b : a;
}


int max(int a, int b)
{
	return (a - b) ? a : b;
}


#endif


void* InitQ(int d, ...)
{
	AQ q;

	va_list ap;

	q = (AQ)malloc(sizeof(TCoada));

	if(!q)
	{
		printf("Error at malloc()!!!\n");

		return NULL;
	}

	va_start(ap, d);

	va_end(ap);

	q->dime = d;
	q->ic = NULL;
	q->sc = NULL;

	return (void*) q;
}


void printcoada(TLG l)
{
	TLG aux = l;

	while(aux)
	{
		printf("%d", ((info*)aux->info)->id);

		aux = aux->urm;
	}

	printf("\n");
}


int IntrQ(void* a, void* ae)
{
	if(InserareQ(&IC(a), ae, DIME(a), &SC(a)) == -1)
	{
		printf("Error at InsertQ!!!\n");

		return -1;
	}

//	printf("Am inserat %c.\n", ((info*)IC(a)->info)->c);
	return 0;	
}


void* ExtrQ(void* a, void* ae)
{	
	if(VIDA(a))
	{
//		printf("Coada este vida!!!\n");

		return NULL;
	}

	if((ae = Sterge(&SC(a), DIME(a))) == NULL)
	{
//		printf("Lista este vida!!!\n");

		return NULL;
	}

	return ae;
}

int PrimQ(void* a, void* ae)
{
	void* ae2 = NULL;
	void* aux = NULL;
	
	if(!ExtrQ(&SC(a), ae))
	{
		printf("Error at ExtrQ()!!!\n");

		return -1;
	}

	if(IntrQ(aux, ae) == -1)
	{
		printf("Error at IntrQ()!!!\n");

		return -1;
	}

	while(!VIDA(a))
	{
		ExtrQ(&SC(a), ae2);

		IntrQ(aux, ae2);
	}

	free(a);

	a = aux;

	return 0;
}


void* MutaQ(void* ad, void* as)
{
	void* ae;

	while(SC(as) != NULL)
	{
		ae = ExtrQ(as, ae);
//		printf("In MutaQ: %c\n", ((info*)ae)->c);
		IntrQ(ad, ae);
	}
//	printf("abc\n");
//	printf("SC(ad): %c\n", ((info*)SC(as)->info)->c);
//	printcoada(SC(ad));
	return ad;
}


/*void* SortQ(void* a)
{
	printf("\n\n\n\n\n\n\n\n\n");
	void* ae1 = NULL;
	void* ae2 = NULL;
	void* aux = InitQ(sizeof(info));
	void* q = InitQ(sizeof(info));

	while(SC(a) != NULL)
	{
		ae1 = ExtrQ(a, ae1);

		while(SC(a) != NULL)
		{
			ae2 = ExtrQ(a, ae2);

			if(((info*)ae1)->id <= ((info*)ae2)->id)
			{
				IntrQ(aux, ae2);
			}
			else
			{
				IntrQ(a, ae1);

				ae1 = ae2;
			}	
		}

		IntrQ(q, ae1);

		a = MutaQ(a, aux);
//		printf("%c\n", ((info*)SC(a)->info)->c);
		break;
	}

	a = MutaQ(a, q);
//	printcoada(SC(aux));
	return a;
}*/


void* PrintQ(void* a, FILE* f)
{
	void* ae;
	void* aux = InitQ(DIME(a));

	fprintf(f, "\"");
	
	while(SC(a) != NULL)
	{
		ae = ExtrQ(a, ae);

		fprintf(f, "%c", ((info*)ae)->c);

		IntrQ(aux, ae);
	}

	fprintf(f, "\"");

	return aux;
}


void* CopiazaQ(void* ad, void* as)
{
	void* ae = NULL;
	void* aux = InitQ(DIME(as));

	while(SC(as) != NULL)
	{
		ae = ExtrQ(as, ae);

		IntrQ(ad, ae);
		IntrQ(aux, ae);
	}

	as = aux;

	return as;
}


void* PuneQInS(void* ad, void** as)
{
	void* ae = NULL;
	void* aux = InitQ(DIME(ad));

	while(SC(*as) != NULL)
	{
		ae = ExtrQ(*as, ae);

		IntrQ(aux, ae);

		Push(ad, ae);
	}

	*as = aux;

	return ad;
}


void* PuneSInQ(void* ad, void** as)
{
	void* ae = NULL;

	while(VF(*as) != NULL)
	{
		ae = Pop(*as, ae);

		IntrQ(ad, ae);
	}

	return ad;
}


void* SortQ(void* a)
{
        void* ae;
        void* ae2;
        void* aux = InitS(DIME(a));
	void* aux2 = InitS(DIME(a));
        void* sorted = InitS(DIME(a));

	aux2 = PuneQInS(aux2, &a);

        while(!VIDA(aux2))
        {
                ae = Pop(aux2, ae);

                while(!VIDA(aux2))
                {
                        ae2 = Pop(aux2, ae2);

                        if(((info*)ae)->id >= ((info*)ae2)->id)
                        {
                                Push(aux, ae2);
                        }
                        else
                        {
                                Push(aux2, ae);
 
                                ae = ae2;
                        }
                }
 
                Push(sorted, ae);
 
                Rastoarna(aux2, aux);
        }
 
	a = InitQ(DIME(a));

	a = PuneSInQ(a, &sorted);	

        return a;
}


void* CorrectQ(void* a, FILE* f)
{
	int result = 0, index = 0;

	char ch, ch2;

	void* ae = NULL;
	void* aux = InitS(DIME(a));
	void* aux2 = InitS(DIME(a));	
	void* aux3 = InitS(DIME(a));

	if(!aux)
	{
		printf("Error at InitS()!!!\n");
	
		return NULL;
	}

	if(!aux2)
	{
		printf("Error at InitS()!!!\n");

		return NULL;
	}

	if(!aux3)
	{
		printf("Error at InitS()!!!\n");

		return NULL;
	}

	aux2 = PuneQInS(aux2, &a);

	Rastoarna(aux3, aux2);
//	printcoada(VF(aux3));
	ae = malloc(sizeof(info));

	((info*)ae)->id = -1;

	Push(aux, ae);
	
	while(!VIDA(aux3))
	{
		ae = Pop(aux3, ae);
		
		ch = ((info*)ae)->c;
		
		if(ch == '(' || ch == '[' || ch == '{')
		{
			((info*)ae)->id = index;
			((info*)ae)->c = ch;

			Push(aux, ae);
		}
		else
		{
//			ae = Top(aux, ae);

//			ch2 = ((info*)ae)->c;

//			if((ch == ')' && ch2 == '(') || (ch == ']' && ch2 == '[') || (ch == '}' && ch2 == '{') || (((info*)ae)->id == -1))
//			{
				ae = Pop(aux, ae);

				if(!VIDA(aux))
				{
					ae = Top(aux, ae);

					result = max(result, index - ((info*)ae)->id);
				}
				else
				{
					((info*)ae)->id = index;
					((info*)ae)->c = ch;
						
					Push(aux, ae);
				}
//			}
		}

		index++;
	}

	fprintf(f, "%d\n", result);

	return a;
}
