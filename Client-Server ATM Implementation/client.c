#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>


//Calculeaza descriptorul maxim.
int max(int x, int y)
{
	return (x > y) ? x : y;
}


int main(int argc, char** argv)
{
	int i, j, sockfd_ATM, sockfd_UNLOCK, bytes, fdmax, flag_LOGIN = 0, flag_UNLOCK = 0;

	char cmd[1024], aux_cmd[1024] = {0}, result[1024], filename[100], pid[10], card_nr[7], last_card[1024] = {0};

	FILE* fp = NULL;

	struct sockaddr_in serv_addr;

	socklen_t addr_size = sizeof(serv_addr);

	fd_set read_fds, tmp_fds;

	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	sockfd_ATM = socket(AF_INET, SOCK_STREAM, 0);
	sockfd_UNLOCK = socket(PF_INET, SOCK_DGRAM, 0);

	FD_SET(0, &read_fds);
	FD_SET(sockfd_ATM, &read_fds);
	FD_SET(sockfd_UNLOCK, &read_fds);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));

	inet_aton(argv[1], &(serv_addr.sin_addr));

	if(connect(sockfd_ATM, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)	//Conexiune TCP.
	{
		printf("-10 : Eroare la apel connect\n");

		return 0;
	}

	sprintf(pid, "%d", getpid());

	strcpy(filename, "client-");

	strcat(filename, pid);
	strcat(filename, ".log");

	fdmax = max(sockfd_ATM, sockfd_UNLOCK);
	fdmax = max(0, fdmax);

	fp = fopen(filename, "wt");

	while(1)
	{
		tmp_fds = read_fds;	//Reinitializare multime.

		if(select(fdmax + 1, &tmp_fds, 0, 0, NULL) == -1)
		{
			printf("-10 : Eroare la apel select\n");

			return 0;
		}

		for(i = 0; i <= fdmax; i++)
		{
			strncpy(result, "0", sizeof(result));

			if(FD_ISSET(i, &tmp_fds))
			{
				if(i == 0)
				{
					bytes = read(0, cmd, sizeof(cmd));
		
					cmd[bytes - 1] = '\0';

					strcpy(aux_cmd, cmd);	//Retin comanda ca sa o scriu in fisier la final, intrucat cmd se modifica.

					if(strcmp(cmd, "unlock") != 0)	//Daca nu e unlock.
					{
						if(strstr(cmd, "login") && strcmp(cmd, last_card) != 0)
						{
							flag_LOGIN = 0;
						}

						if(strstr(cmd, "login") != NULL && flag_LOGIN == 1)	//Comanda login.
						{
							printf("-2 : Sesiune deja deschisa\n");

							fprintf(fp, "%s\n", cmd);
							fprintf(fp, "%s", "-2 : Sesiune deja deschisa\n");

							continue;
						}
						else if(strstr(cmd, "login") != NULL && flag_LOGIN == 0) //Daca nu sunt logat deja.
						{
							for(j = 6; cmd[j] != ' '; j++)
							{
								card_nr[j - 6] = cmd[j];
							}

							card_nr[j - 6] = '\0';

							strcpy(last_card, cmd);

							flag_LOGIN = 1;
						}
						else if(strstr(cmd, "logout") != NULL && flag_LOGIN == 0) //Comanda logout.
						{
							printf("-1 : Clientul nu este autentificat\n");

							fprintf(fp, "%s\n", cmd);
							fprintf(fp, "%s\n", "-1 : Clientul nu este autentificat\n");

							continue;
						}
						else if(strstr(cmd, "logout") != NULL && flag_LOGIN == 1)
						{
							flag_LOGIN = 0;	//Clientul nu mai e logat.
						}
						else if(strstr(cmd, "listsold") || strstr(cmd, "getmoney") || strstr(cmd, "putmoney"))
						{
							if(flag_LOGIN == 0)
							{
								printf("-1 : Clientul nu este autentificat\n");

								fprintf(fp, "%s\n", cmd);
								fprintf(fp, "%s\n", "-1 : Clientul nu este autentificat\n");

								continue;
							}
						}
						else if(strstr(cmd, "quit"))	//Se inchid socketii si procesul client.
						{
							send(sockfd_ATM, cmd, strlen(cmd), 0);

							close(sockfd_ATM);
							close(sockfd_UNLOCK);

							FD_ZERO(&read_fds);
							FD_ZERO(&tmp_fds);

							fprintf(fp, "%s\n", cmd);

							fclose(fp);
							
							return 0;
						}
						
						if(flag_UNLOCK == 0)	//Daca comanda trecuta nu a fost "unlock".
						{
							send(sockfd_ATM, cmd, strlen(cmd), 0);
						}
					}
					else if(strcmp(cmd, "unlock") == 0 && flag_LOGIN == 0)	//Comanda unlock.
					{
						strcat(cmd, " ");
						strcat(cmd, card_nr);
						
						sendto(sockfd_UNLOCK, cmd, strlen(cmd), 0, (struct sockaddr*) &serv_addr, addr_size);
					}
					
					if(flag_UNLOCK == 1)
					{
						strcat(cmd, " ");
						strcat(cmd, card_nr);
	
						sendto(sockfd_UNLOCK, cmd, strlen(cmd), 0, (struct sockaddr*) &serv_addr, addr_size);
					}
				}
			
				if(i == sockfd_ATM)
				{
					bytes = read(sockfd_ATM, result, sizeof(result));

					if(strstr(result, "-3") || strstr(result, "-5") || strstr(result, "-4"))
					{
						flag_LOGIN = 0;	//Se reseteaza flagul, in caz de eroare.
					}

					if(strstr(result, "Deconectare"))
					{
						flag_LOGIN = 0;
					}

					if(strstr(result, "quit"))	//Se inchide serverul.
					{
						close(sockfd_ATM);
						close(sockfd_UNLOCK);

						FD_ZERO(&read_fds);
						FD_ZERO(&tmp_fds);

						fclose(fp);

						return 0;
					}
						
					fprintf(fp, "%s\n", cmd);
					fprintf(fp, "%s\n\n", result);

					strncpy(cmd, "0", sizeof(cmd));

					printf("%s\n", result);

					continue;
				}
				else if(i == sockfd_UNLOCK)
				{
					bytes = recvfrom(sockfd_UNLOCK, result, sizeof(result), 0, (struct sockaddr*) &serv_addr, &addr_size);
				
					if(strstr(result, "Trimite parola secreta"))
					{
						flag_UNLOCK = 1;	//Se asteapta ca urmatorul input sa fie parola.
					}
					else
					{
						flag_UNLOCK = 0;
					}

					fprintf(fp, "%s\n", cmd);
					fprintf(fp, "%s\n\n", result);

					strncpy(cmd, "0", sizeof(cmd));

					printf("%s\n", result);

					break;
				}
			}
		}
	}

	return 0;
}
