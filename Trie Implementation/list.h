// Andrei Emanuel Galbenus - 322CB


typedef struct list
{
	int end;		// 1 daca e sfarsit de cuvant, 0 altfel.
	
	char info;		// Simbolul.

	struct list* p;		// Parinte.
	struct list* sons;	// Copii.
	struct list* urm;  	// Celula urmatoare.
} Cell, *List, **AList;


List create_cell(char info);
int insert(AList l, char info);
int delete(AList l, char info);
