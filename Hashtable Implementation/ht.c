#include "ht.h"


/* Aloca si initializeaza un obiect de tip Hashtable. */
Hashtable *create_ht(unsigned int size, TFHash hash)
{
	int i;
	Hashtable *ht = (Hashtable *)calloc(1, sizeof(Hashtable));

	DIE(ht == NULL, "Could not allocate memory.\n");
	ht->size = size;
	ht->hash = hash;
	ht->v = (TList *)calloc(size, sizeof(TList));

	if (ht->v == NULL)
		free(ht);
	DIE(ht->v == NULL, "Could not allocate memory.\n");

	for (i = 0; i < ht->size; i++)
		ht->v[i] = NULL;

	return ht;
}


/*
Adauga un cuvant in hash table.
Foloseste functia hash pentru a gasi indexul listei
si functia insert_cell() pentru a-l introduce.
Daca cuvantul exista deja, acesta nu mai e reintrodus.
*/
void add_word(Hashtable *ht, char *word)
{
	int bucket = ht->hash(word, ht->size);

	if (strcmp(find_word(ht, word), "True\n") == 0)
		return;

	insert_cell(&(ht->v[bucket]), word);
}


/* Sterge din hash table intrarea cu informatia word. */
void remove_word(Hashtable *ht, char *word)
{
	int bucket = ht->hash(word, ht->size);

	remove_cell(&ht->v[bucket], word);
}


/* Cauta un cuvant in hash table, returnand "True" daca il gaseste, "False" altfel. */
char *find_word(Hashtable *ht, char *word)
{
	int bucket = ht->hash(word, ht->size);

	if (strcmp(find_info(ht->v[bucket], word), "True\n") == 0)
		return "True\n";
	return "False\n";
}


/*
Parcurge fiecare lista din hash table si sterge fiecare intrare,
folosind functia delete_list().
*/
void clear(Hashtable *ht)
{
	int i;

	for (i = 0; i < ht->size; i++)
		delete_list(&(ht->v[i]));
}


/* Afiseaza informatia din fiecare celula din lista cu un anumit index. */
void print_bucket(Hashtable *ht, int bucket, FILE *file)
{
	print_list(ht->v[bucket], file);
}


/*
Parcurge bucketurile hash tabelului si printeza cuvintele din ele,
folosind functia print_bucket().
*/
void print(Hashtable *ht, FILE *file)
{
	int i;

	for (i = 0; i < ht->size; i++)
		print_bucket(ht, i, file);
}


/*
Dubleaza (mode 1) sau injumatateste (mode 2) hash tabelul.
Creeaza un nou hash table, cu noua dimensiune, parcurge
listele celui vechi si adauga fiecare element in cel nou.
Totodata, elibereaza si memoria celui vechi.
Metoda returneaza noul hash table.
*/
Hashtable *resize(Hashtable *ht, int mode)
{
	int i;
	TList it, aux;
	Hashtable *new_ht;

	if (mode == 1)
		new_ht = create_ht(ht->size / 2, ht->hash);
	else
		new_ht = create_ht(ht->size * 2, ht->hash);

	for (i = 0; i < ht->size; i++) {
		it = ht->v[i];
		while (it != NULL) {
			add_word(new_ht, it->info);
			aux = it;
			it = it->next;
			free(aux->info);
			free(aux);
		}
	}

	free(ht->v);
	free(ht);
	return new_ht;
}
