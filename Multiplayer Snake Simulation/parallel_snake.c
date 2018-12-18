#include<string.h>
#include<stdlib.h>

#include "main.h"


// Functia returneaza pozitia in care un serpisor urmeaza sa se mute.
void get_next_pos(struct coord head, char direction, int num_lines, 
		  int num_cols, struct coord* next_pos1)
{
	if(direction == 'N')
	{
		if(head.line == 0)
		{
			next_pos1->line = num_lines - 1;
			next_pos1->col = head.col;
			
			return;
		}	
		
		next_pos1->line = head.line - 1;
		next_pos1->col = head.col;

		return;
	}
	
	if(direction == 'S')
	{
		if(head.line == num_lines - 1)
		{
			next_pos1->line = 0;
			next_pos1->col = head.col;
			
			return;
		}	
		
		next_pos1->line = head.line + 1;
		next_pos1->col = head.col;
		
		return;
	}
	
	if(direction == 'V')
	{
		if(head.col == 0)
		{
			next_pos1->line = head.line;
			next_pos1->col = num_cols - 1;
			
			return;
		}

		next_pos1->line = head.line;
		next_pos1->col = head.col - 1;
		
		return;
	}
	
	if(direction == 'E')
	{
		if(head.col == num_cols - 1)
		{
			next_pos1->line = head.line;
			next_pos1->col = 0;

			return;
		}
		
		next_pos1->line = head.line;
		next_pos1->col = head.col + 1;

		return;
	}
}


// Functia returneaza pozitia ultimei celule a serpisorului.
void get_tail_pos(int num_lines, int num_cols, int** world, struct snake* s)
{
	struct coord pos, last_pos;
	
	pos.line = s->head.line;
	pos.col = s->head.col;
	last_pos.line = s->head.line;
	last_pos.col = s->head.col;
	
	while(1)
	{
		// stanga
		if(pos.col == 0)
		{
			if(world[pos.line][num_cols - 1] == s->encoding && 
			   last_pos.col != num_cols - 1)
			{
				last_pos.col = pos.col;
				pos.col = num_cols - 1;

				continue;
			}
		}
		else
		{
			if(world[pos.line][pos.col - 1] == s->encoding && 
			   last_pos.col != pos.col - 1)
			{
				last_pos.col = pos.col;
				pos.col -= 1;
				
				continue;
			}
		}
				
		// jos
		if(pos.line == num_lines - 1)
		{
			if(world[0][pos.col] == s->encoding && 
			   last_pos.line != 0)
			{
				last_pos.line = pos.line;
				pos.line = 0;
					
				continue;
			}
		}
		else
		{
			if(world[pos.line + 1][pos.col] == s->encoding && 
			   last_pos.line != pos.line + 1)
			{
				last_pos.line = pos.line;
				pos.line += 1;
				
				continue;
			}
		}
				
		// dreapta
		if(pos.col == num_cols - 1)
		{
			if(world[pos.line][0] == s->encoding && 
			   last_pos.col != 0)
			{
				last_pos.col = pos.col;
				pos.col = 0;
					
				continue;
			}
		}
		else
		{
			if(world[pos.line][pos.col + 1] == s->encoding && 
			   last_pos.col != pos.col + 1)
			{
				last_pos.col = pos.col;
				pos.col += 1;
					
				continue;
			}
		}
	
		// sus
		if(pos.line == 0)
		{
			if(world[num_lines - 1][pos.col] == s->encoding && 
			   last_pos.line != num_lines - 1)
			{
				last_pos.line = pos.line;
				pos.line = num_lines - 1;
					
				continue;
			}
		}
		else
		{
			if(world[pos.line - 1][pos.col] == s->encoding && 
			   last_pos.line != pos.line - 1)
			{
				last_pos.line = pos.line;
				pos.line -= 1;
					
				continue;
			}
		}
		
		s->tail.line = pos.line;
		s->tail.col = pos.col;
		
		return;
	}
}

void run_simulation(int num_lines, int num_cols, int **world, int num_snakes,
	            struct snake *snakes, int step_count, char *file_name) 
{
	int i, j, k, collision_flag = 0;
	int** aux;	// a[i][j] = snake encoding, daca un serpisor urmeaza sa se mute in world[i][j].
	
	aux = (int**)calloc(num_lines, sizeof(int*));
	
	#pragma omp parallel for
	for(i = 0; i < num_lines; i++)
	{
		aux[i] = calloc(num_cols, sizeof(int));

		memset(aux[i], 0, sizeof(int) * num_cols);
	}

	for(k = 0; k < step_count; k++)
	{
		// Calculez unde si daca pot sa ma mut pentru fiecare serpisor.
		#pragma omp parallel for
		for(i = 0; i < num_snakes; i++)
		{
			get_next_pos(snakes[i].head, snakes[i].direction, num_lines, 
			             num_cols, &snakes[i].next_pos);		// obtin celula din fata serpisorului
			get_tail_pos(num_lines, num_cols, world, &snakes[i]);	// obtin coada
			
			if(world[snakes[i].next_pos.line][snakes[i].next_pos.col] == 0)	// daca celula din fata e libera
			{
				if(aux[snakes[i].next_pos.line][snakes[i].next_pos.col] == 0)	// daca aux e libera, se poate muta.
				{
					aux[snakes[i].next_pos.line][snakes[i].next_pos.col] = snakes[i].encoding;
				}
				
				if(aux[snakes[i].next_pos.line][snakes[i].next_pos.col] != snakes[i].encoding)	// altfel, coliziune
				{
					collision_flag = 1;
				}
			}
			else	// daca nu e libera
			{
				for(j = 0; j < num_snakes; j++)
				{
					if(snakes[i].next_pos.line == snakes[j].head.line &&
					   snakes[i].next_pos.col == snakes[j].head.col && i != j)	// daca e capul unui serpisor
					{
						if(snakes[i].next_pos.line == snakes[j].head.line &&
						   snakes[i].next_pos.col == snakes[j].head.col &&
						   snakes[j].next_pos.line == snakes[i].head.line &&
						   snakes[j].next_pos.col == snakes[i].head.col)
						{
							collision_flag = 1;
						}
					
						if(snakes[j].head.line != snakes[j].tail.line ||
						   snakes[j].head.col != snakes[j].tail.col)
						{
							collision_flag = 1;
						}
					}
					else // daca nu e capul unui serpisor.
					{
						if((snakes[j].tail.col < snakes[i].head.col &&	// daca serpisorii sunt in "T"
						    snakes[j].head.col > snakes[i].head.col) ||
						   (snakes[j].tail.col > snakes[i].head.col && 
						    snakes[j].head.col < snakes[i].head.col) ||
						   (snakes[j].tail.line < snakes[i].head.line && 
						    snakes[j].head.line > snakes[i].head.line) ||
						   (snakes[j].tail.line > snakes[i].head.line && 
						    snakes[j].head.line < snakes[i].head.line))
						{
							collision_flag = 1;
						}
					}
				}
			}
		}
	
		if(collision_flag == 1)
		{
			return;
		}
			
		//Fac mutarile.
		#pragma omp parallel for
		for(i = 0; i < num_snakes; i++)
		{
			aux[snakes[i].next_pos.line][snakes[i].next_pos.col] = 0;	// resetez matricea
			
			world[snakes[i].tail.line][snakes[i].tail.col] = 0;	// sterg coada
			
			world[snakes[i].next_pos.line][snakes[i].next_pos.col] = snakes[i].encoding;	// mut capul
		
			snakes[i].head.line = snakes[i].next_pos.line;	// actualizez linia capului
			snakes[i].head.col = snakes[i].next_pos.col;	// actualizez coloana capului
		}
	}
}
