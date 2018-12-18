#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "utils.h"

typedef struct cell {
	char *info;
	struct cell *next;
} TCell, *TList, **AList;


TList create_cell(char *info);
void insert_cell(AList L, char *info);
void remove_cell(AList L, char *info);
void delete_list(AList L);
void print_list(TList L, FILE *file);
char *find_info(TList L, char *word);
