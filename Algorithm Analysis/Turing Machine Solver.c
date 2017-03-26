#include<stdio.h>
#include<string.h>
#include<stdlib.h>


char* parse(char *v) //Sterge spatiul de dinainte de string.
{
	int i;

	for(i = 0; i < strlen(v); i++)
	{
		v[i] = v[i + 1];
	}

	v[strlen(v)] = '\0';

	return v;
}


int main()
{
	FILE *f1, *f2, *f3; 
	char *initial_stages, *final_stages, *initial_stage, *initial_string, *empty_space, *current_stage, *next_stage, *read_symbol, *write_symbol, *direction, *temp;
	char **transitions;
	long long i, j, k, N, M, P, count = 0, count2 = 0, nr = 0, a = 0;
		
	initial_stages = calloc(10000, sizeof(char));
	final_stages = calloc(10000, sizeof(char));
	initial_stage = calloc(10000, sizeof(char));
	empty_space = calloc(10000, sizeof(char));
	current_stage = calloc(10000, sizeof(char));
	next_stage = calloc(10000, sizeof(char));
	read_symbol = calloc(10000, sizeof(char));
	write_symbol = calloc(10000, sizeof(char));
	direction = calloc(10000, sizeof(char));

	initial_string = calloc(10000, sizeof(char));
	
	f1 = fopen("tape.in", "rt");
	f2 = fopen("tm.in", "rt");

	fscanf(f1, "%s", initial_string);

	fclose(f1);

	fscanf(f2, "%lli", &N);

	fgets(initial_stages, 10000, f2); //Toate starile initiale.
	
	strcpy(initial_stages, parse(initial_stages));

	fscanf(f2, "%lli", &M);

	fgets(final_stages, 10000, f2);
	
	strcpy(final_stages, parse(final_stages));

	fscanf(f2, "%s", initial_stage); //Starea initiala.

	fscanf(f2, "%lli", &P);

	fgets(empty_space, 10000, f2);

	transitions = calloc(P, sizeof(char*));

	for(i = 0; i < P; i++)
	{
		transitions[i] = calloc(10000, sizeof(char));

		fgets(transitions[i], 10000, f2);
	}

	fclose(f2);	

	for(i = 0; i < strlen(initial_string); i++)
	{
		if(initial_string[i] == '#')
		{
			count2++; 
		}
		else
		{
			break;
		}
	}

	if(count2 == strlen(initial_string))
	{
		f3 = fopen("tape.out", "wt");
		
		fprintf(f3, "%s", initial_string);

		fclose(f3);

		return 0;
	}
	
	temp = calloc(10000, sizeof(char)); 

	for(i = count2; initial_string[i] != '\0'; i++)
	{
		count = 0;

		temp[0] = initial_string[i];
		temp[1] = '\0'; 

		for(j = 0; j < P; j++)
		{
			nr = 0;

			for(k = 0; k < 10000; k++)
			{
				if(transitions[j][k] != ' ')
				{
					current_stage[k] = transitions[j][k];   //Retin starea curenta din tranzitie.
					
					nr++;   //Retine pozitia la care trebuie sa continui citirea.
				}
				else
				{
					current_stage[k] = '\0';

					nr++;

					break;
				}
			}

			read_symbol[0] = transitions[j][nr];
			read_symbol[1] = '\0';

			nr = nr + 2;

			a = 0;

			for(k = nr; k < 10000; k++)
			{
				if(transitions[j][k] != ' ')
				{
					next_stage[a] = transitions[j][k];   //Retin starea urmatoare din tranzitie.
				
					a++;   //Indexul pentru next_stage.
					nr++;
				}
				else
				{
					next_stage[a] = '\0';

					nr++;

					break;
				}
			}

			write_symbol[0] = transitions[j][nr];
			write_symbol[1] = '\0';

			nr = nr + 2;

			direction[0] = transitions[j][nr];
			direction[1] = '\0';

			if(strcmp(initial_stage, current_stage) == 0)
			{
				if(strcmp(temp, read_symbol) == 0)
				{
					initial_string[i] = write_symbol[0];

					strcpy(initial_stage, next_stage);

					if(direction[0] == 'H')
					{
						i = i - 1;
					}

					if(direction[0] == 'L')
					{
						i = i - 2;
					}
					
					break;
				}
			}

			count++;

			if((count == P) && (strstr(final_stages, initial_stage) == NULL))
			{
				f3 = fopen("tape.out", "wt");
				
				fprintf(f3, "Se agata!");

				fclose(f3);

				return 0;
			}
		}
	}

	f3 = fopen("tape.out", "wt");	

	fprintf(f3, "%s", initial_string);

	fclose(f3);

	return 0;
}
