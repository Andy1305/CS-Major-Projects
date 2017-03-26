#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


int* binary_to_decimal(int* a)	//Converteste vectorul primit (masca in binar) in zecimal.
{
	int i, j, *int_mask;

	int_mask = calloc(4, sizeof(int));

	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 8; j++)
		{
			int_mask[i] = int_mask[i] + pow(2, j) * (a[i] % 10);

			a[i] = a[i] / 10;
		}
	}	

	return int_mask;	//Returneaza masca in zecimal.
}


int* mask_to_decimal(int n)	//Creeaza un vector de 4 octeti cu n (masca) biti de 1.
{
	int i, j, k = 0, *a;
	char mask[100], aux[100];

	a = calloc(4, sizeof(int));

	for(i = 0; i < 32; i++)
	{
		mask[i] = '0';
	}

	for(i = 0; i < n; i++)
	{
		mask[i] = '1';
	}

	mask[32] = '\0';

	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 8; j++)
		{
			aux[j] = mask[k];	//Imparte in cate 8 biti.
			
			k++;
		}

		aux[8] = '\0';

		a[i] = atoi(aux);	//Converteste octetii din caracter in numar.
	}

	return binary_to_decimal(a);	//Returneaza un vector de intregi ce contine masca in zecimal.
} 


int* adresa_de_retea(char* ip, int* mask)
{
	int i = 0, j = 0, c = 0, aux, *v;
	char temp[100];

	v = calloc(4, sizeof(int));

	for(j = 0; ip[j] != '\0'; j++)
	{
		if((ip[j] == '.') || (ip[j] == '/'))
		{
			temp[c] = '\0';

			c = 0;

			j++;	

			aux = atoi(temp);

			aux = aux & mask[i];	//AND pe biti cu fiecare octet.

			v[i] = aux;

			i++;
		}

		temp[c] = ip[j];

		c++;
	}

	return v;				//Contine adresa de retea in zecimal.
}

	
void adresa_de_broadcast(char *ip, int* mask)
{
        int i = 0, j, c = 0, aux, comp_mask[100];
        char temp[100];

        for(j = 0; ip[j] != '\0'; j++)
        {
		if((ip[j] == '.') || (ip[j] == '/'))
		{
			temp[c] = '\0';
			
			c = 0;
			
			j++;	
		
			aux = atoi(temp);

			comp_mask[i] = mask[i] ^ 255;	//Contine masca negata.

			aux = aux | comp_mask[i];	//OR pe biti cu fiecare octet.

			if(i == 3)
			{
				printf("%d", aux);

				break;
			}

			printf("%d.", aux);

			i++;	
		}
	
        	temp[c] = ip[j];			//Contine octetii IP-ului.

                c++;
	}
}


void convert_to_hexa(char* ip1)
{
	int i = 0, j, c = 0, aux;
	char temp[100];
      
        for(j = 0; ip1[j] != '\0'; j++)			//Parcurge IP-ul.
        {
		if((ip1[j] == '.') || (ip1[j] == '/'))	//Cand intalneste un anumit caracter afiseaza si reseteaza tot.
		{
			temp[c] = '\0';
			
			c = 0;

			j++;

			aux = atoi(temp);

			if(i == 3)
			{
				printf("%X", aux);	//Afiseaza rezultatul in hexazecimal.

				return;
			}

			printf("%X.", aux);

			i++;
		}
			
                temp[c] = ip1[j];

                c++;
        }
}


void convert_to_octal(char* ip2)
{
	int i = 0, j, c = 0, aux;
	char temp[100], temp2[100];

	memset(temp2, '\0', sizeof(ip2));

	strcpy(temp2, ip2);

	strcat(temp2, "/");	//Am adaugat ca sa pot citi si ultimul octet si sa ma opresc.

        for(j = 0; temp2[j] != '\0'; j++)
        {
		if((temp2[j] == '.') || (temp2[j] == '/'))
		{
			temp[c] = '\0';

			c = 0;

			j++;

			aux = atoi(temp);

			if(i == 3)
			{
				printf("%o", aux);	//Afiseaza rezultatul in octal.

				return;
			}

			printf("%o.", aux);

			i++;
		}

		temp[c] = temp2[j];
	
		c++;
 	}
}


void number_to_binary(int n)				//Creeaza un vector cu numarul in binar, inversat.
{
	int i;
	char v[8];

	for(i = 0; i < 8; i++)
	{
		v[i] = '0';
	}

	i = 7;

	while(n != 0)
	{
		if(n % 2 == 1)
		{
			v[i] = '1';
		}

		n = n / 2;

		i--;
	}

	v[8] = '\0';

	printf("%s", v);
}


void ip_to_binary(char* ip)
{
	int i, j = 0, c = 0, aux;
	char temp[100], temp2[100];

        memset(temp2, '\0', sizeof(ip));

	strcpy(temp2, ip);

	strcat(temp2, "/");

	for(i = 0; temp2[i] != '\0'; i++)			//Parcurge IP-ul si transforma fiecare octet in numar intreg.
	{
		if((temp2[i] == '.') || (temp2[i] == '/'))
		{
			temp[c] = '\0';

			c = 0;			

			i++;

			aux = atoi(temp);	
		
			if(j == 3)
			{
				number_to_binary(aux);

				break;
			}

			number_to_binary(aux);

			printf(".");

			j++;
		}

		temp[c] = temp2[i];

		c++;
	}
}


void number_to_32(int n)					//Creeaza un vector cu numarul in baza 32, inversat.
{
	int i = 0;
	char c = 'A', v[100];

	if(n == 0)
	{
		v[0] = '0';

		i++;
	}

	while(n != 0)
	{
		if(n % 32 == 0)
		{
			v[i] = '0';
		}
		
		if(n % 32 < 10)
		{
			sprintf(&v[i], "%d", n % 32);		//Transforma un numar in caracter si il pune in vector.
		}

		if(n % 32 >= 10)
		{
			v[i] = c + (n % 32) - 10;		//Reprezinta caracterul corespunzator restului mai mare sau egal cu 10.
		}

		n = n / 32;	

		i++;
	}

	v[i] = '\0';

	for(i = strlen(v) - 1; i >= 0; i--)
	{
		printf("%c", v[i]);
	}
}


void ip_to_32(char *ip)
{
        int i, j = 0, c = 0, aux;
        char temp[100], temp2[100];

        memset(temp2, '\0', sizeof(ip));

        strcpy(temp2, ip);

        strcat(temp2, "/");

        for(i = 0; temp2[i] != '\0'; i++)				//Parcurge IP-ul si transforma fiecare octet in numar intreg.
        {
                if((temp2[i] == '.') || (temp2[i] == '/'))
                {
                        temp[c] = '\0';

                        c = 0;

                        i++;

                        aux = atoi(temp);

                        if(j == 3)
                        {
                                number_to_32(aux);

                                break;
                        }

                        number_to_32(aux);

                        printf(".");

                        j++;
                }

                temp[c] = temp2[i];

                c++;
        }
}


int main()
{
	int N, NUM, i, j, k, c = 0, int_mask, *dec_mask, *temp;
	char ip1[1000], ip2[1000], adr[1000][1000], mask[1000], temp2[100];

	dec_mask = calloc(4, sizeof(int));
	
	temp = calloc(4, sizeof(int));

	scanf("%d", &N);						//Retine numarul de linii.

	for(i = 0; i < N; i++)
	{
		scanf("%s", ip1);
		
		scanf("%s", ip2);

		scanf("%d", &NUM);

		for(j = 0; j < NUM; j++)
		{
			scanf("%s", adr[j]);				//Retine NUM adrese de retea.
		}
	
		printf("-0 ");

		for(j = 0; ip1[j] != '/'; j++)
		{
			printf("%c", ip1[j]);
		}

		printf("\n-1 ");

		for(j = 0; ip1[j] != '\0'; j++)
		{
			if(ip1[j] == '/')
			{
				break;
			}
		}

		for(j = j + 1; ip1[j] != '\0'; j++)
		{
			mask[c] = ip1[j];
		
			c++;
		}

		mask[c] = '\0';

		int_mask = atoi(mask);					//Converteste masca in numar intreg.

		dec_mask = mask_to_decimal(int_mask);

		for(j = 0; j < 4; j++)
		{
			if(j == 3)
			{
				printf("%d", dec_mask[j]);
	
				break;
			}

			printf("%d.", dec_mask[j]);
		}

		printf("\n-2 ");

		temp = adresa_de_retea(ip1, dec_mask);

		for(j = 0; j < 4; j++)
		{
			if(j == 3)
			{
				printf("%d", temp[j]);

				break;
			}

			printf("%d.", temp[j]);
		}		
 

		printf("\n-3 ");

		adresa_de_broadcast(ip1, dec_mask);

		printf("\n-4 ");

		int *a, *b, flag = 0;

		a = adresa_de_retea(ip1, dec_mask);
		b = adresa_de_retea(ip2, dec_mask);

		if((a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]) && (a[3] == b[3]))
		{
			printf("da");
	
			flag = 1;
		}
		else
		{
			printf("nu");
		}

		printf("\n-5 ");
			
		convert_to_hexa(ip1);

		printf(" ");

		convert_to_octal(ip2);

		printf("\n-6 ");

		if(flag == 1)
		{
			printf("0");
		}
		else
		{
			for(j = 0; j < NUM; j++)
			{
				c = 0;
				
				for(k = 0; adr[j][k] != '/'; k++)
				{
				}

				k++;

				for(; adr[j][k] != '\0'; k++)
				{
					temp2[c] = adr[j][k];

					c++;	
				}

				temp2[c] = '\0';

				int_mask = atoi(temp2);

		                dec_mask = mask_to_decimal(int_mask);	

				a = adresa_de_retea(adr[j], dec_mask);
				b = adresa_de_retea(ip2, dec_mask);

		                if((a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]) && (a[3] == b[3]))
				{
					printf("%d ", j + 1);
				}
			}
		}

		printf("\n-7 ");

		ip_to_binary(ip1);
	
		printf(" ");
		
		ip_to_binary(ip2);
	
		printf("\n-8 ");

		ip_to_32(ip1);

		printf(" ");

		ip_to_32(ip2);

		c = 0;

		printf("\n");
	}

	free(dec_mask);
	free(temp);

	return 0;
}
