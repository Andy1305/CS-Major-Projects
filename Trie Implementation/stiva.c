// OK
#ifndef _INCLUDE_


#define _INCLUDE_


#include<stdio.h>


#endif


#include "stiva.h"


#ifndef _FUNCTIONS_


#define _FUNCTIONS_


int min(int a, int b)
{
	return (a - b) ? b : a;
}


int max(int a, int b)
{
	if(a > b)
	{
		return a;
	}

	if(b > a)
	{
		return b;
	}

	return 0;
	//return (a - b) ? a : b;
}


#endif


void* InitS(int d, ...)
{
	ASt s;

	va_list ap;

	s = (ASt)malloc(sizeof(TStiva));

	if(!s)
	{
		printf("Error at malloc()!!!\n");

		return NULL;
	}

	va_start(ap, d);

	va_end(ap);

	s->dime = d;
	s->vf = NULL;

	return (void*) s;
}


int Push(void* a, void* ae)
{
	if(a == NULL)
	{
		a = InitS(sizeof(info));

		if(!a)
		{
			printf("Error at InitS()!!!\n");

			return -1;
		}
	}

	if(InserareS(&VF(a), ae, DIME(a)) == -1)
	{
		printf("Errot at InserareS()!!!\n");

		return -1;
	}

	return 0;
}


void* Pop(void* a, void* ae)
{
	if(VIDA(a))
	{
//		printf("Stiva e vida!!!\n");

		return NULL;
	}

	ae = Sterge(&VF(a), DIME(a));

	return ae;
}


void* Top(void* a, void* ae)
{
	ae = Pop(a, ae);
	
	Push(a, ae);

	return ae;
}


void* SortS(void* a)
{
	void* ae;
	void* ae2;
	void* aux = InitS(DIME(a));
	void* sorted = InitS(DIME(a));

	while(!VIDA(a))
	{
		ae = Pop(a, ae);

		while(!VIDA(a))
		{
			ae2 = Pop(a, ae2);

			if(((info*)ae)->id >= ((info*)ae2)->id)
			{
				Push(aux, ae2);
			}
			else
			{
				Push(a, ae);

				ae = ae2;
			}
		}

		Push(sorted, ae);

		Rastoarna(a, aux);
	}

	Rastoarna(a, sorted);

	return a;
}


int Rastoarna(void* ad, void* as)
{
	void* ae = NULL;

	while(!VIDA(as))
	{
		ae = Pop(as, ae);

		Push(ad, ae);
	}

	return 0;
}


void* Copiaza(void* ad, void* as)
{
	void* ae = NULL;
	void* aux = InitS(DIME(as));

	while(!VIDA(as))
	{
		ae = Pop(as, ae);

		Push(ad, ae);
		Push(aux, ae);
	}

	Rastoarna(as, aux);
	Rastoarna(aux, ad);

	return aux;
}


void PrintS(void* a, FILE* f)
{
	void* aux = InitS(sizeof(info));
	void* ae;

	if(!aux)
	{
		printf("Error at InitS()!!!\n");

		return;
	}

	Rastoarna(aux, a);
	
	fprintf(f, "\"");
	
	while(!VIDA(aux))
	{
		ae = Pop(aux, ae);

		fprintf(f, "%c", ((info*)ae)->c);

		Push(a, ae);
	}

	fprintf(f, "\"");
}


void* CorrectS(void* a, FILE* f)
{
	int result = 0, index = 0;

	char ch;

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

	aux2 = Copiaza(aux2, a);
	
	Rastoarna(aux3, a);

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
			if(ch == ')')
			{
				ae = Top(aux, ae);

				ch = ((info*)ae)->c;

				if(ch == '(')
				{
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
				}
			}

			if(ch == ']')
			{
				ae = Top(aux, ae);

				ch = ((info*)ae)->c;

				if(ch == '[')
				{
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
				}
			}

			if(ch == '}')
			{
				ae = Top(aux, ae);

				ch = ((info*)ae)->c;

				if(ch == '{')
				{
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
								
						Push(aux, &index);
					}
				}
			}
		}

		index++;
	}
	a = Copiaza(a, aux2);

	fprintf(f, "%d\n", result);
	
	return a;
}
