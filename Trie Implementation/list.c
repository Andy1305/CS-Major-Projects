// Andrei Emanuel Galbenus - 322CB


#include "list.h"


// Aloca o celula.
List create_cell(char info)
{
	List aux = (List)malloc(sizeof(Cell));

	if(!aux)
	{
		printf("Error at malloc()!!!\n");

		return NULL;
	}
	
	aux->end = 0;
	aux->info = info;
	aux->p = NULL;
	aux->urm = NULL;
	aux->sons = NULL;

	return aux;
}


// Insereaza o celula in lista.
int insert(AList l, char info)
{
	List p = *l, aux = create_cell(info), aux2 = NULL;

	if(!aux)
	{
		printf("Error at create_cell()!!!\n");

		return -1;
	}
	
	if(p)	// Daca lista nu e goala.
	{
		if(info < p->info)	// Se introduce info inainte.
		{
			*l = aux;

			aux->urm = p;
		}
		else
		{
			if(info == p->info)
			{
				return 0;
			}
			
			// Se introduce info dupa.
			while(p->urm)
			{
				if(info > p->urm->info)
				{
					p = p->urm;
				}
				else if(info < p->urm->info)
				{
					aux2 = p->urm;
					
					p->urm = aux;
					
					aux->urm = aux2;
					
					return 0;
				}
			}
			
			if(!p->urm)	// Daca s-a ajuns la finalul listei.
			{
				p->urm = aux;
				
				aux->urm = NULL;
			} 		
		}
	}
	else // Daca lista e goala.
	{
		*l = aux;
	}
		
	return 0;
}


// Sterge o celula din lista.
int delete(AList l, char info)
{
	List u = NULL, aux = *l;

	if(!aux)
	{
		printf("Lista este vida in Sterge()!!!\n");

		return -1;
	}

	if(aux->urm)
	{
		while(aux)	// Se cauta celula.
		{
			if(aux->info == info)
			{
				if(u == NULL)	// Daca e prima.
				{
					*l = (*l)->urm;

					free(aux);

					aux = NULL;
				}
				else
				{
					u->urm = aux->urm;
				
					free(aux);
				
					aux = NULL;
				}
							
				return 0;
			}
			else
			{
				u = aux;

				aux = aux->urm;
			}
		}
	}		
	else if(!aux->urm && aux->info == info)	// Daca e o singura celula ce contine informatia egala cu info.
	{
		*l = (*l)->urm;

		return 0;
	}	
	
	printf("Celula nu a fost gasita!!!\n");	// Daca ajunge aici, inseamna ca nu s-a gasit celula.
	
	return 0;
}
