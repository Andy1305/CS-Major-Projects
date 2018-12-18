// Andrei Emanuel Galbenus - 322CB


#include "list.c"


int add_word(List t, char* word)
{
	int i, flag = 0;
    
	List aux = NULL, node = t, node2 = t;
    
    	for(i = 0; i < strlen(word); i++)
        {
    		if(node->sons == NULL)	// Daca nodul nu are niciun copil, se creeaza o celula noua.
    		{
    			node->sons = create_cell(word[i]);
    			
    			if(!node->sons)
    			{
    				printf("Error at create_cell()!!!\n");
    				
    				return -1;
    			}
    		
    			node2 = node;
    		
    			node = node->sons;

    			node->p = node2;
    		
    			if(i == (strlen(word) - 1))	// Daca e ultima litera, se marcheaza sfarsitul cuvantului.
    			{
    				node->end = 1;
    			}
    	        }
    		else
    		{
    			aux = node->sons;	// Nodul puncteaza catre lista copiilor.
    		
    			while(aux)
    			{
    				if(aux->info == word[i])	// S-a gasit simbolul.
    				{
    					node = aux;
    				
    					flag = 1;
    				
    					if(i == (strlen(word) - 1))
    					{
    						node->end = 1;
    					}
    				
    					break;
    			        }
    			
    				aux = aux->urm;
    			}
    		
    			if(flag == 0)	// Daca simbolul nu exista deja in trie.
    			{
    				if(insert(&node->sons, word[i]) == -1)
    				{
    					printf("Error at insert()!!!\n");
    				
    					return -1;
    				}
    			
    				aux = node->sons;
    			
    				while(aux)	// Se cauta simbolul nou adaugat.
    				{
    					if(aux->info == word[i])
    					{
    						break;
    					}
    				
    					aux = aux->urm;
    				}
    			
    				aux->p = node;
    			
    				node = aux;
    			
    				flag = 0;
    			
    				if(i == (strlen(word) - 1))	// Daca s-a ajuns la sfarsitul cuvantului, se marcheaza prin end = 1.
   				{
    					while(aux)
    					{
    						if(aux->info == word[i])
    						{
    							aux->end = 1;
    						
    							break;
    						}
    					
    						aux = aux->urm;
    					}
    				} 
    			}
    		
    			flag = 0;
    		}
	}
    
	return 0;
}


int remove_word(List t, char* word)
{
	int i;

	List node = t, aux = NULL, aux2 = NULL;
	
	for(i = 0; i < strlen(word); i++) // La finalul forului, ne aflam in nodul cu ultimul simbol din cuvant.
	{
		aux = node->sons;
		
		while(aux)	// Se cauta simbolul.
		{
			if(aux->info == word[i])
			{
				node = aux;
				
				break;
			}
			
			aux = aux->urm;
		}
		
		if(aux == NULL)
		{
			printf("Cuvantul nu exista\n");
			
			return 0;
		}
	}
	
	while(node->info != '\0')	// Cat timp nu am ajuns la radacina.
	{
		if(node->end == 1 && node->sons == NULL)	// Daca e final de cuvant si nu mai am alt cuvant dupa.
		{
			aux2 = node;
			
			node = node->p;	// Se revine la nodul parinte.
			
			node->end = 1;
			
			if(delete(&node->sons, aux2->info) == -1)	// Se elimina nodul.
			{
				printf("Error at delete()!!!\n");
				
				return -1;
			}
			
			aux2 = NULL;
		}
		else if(node->end == 1 && node->sons != NULL)	// Daca e final de cuvant si mai am alt cuvant dupa.
		{
			node->end = 0;	// Elimin sfarsitul cuvantului.
			
			break;
		}
	}
	
	return 0;
}


int find(List t, char* word)
{
	int i;
	
	List aux = t->sons;
	
	for(i = 0; i < strlen(word); i++)
	{
		while(aux)
		{
			if(aux->info == word[i])
			{
				if((i == strlen(word) - 1) && (aux->end == 1)) // Daca am ajuns la finalul cuvantului.
				{
					return 1;
				}
				
				aux = aux->sons;
			
				break;
			}
			
			aux = aux->urm;
		}
	}
	
	return 0;
}


char* find_longest_prefix(List t, char* word)
{
	int i, flag = 0;
	
	char* pref = (char*)malloc(strlen(word));
	
	if(!pref)
	{
		printf("Error at malloc()!!!\n");
		
		return NULL;
	}
	
	List aux = t->sons;
	
	for(i = 0; i < strlen(word); i++)
	{
		while(aux)
		{
			if(aux->info == word[i])
			{
				pref[i] = aux->info;	// Daca s-a gasit litera, se retine in pref.
				
				aux = aux->sons;
			
				flag = 1;	// In caz ca o litera nu se gaseste, flagul va fi 0 si se va iesi din for.
			
				break;
			}
			
			aux = aux->urm;
		}
		
		if(flag == 1)
		{
			flag = 0;
		}
		else
		{
			break;
		}
	}
	
	pref[i] = '\0';
	
	if(i == 0)
	{
		strcpy(pref, "None");
	}
	
	return pref;
}


// Functie pe care o folosesc pentru a gasi recursiv toate cuvintele care incep cu un anumit prefix.
void find_all(List aux, char* word, char* res, int pos)
{
	if(!aux)
	{
		return;
	}
	
	while(aux)
	{
		if(aux->end == 1)	// Daca suntem la finalul cuvantului, il scriem in res, ce contine toate cuvintele.
		{
			word[pos] = aux->info;

			word[pos + 1] = '\0';

			strcat(res, word);	// Se adauga cuvantul la rezultat.

			strcat(res, " ");

			find_all(aux->sons, word, res, pos + 1);
			
			aux = aux->urm;
		}
		else                   // Daca nu, scriem doar litera si mergem mai departe.
		{
			word[pos] = aux->info;

			find_all(aux->sons, word, res, pos + 1);
			
			aux = aux->urm;
		}
	}
}


char* find_all_with_prefix(List t, char* pref, int n, int length) 	// n = numar de cuvinte 	length = lungimea celui mai lung cuvant 
{
	int i, flag = 0, pos = 0;
	
	char* word;
	char* res;
	
	List aux = t->sons;
	
	word = malloc(length * sizeof(char));
	
	if(!word)
	{
		printf("Error at malloc()!!!\n");
		
		return NULL;
	}
	
	memset(word, 0, length);
	
	res = malloc(((n - 1) + length * n) * sizeof(char));
	
	if(!res)
	{
		printf("Error at malloc()!!!\n");
		
		return NULL;
	}
	
	memset(res, 0, (n - 1) + length * n);
	
	strcpy(res, "");

	if(strlen(pref) > 0)
	{
		for(i = 0; i < strlen(pref); i++)	// Caut prefixul in trie si il pun in word.
		{
			while(aux)
			{
				if(aux->info == pref[i])
				{
					word[i] = aux->info;
					
					if((i == strlen(word) - 1) && (aux->end == 1))
					{
						strcpy(res, word);
			
						strcat(res, " ");
					}
				
					aux = aux->sons;
			
					flag = 1;
			
					break;
				}
			
				aux = aux->urm;
			}
			
			if(flag == 1)
			{
				flag = 0;
			}
			else
			{
				break;
			}
		}

		if(word[0] == 0 || strlen(word) < strlen(pref))	// Daca prefixul nu este in trie.
		{
			strcpy(res, "None");
			
			return res;
		}
	
		find_all(aux, word, res, i);
	}
	else    // Afisez toate cuvintele.
	{
		find_all(aux, word, res, 0);	// Caut recursiv toate cuvintele care incep cu prefixul.
	}

	for(i = 0; i < strlen(res); i++)
	{
		if(res[i] == ' ')
		{
			pos = i;
		}
	}
	
	res[pos] = '\0';

	return res;	// Contine toate cuvintele.
}


double mean_length(List t, char* pref, int n, int length)
{
	int i, j = 0, count = 0;
	
	double mean = 0;
	
	char aux[300];
	
	char* res = malloc(((n - 1) + length * n) * sizeof(char));
	
	if(!res)
	{
		printf("Error at malloc()!!!\n");
		
		return -1;
	}
	
	memset(res, 0, (n - 1) + length * n);
	memset(aux, 0, 300);
	
	res = find_all_with_prefix(t, pref, n, length);	// Gasesc toate cuvintele care incep cu un anumit prefix.

	if(strcmp(res, "None") == 0)	// Daca nu e niciunul, returnez 0.
	{
		return 0;
	}

	for(i = 0; res[i] != '\0'; i++, j++)	// Extrag cate un cuvant si adun lungimea lui la mean.
	{
		if(res[i] != ' ')
		{
			aux[j] = res[i];
		}
		else
		{
			strcat(aux, "\0");
			
			mean += strlen(aux);
			
			memset(aux, 0, 300);
			
			j = -1;
			
			count++;	// Retine numarul de cuvinte.
		}
	}
	
	strcat(aux, "\0");
	
	mean += strlen(aux);	// Adun lungimea ultimului cuvant.

	mean = mean / (++count);
	
	return mean;
}
