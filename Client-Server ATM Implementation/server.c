#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include<sys/socket.h>
#include<sys/types.h>


typedef struct
{
	char name[12], surname[12];

	int card_nr, pin, sockfd, tries;

	char pass[16];

	double sold;
} Entry;


int max(int x, int y)
{
	return (x > y) ? x : y;
}


int main(int argc, char** argv)
{
	int i, j, k = 0, x = 1, N, sockfd_ATM, sockfd_UNLOCK, fdmax, newsockfd, bytes, flag = 0, flag_LOGGED_IN = 0;
	
	double d;

	char msg[1024], aux_pin[30], aux_card_nr[100], listsold[150], sum[150], pass[100];

	FILE* fp;

	struct sockaddr_in serv_addr, cli_addr;

	socklen_t addr_size = sizeof(cli_addr);

	fp = fopen(argv[2], "rt");

	fscanf(fp, "%d", &N);

	int logged_in[N];	//Retine clientii logati.

	Entry e[N];	//Vectorul cu persoane din fisierul de intrare.

	for(i = 0; i < N; i++)
	{
		fscanf(fp, "%s %s %d %d %s %lf", e[i].name, e[i].surname, &e[i].card_nr, &e[i].pin, e[i].pass, &e[i].sold);
		
		logged_in[N] = 0;

		e[i].tries = 0;
	}

	fclose(fp);

	sockfd_ATM = socket(AF_INET, SOCK_STREAM, 0);

	setsockopt(sockfd_ATM, SOL_SOCKET, SO_REUSEADDR, &x, sizeof(x));	//Elibereaza socketul imediat.

	sockfd_UNLOCK = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	setsockopt(sockfd_UNLOCK, SOL_SOCKET, SO_REUSEADDR, &x, sizeof(x));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	fd_set read_fds;
	fd_set tmp_fds;

	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	if(bind(sockfd_ATM, (struct sockaddr*) &serv_addr, sizeof(struct sockaddr)) < 0)
	{
		printf("-10 : Eroare la apel bind\n");

		return 0;
	}

	if(bind(sockfd_UNLOCK, (struct sockaddr*) &serv_addr, sizeof(struct sockaddr)) < 0)
	{
		printf("-10 : Eroare la apel bind\n");

		return 0;
	}

	listen(sockfd_ATM, 1000);

	FD_SET(0, &read_fds);
	FD_SET(sockfd_ATM, &read_fds);
	FD_SET(sockfd_UNLOCK, &read_fds);

	fdmax = max(sockfd_ATM, sockfd_UNLOCK);
	fdmax = max(0, fdmax);

	x = 0;

	while(1)
	{
		tmp_fds = read_fds;

		if(select(fdmax + 1, &tmp_fds, NULL, NULL, NULL) == -1)
		{
			printf("-10 : Eroare la apel select\n");

			return 0;
		}

		for(i = 0; i <= fdmax; i++)
		{
			strncpy(msg, "0", sizeof(msg));
			strncpy(aux_card_nr, "0", sizeof(aux_card_nr));	//String pentru parsare numar card primit.
			strncpy(aux_pin, "0", sizeof(aux_pin));	//String pentru parsare pin primit.
			strncpy(sum, "0", sizeof(sum));	//String pentru parsare suma de bani primita.

			if(FD_ISSET(i, &tmp_fds))
			{
				if(i == 0)
				{
					if((bytes = read(0, msg, sizeof(msg))) <= 0)	//Citire de la tastatura.
					{
						printf("-10 : Eroare la apel read\n");
					}
					else
					{
						if(strstr(msg, "quit"))	//Serverul primeste quit de la tastatura.
						{
							for(i = 1; i <= fdmax; i++)	//Se inchid conexiunile cu clientii.
							{
								if(FD_ISSET(i, &read_fds) && i != sockfd_ATM && i != sockfd_UNLOCK)
								{
									send(i, msg, sizeof(msg), 0);

									close(i);

									FD_CLR(i, &read_fds);
									FD_CLR(i, &tmp_fds);
								}
							}

							close(sockfd_ATM);
							close(sockfd_UNLOCK);

							FD_ZERO(&read_fds);
							FD_ZERO(&tmp_fds);

							return 0;
						}
					}
				}
				else if(i == sockfd_ATM)	//Conexiune TCP noua.
				{
					if((newsockfd = accept(sockfd_ATM, (struct sockaddr*) &cli_addr, (socklen_t*) &addr_size)) == -1)
					{
			 			printf("-10 : Eroare la apel accept\n");
						
						return 0;
					}
					else
					{
						FD_SET(newsockfd, &read_fds);
						FD_SET(newsockfd, &tmp_fds);
		
						if(newsockfd > fdmax)
						{
							fdmax = newsockfd;
						}
					}
				}
				else if(i == sockfd_UNLOCK)	//UDP
				{
					if((bytes = recvfrom(i, msg, sizeof(msg), 0, (struct sockaddr*) &cli_addr, &addr_size)) <= 0)
					{
						printf("-10 : Eroare la apel recvfrom\n");

						return 0;
					}
					else
					{
						if(strstr(msg, "unlock"))	//Comanda unlock.
						{
							for(j = 7; msg[j] != '\0'; j++)	//Extragere numar card.
                                                        {
                                                	        aux_card_nr[j - 7] = msg[j];
                                                        }

							aux_card_nr[j - 7] = '\0';

							for(j = 0; j < N; j++)	//Se gaseste socketul pentru un numar de card.
							{
								if(atoi(aux_card_nr) == e[j].card_nr)
								{
									x = e[j].sockfd;

									break;
								}
							}

							for(j = 0; j < N; j++)
							{
								if(atoi(aux_card_nr) == e[j].card_nr && e[j].tries == 3)
								{
									strncpy(msg, "0", sizeof(msg));

									strcpy(msg, "UNLOCK> Trimite parola secreta");

									break;
								}
								else if(atoi(aux_card_nr) == e[j].card_nr && e[j].tries < 3)
								{
									strncpy(msg, "0", sizeof(msg));

									strcpy(msg, "UNLOCK> -6 : Operatie esuata");
								}
							}
							
							if(msg[0] == '0') //Daca nu s-a gasit cardul, stringul ramane initializat cu 0.
							{
								strcpy(msg, "ATM> -4 : Numar card inexistent");
							}

							sendto(sockfd_UNLOCK, msg, strlen(msg), 0, (struct sockaddr*) &cli_addr, addr_size);
						}
						else	//Se primeste parola.
						{
							strncpy(pass, "0", sizeof(pass));

							for(j = 0; msg[j] != ' '; j++)	//Se extrage parola.
							{
								pass[j] = msg[j];
							}

							pass[j] = '\0';

							for(++j; msg[j] != '\0'; j++)
							{
								aux_card_nr[j - strlen(pass) - 1] = msg[j];
							}
								
							aux_card_nr[j - strlen(pass) - 1] = '\0';

							for(j = 0; j < N; j++)
							{
								if(atoi(aux_card_nr) == e[j].card_nr)
								{
									if(strcmp(pass, e[j].pass) == 0)
									{
										strncpy(msg, "0", sizeof(msg));

										strcpy(msg, "UNLOCK> Client deblocat");

										e[j].tries = 0; 

										sendto(sockfd_UNLOCK, msg, strlen(msg), 0, (struct sockaddr*) &cli_addr, addr_size);
	
										continue;
									}
									else
									{
										strncpy(msg, "0", sizeof(msg));

										strcpy(msg, "UNLOCK> Deblocare esuata");

										sendto(sockfd_UNLOCK, msg, strlen(msg), 0, (struct sockaddr*) &cli_addr, addr_size);

										continue;
									}
								}
							}
						}
					}
				}
				else	//Pentru socketii TCP, acceptati mai devreme.
				{
					if((bytes = recv(i, msg, sizeof(msg), 0)) <= 0)
					{
						printf("-10 : Eroare la apel recv\n");

						return 0;
					}
					else
					{
						if(strstr(msg, "login"))	//Comanda login.
						{
							for(j = 6; msg[j] != ' '; j++)
							{
								aux_card_nr[j - 6] = msg[j];
							}

							aux_card_nr[j - 6] = '\0';

							for(++j; msg[j] != '\0'; j++)
							{
								aux_pin[j - strlen(aux_card_nr) - 7] = msg[j];
							}
							
							aux_pin[j - strlen(aux_card_nr) - 7] = '\0';

							for(j = 0; j < N; j++)	//Se initializeaza socketul pentru numarul de card.
							{
								if(atoi(aux_card_nr) == e[j].card_nr)
								{
									e[j].sockfd = i;

									newsockfd = i;	//Se retine socketul.

									break;
								}
							}

							for(j = 0; j < N; j++)
							{
								if(logged_in[j] == newsockfd)	//Daca clientul e logat.
								{
                                                        	        strncpy(msg, "0", sizeof(msg));

									strcpy(msg, "ATM> -2 : Sesiune deja deschisa");
						
									flag_LOGGED_IN = 1;

									send(i, msg, strlen(msg), 0);

									break;
								}
							}

							if(flag_LOGGED_IN == 1)	//Daca clientul e logat deja.
							{
								break;
							}

							for(j = 0; j < N; j++)
							{
								if(atoi(aux_card_nr) == e[j].card_nr && e[j].tries < 3)
								{
									if(atoi(aux_pin) == e[j].pin)	//Logare in regula.
									{
                                                             		        strncpy(msg, "0", sizeof(msg));

										strcpy(msg, "ATM> Welcome ");
								
										strcat(msg, e[j].name);
										strcat(msg, " ");

										strcat(msg, e[j].surname);

										logged_in[k] = e[j].sockfd;

										k++;

										flag = 1;

										e[j].tries = 0;

										break;
									}
									else	//Logare esuata.
									{
										if(e[j].tries == 2)
										{
											strncpy(msg, "0", sizeof(msg));
										
											strcpy(msg, "ATM> -5 : Card blocat");

											e[j].tries++;

											flag = 1;

											break;
										}
										else
										{
											strncpy(msg, "0", sizeof(msg));
										
											strcpy(msg, "ATM> -3 : Pin gresit");

											e[j].tries++;

											flag = 1;

											break;
										}
									}
								}
							}

							if(flag == 0)	//Daca nu s-a gasit cardul.
							{
                                                                strncpy(msg, "0", sizeof(msg));

								strcpy(msg, "ATM> -4 : Numar card inexistent");
							}
							
							send(i, msg, strlen(msg), 0);

							flag = 0;

							continue;
						}
						else if(strstr(msg, "logout"))	//Comanda logout.
						{
						        strncpy(msg, "0", sizeof(msg));

							for(j = 0; j < N; j++)
							{
								if(logged_in[j] == i)	//Daca clientul e logat.
								{
									logged_in[j] = 0;

									break;
								}
							}

							strcpy(msg, "ATM> Deconectare de la bancomat");

							send(i, msg, strlen(msg), 0);

							continue;
						}	
						else if(strstr(msg, "listsold"))	//Comanda listsold.
						{
							for(j = 0; j < N; j++)
							{
								if(e[j].sockfd == i)	//Se cauta clientul.
								{		        
		                                                        strncpy(msg, "0", sizeof(msg));

									strcpy(msg, "ATM> ");

									snprintf(listsold, sizeof(listsold), "%.2lf", e[j].sold);

									strcat(msg, listsold);
								}
							}

							send(i, msg, strlen(msg), 0);

							continue;
							
						}
						else if(strstr(msg, "getmoney"))	//Comanda getmoney.
						{
							for(j = 9; msg[j] != ' '; j++)	//Se extrage suma de bani.
							{
								sum[j - 9] = msg[j];
							}

							sum[j - 9] = '\0';

							if(atoi(sum) % 10 == 0) //Daca e multiplu de 10.
							{
								for(j = 0; j < N; j++)
								{
									if(e[j].sockfd == i)
									{
										if(atoi(sum) <= e[j].sold) //Daca suma <= ca soldul.
										{
											strncpy(msg, "0", sizeof(msg));
											
											e[j].sold -= atoi(sum);

											strcpy(msg, "ATM> Suma ");

											strcat(msg, sum);

											strcat(msg, " retrasa cu succes");
										}
										else
										{
											strncpy(msg, "0", sizeof(msg));

											strcpy(msg, "ATM> -8 : Fonduri insuficiente");
										}
									}
								}
							}
							else
							{
								strncpy(msg, "0", sizeof(msg));

								strcpy(msg, "ATM> -9 : Suma nu este multiplu de 10");
							}

							send(i, msg, strlen(msg), 0);
						}
						else if(strstr(msg, "putmoney"))	//Comanda getmoney.
						{
							for(j = 9; msg[j] != ' '; j++)
                                                        {
                                                        	sum[j - 9] = msg[j];
                                                        }
                                                        
							sum[j - 9] = '\0';
 
							for(j = 0; j < N; j++)
							{
								if(e[j].sockfd == i)	//Daca s-a gasit clientul.
								{
									strncpy(msg, "0", sizeof(msg));

									sscanf(sum, "%lf", &d);

									e[j].sold += d;

									strcpy(msg, "ATM> Suma depusa cu succes");

									send(i, msg, strlen(msg), 0);

									break;
								}
							}
						}
						else if(strstr(msg, "quit"))	//Daca clientul se inchide.
						{
							close(i);

							FD_CLR(i, &read_fds);
							FD_CLR(i, &tmp_fds);
						}
					}
				}
			}
		}
	}
	
	return 0;
}
