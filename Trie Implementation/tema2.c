#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>

#include "lista.c"
#include "stiva.c"
#include "coada.c"


typedef struct
{
	char op[100];

	int id_struc, id_par;

	char tip;
} Operation;


int main(int argc, char** argv)
{
	int i, j, N, S, C;

	FILE* in;
	FILE* out;

	info* ae;

	in = fopen(argv[1], "rt");
	
	fscanf(in, "%d %d %d", &N, &S, &C);

	Operation op[N];

	void* s[S];
	void* c[C];

	for(i = 0; i < S; i++)
	{
		s[i] = InitS(sizeof(info));

		if(!s[i])
		{
			printf("Error at InitS()!!!\n");

			return 0;
		}
	}

	for(i = 0; i < C; i++)
	{
		c[i] = InitQ(sizeof(info));

		if(!c[i])
		{
			printf("Error at InitQ()!!!\n");

			return 0;
		}
	}

	for(i = 0; i < N; i++)
	{
		fscanf(in, "%s", op[i].op);

		if(strstr(op[i].op, "push") || strstr(op[i].op, "intrq"))
		{
			fscanf(in, "%d %d %c", &op[i].id_struc, &op[i].id_par, &op[i].tip);

			continue;
		}
		else if(strstr(op[i].op, "prints") || strstr(op[i].op, "printq"))
		{
			continue;
		}
		else
		{
			fscanf(in, "%d", &op[i].id_struc);
		}
	}

	fclose(in);

	ae = (info*)malloc(sizeof(info));

	if(!ae)
	{
		printf("Error at malloc()!!!\n");

		return 0;
	}

	ae->id = 0;

	out = fopen(argv[2], "wt");

	for(i = 0; i < N; i++)
	{
		ae->id = op[i].id_par;
		ae->c = op[i].tip;

		if(strstr(op[i].op, "push"))
		{
			Push(s[op[i].id_struc], (void*)ae);

			continue;
		}
		else if(strstr(op[i].op, "intrq"))
		{
			IntrQ(c[op[i].id_struc], (void*)ae);

			continue;
		}
		else if(strstr(op[i].op, "pop"))
		{
			Pop(s[op[i].id_struc], (void*)ae);

			continue;
		}
		else if(strstr(op[i].op, "extrq"))
		{
			ExtrQ(c[op[i].id_struc], (void*)ae);

			continue;
		}
		else if(strstr(op[i].op, "sorts"))
		{
			s[op[i].id_struc] = SortS(s[op[i].id_struc]);

			continue;
		}
		else if(strstr(op[i].op, "sortq"))
		{
			c[op[i].id_struc] = SortQ(c[op[i].id_struc]);

			continue;
		}
		else if(strstr(op[i].op, "prints"))
		{
			for(j = 0; j < S; j++)
			{
				PrintS(s[j], out);

				fprintf(out, "\n");
			}

			continue;
		}
		else if(strstr(op[i].op, "printq"))
		{
			for(j = 0; j < C; j++)
			{
				c[j] = PrintQ(c[j], out);
	
				fprintf(out, "\n");
			}

			continue;
		}
		else if(strstr(op[i].op, "corrects"))
		{
			s[op[i].id_struc] = CorrectS(s[op[i].id_struc], out);

			continue;
		}
		else if(strstr(op[i].op, "correctq"))
		{
			c[op[i].id_struc] = CorrectQ(c[op[i].id_struc], out);
		}
	}		

	fclose(out);

	return 0;
}
