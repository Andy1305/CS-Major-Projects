#include "list.h"


/* Aloca memorie pentru o celula a listei si adauga informatia in ea. */
TList create_cell(char *info)
{
	TList cell = (TList)calloc(1, sizeof(TCell));

	DIE(cell == NULL, "Could not allocate memory.\n");
	cell->info = (char *)calloc(strlen(info)+10, sizeof(char));
	memset(cell->info, 0, strlen(info)+10);
	strcpy(cell->info, info);
	cell->next = NULL;
	return cell;
}

/*
Insereaza un cuvant intr-o lista. Creeaza o celula noua.
Daca lista este vida, capatul listei va fi noua celula.
Altfel, noua celula este adaugata la sfarsitul liste.
*/
void insert_cell(AList L, char *info)
{
	TList it = *L, head = NULL, new;

	new = create_cell(info);
	if (*L == NULL) {
		*L = new;
		return;
	}

	for (; it != NULL; it = it->next)
		head = it;
	head->next = new;
}


/*
Elimina o celula din lista, cautand-o in fiecare lista.
Daca celula de eliminat este prima si singura lista va deveni nula.
Altfel, se va elimina doar celula.
In ambele cazuri, memoria este eliberata.
*/
void remove_cell(AList L, char *info)
{
	TList it = *L, head = NULL;

	for (; it != NULL; it = it->next) {
		if (strcmp(it->info, info) == 0) {
			// daca e prima celula.
			if (head == NULL) {
				head = it;
				// daca e prima si singura celula.
				if (head->next == NULL) {
					*L = NULL;
					free(it->info);
					free(it);
					return;
				}
				// daca e prima, dar mai sunt altele, dupa.
				*L = it->next;
				free(it->info);
				free(it);
				return;
			}
			break;
		}
		head = it;
	}

	if (head != NULL) {
		head->next = it->next;
		free(it->info);
		free(it);
	}
}

/*
Parcurge o lista si elimina fiecare element, eliberand memoria.
La final, lista va fi nula.
*/
void delete_list(AList L)
{
	TList head = *L, it = *L;

	if (it == NULL)
		return;

	while (it != NULL) {
		head = it;
		it = it->next;
		free(head->info);
		free(head);
	}
	*L = NULL;
}

/* Afiseaza informatiile dintr-o lista. */
void print_list(TList L, FILE *file)
{
	TList it = L;

	for (; it != NULL; it = it->next)
		fprintf(file, "%s ", it->info);

	if (L != NULL)
		fprintf(file, "\n");
}

/* Cauta un cuvant intr-o lista. Daca-l gaseste, returneaza "True", alfel "False". */
char *find_info(TList L, char *info)
{
	TList it = L;

	for (; it != NULL; it = it->next) {
		if (strcmp(it->info, info) == 0)
			return "True\n";
	}

	return "False\n";
}
