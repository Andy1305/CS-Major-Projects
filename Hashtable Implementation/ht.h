#include<stdio.h>

#include "list.h"


typedef unsigned int (*TFHash)(const char *str, unsigned int hash_length);
typedef struct {
	unsigned int size;
	TFHash hash;
	TList *v;
} Hashtable;


Hashtable *create_ht(unsigned int size, TFHash hash);
void add_word(Hashtable *ht, char *word);
void remove_word(Hashtable *ht, char *word);
char *find_word(Hashtable *ht, char *word);
void clear(Hashtable *ht);
void print_bucket(Hashtable *ht, int bucket, FILE *file);
void print(Hashtable *ht, FILE *file);
Hashtable *resize(Hashtable *ht, int mode);
