// Andrei Emanuel Galbenus - 322CB


#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#include "trie.c"


// Extrage cuvantul de dupa operatie.
char* get_string(char* str, int pos)
{
	int i;
	
	char* aux = (char*)calloc(300, sizeof(char));
	
	if(!aux)
	{
		printf("Error at malloc()!!!\n");
		
		return NULL;
	}
	
	for(i = pos; i < strlen(str); i++)
	{
		aux[i - pos] = str[i];
	}
	
	aux[i - pos] = '\0';
	
	return aux;
}


int main(int argc, char** argv)
{
	int i, N, count = 0, length = 0;
	
	char** op;

	FILE* in = fopen(argv[1], "r");
	
	List t = create_cell('\0'); 	// Radacina.
	
	if(!t)
	{
		printf("Error at create_cell()!!!\n");
		
		return 0;
	}
	
	fscanf(in, "%d", &N);

	op = (char**)calloc(N, sizeof(char*));
	
	if(!op)
	{
		printf("Error at malloc()!!!\n");
		
		return 0;
	}

	for(i = 0; i < N; i++)
	{
		op[i] = (char*)calloc(300, sizeof(char));
		
		if(!op[i])
		{
			printf("Error at malloc()!!!\n");
		
			return 0;
		}

		if(i == 0)	// Citesc ce ramane de la fscanful anterior.
		{
			fgets(op[i], 300, in);
		}
		
		fgets(op[i], 300, in);
		
		op[i][strlen(op[i]) - 1] = '\0';
	}
	
	fclose(in);
	
	FILE* out = fopen(argv[2], "w");

	for(i = 0; i < N; i++)	// Apelez functia corespunzatoare, in functie de fiecare operatie.
	{
		if(strstr(op[i], "add"))	// Operatia add.
		{
			add_word(t, get_string(op[i], 4));
			
			if(length < strlen(get_string(op[i], 4)))
			{
				length = strlen(get_string(op[i], 4));	// Lungimea celui mai mare cuvant.
			}
			
			count++;	// Numarul de cuvinte.
			
			continue;
		}
		else if(strstr(op[i], "remove"))	// Operatia remove.
		{
			remove_word(t, get_string(op[i], 7));
		
			continue;
		}
		else if(strstr(op[i], "find_longest_prefix"))	// Operatia find_longest_prefix.
		{
			fprintf(out, "%s\n", find_longest_prefix(t, get_string(op[i], 20)));
		
			continue;
		}
		else if(strstr(op[i], "find_all_with_prefix"))	// Operatia find_add_with_prefix.
		{
			fprintf(out, "%s\n", find_all_with_prefix(t, get_string(op[i], 21), count, length));		
		
			continue;
		}
		else if(strstr(op[i], "find"))	// Operatia find.
		{
			if(find(t, get_string(op[i], 5)))
			{
				fprintf(out, "True\n");
			}
			else
			{
				fprintf(out, "False\n");
			}
		
			continue;
		}
		else if(strstr(op[i], "mean_length"))	// Operatia mean_length.
		{
			if(mean_length(t, get_string(op[i], 12), count, length) == 0)
			{
				fprintf(out, "0\n");
			}
			else
			{
				fprintf(out, "%.3f\n", mean_length(t, get_string(op[i], 12), count, length));
			}
		}
	}
	
	fclose(out);
	
	return 0;
}
