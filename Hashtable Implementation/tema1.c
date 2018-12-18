#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "utils.h"
#include "hash.h"
#include "ht.h"

#define COMMAND_SIZE	20000

/*
Executa o comanda primita ca parametru.
Totodata o parseaza, impartind-o pe componente.
In functie de comanda, apeleza functia specifica.
Deschide si inchide fisiere, unde este cazul.
*/
void execute_command(Hashtable **addrht, char *line)
{
	int bucket;
	char *word, *file, *delim = " ", *res = NULL;
	FILE *out_file;
	Hashtable *ht = *addrht;

	if (strncmp(line, "add", strlen("add")) == 0) {
		word = strtok(line, delim);
		word = strtok(NULL, delim);
		DIE(word == NULL, "add command not correct.\n");
		add_word(ht, word);
	} else if (strncmp(line, "remove", strlen("remove")) == 0) {
		word = strtok(line, delim);
		if (strlen(word) != strlen("remove"))
			DIE(1, "remove: Bad command.\n");

		word = strtok(NULL, delim);
		DIE(word == NULL, "remove command not correct.\n");
		remove_word(ht, word);
	} else if (strncmp(line, "find", strlen("find")) == 0) {
		word = strtok(line, delim);
		if (strlen(word) != strlen("find"))
			DIE(1, "find: Bad command.\n");

		word = strtok(NULL, delim);
		DIE(word == NULL, "find command not correct.\n");
		file = strtok(NULL, delim);
		res = find_word(ht, word);
		if (file == NULL) {
			fprintf(stdout, "%s", res);
		} else if (file != NULL) {
			out_file = fopen(file, "a");
			fprintf(out_file, "%s", res);
			fclose(out_file);
		}
	} else if (strncmp(line, "clear", strlen("clear")) == 0) {
		word = strtok(line, delim);
		if (strlen(word) != strlen("clear"))
			DIE(1, "clear: Bad command.\n");

		word = strtok(NULL, delim);
		DIE(word != NULL, "clear command not correct.\n");
		clear(ht);
	} else if (strncmp(line, "print_bucket", strlen("print_bucket")) == 0) {
		word = strtok(line, delim);
		if (strlen(word) != strlen("print_bucket"))
			DIE(1, "print_bucket: Bad command.\n");
		word = strtok(NULL, delim);
		DIE(word == NULL, "print_bucket command not correct.\n");
		bucket = atoi(word);
		DIE(strcmp(word, "0") != 0 && bucket == 0,
		    "print_bucket: invalid bucket number\n");
		file = strtok(NULL, delim);
		if (file == NULL) {
			print_bucket(ht, bucket, stdout);
		} else if (file != NULL) {
			out_file = fopen(file, "a");
			print_bucket(ht, bucket, out_file);
			fclose(out_file);
		}
	} else if (strncmp(line, "print", strlen("print")) == 0) {
		word = strtok(line, delim);
		file = strtok(NULL, delim);

		if (file == NULL) {
			print(ht, stdout);
		} else if (file != NULL) {
			out_file = fopen(file, "a");
			print(ht, out_file);
			fclose(out_file);
		}
	} else if (strncmp(line, "resize double",
		   strlen("resize double")) == 0) {
		if (strlen(line) != strlen("resize double"))
			DIE(1, "resize double: Bad command.\n");

		*addrht = resize(ht, 2);
	} else if (strncmp(line, "resize halve", strlen("resize halve")) == 0) {
		if (strlen(line) != strlen("resize halve"))
			DIE(1, "resize halve: Bad command.\n");

		*addrht = resize(ht, 1);
	} else {
		DIE(1, "Bad command.\n");
	}
}


/*
In main() se citesc comenzile din fisiere si se elibereaza hsah_tabelul
si restul memoriei, in final.
*/
int main(int argc, char **argv)
{
	int ht_size, nr_in_files, file_counter = 0;
	char *line, *ret_str;
	FILE *in_file;
	Hashtable *ht;

	line = calloc(COMMAND_SIZE, sizeof(char));
	DIE(argc < 2, "Not enough parameters.\n");
	ht_size = atoi(argv[1]);
	DIE(ht_size == 0, "Incorrect format of the second paramter.\n");
	ht = create_ht(ht_size, hash);

	if (argc == 2)
		nr_in_files = 0;
	else
		nr_in_files = argc - 2;

	do {
		if (nr_in_files == 0) {
			in_file = stdin;
		} else {
			in_file = fopen(argv[2 + file_counter], "r");
			DIE(in_file == NULL, "Could not open input file.\n");
		}

		while ((ret_str = fgets(line, COMMAND_SIZE, in_file)) != NULL) {
			DIE(strlen(line) == 0, "Empty string is not valid.");
			if (line[strlen(line) - 1] == '\n')
				line[strlen(line) - 1] = '\0';

			if (strlen(line) != 0) {
				execute_command(&ht, line);
				memset(line, 0, COMMAND_SIZE);
			}
		}

		if (nr_in_files > 0)
			fclose(in_file);

		file_counter++;
	} while (file_counter < nr_in_files);

	clear(ht);
	free(ht->v);
	free(ht);
	free(line);
	return 0;
}
