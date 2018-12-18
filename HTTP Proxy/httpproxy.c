#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>


typedef struct
{
	int socket;

	char request[300];
} Client;	// Face legatura intre socket (client) si cererea pe care o primeste de la acesta.


int main(int argc, char** argv)
{
	int i, j, k = 0, l = 0, x, y, sockfd, serv_sock, fdmax, bytes, newsockfd, yes = 1, clientfd,
	    flag[500] = {0}, cache_flag[500] = {0};
	
	char msg[500], p1[500], p2[500], p3[500], temp[500], port[300];

	FILE* fp;

	Client c[500];

	struct sockaddr_in serv_addr, cli_addr;

	socklen_t addr_size = sizeof(cli_addr);

	struct hostent* h;

	fd_set read_fds;
	fd_set tmp_fds;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);	// Legatura cu clientii.

	if(sockfd < 0)
	{
		printf("Error at socket()!!!\n");

		return 0;
	}

	cli_addr.sin_family = AF_INET;
	cli_addr.sin_port = htons(atoi(argv[1]));
	cli_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

	if(bind(sockfd, (struct sockaddr*)&cli_addr, sizeof(cli_addr)) < 0)
	{
		printf("Error at binding()!!!\n");
	
		return 0;
	}

	listen(sockfd, 300);

	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	FD_SET(sockfd, &read_fds);

	fdmax = sockfd;

	while(1)
	{
		tmp_fds = read_fds;

		if(select(fdmax + 1, &tmp_fds, NULL, NULL, NULL) == -1)
		{
			printf("Error at select()!!!\n");

			return 0;
		}

		for(i = 0; i <= fdmax; i++)
		{
			if(FD_ISSET(i, &tmp_fds))
			{
				if(i == sockfd)	// Daca primesc cerere de la client.
				{
					if((newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, (socklen_t*) &addr_size)) == -1)
					{
			 			printf("Error at accept()!!!\n");
						
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
				else if(i == serv_sock)	// Daca primesc date de la server.
				{
					memset(msg, 0, sizeof(msg));

					for(j = 0; j < k; j++)	// Caut clientul care a trimis cererea.
					{
						if(strstr(c[j].request, temp))
						{
							clientfd = c[j].socket;

							break;
						}
					}

					strcat(temp, ".html");

					fp = fopen(temp, "w");

					memset(msg, 0, sizeof(msg));

					// Primesc date de la server, le trimit la client si le scriu in fisier, daca se poate. 
					while((bytes = recv(serv_sock, msg, sizeof(msg), 0)) > 0)
					{
						send(clientfd, msg, bytes, 0);
					
						if(!strstr(msg, "no_cache") && !strstr(msg, "private") && 
						   cache_flag[clientfd] != 1)
						{
							fwrite(msg, 1, bytes, fp);
						}
						else
						{
							cache_flag[clientfd] = 1;	// Retin ca nu pot scrie in cache.
						}
						
						memset(msg, 0, sizeof(msg));
					}

					fclose(fp);
					
					// Elimin cererea din lista.
					for(j = 0; j < k; j++)
					{
						if(strstr(c[j].request, temp))
						{
							memset(c[j].request, 0, sizeof(c[j].request));
						}
					}
					
					// Inchid conexiunea.
					cache_flag[clientfd] = 0;

					FD_CLR(clientfd, &read_fds);
					FD_CLR(clientfd, &tmp_fds);

					FD_CLR(serv_sock, &read_fds);
					FD_CLR(serv_sock, &tmp_fds);

					close(clientfd);
					close(serv_sock);

					fdmax = sockfd;

					break;
				}
				else
				{
					memset(msg, 0, sizeof(msg));
					memset(temp, 0, sizeof(temp));
					memset(p1, 0, sizeof(p1));
					memset(p2, 0, sizeof(p2));
					memset(p3, 0, sizeof(p3));
					memset(port, 0, sizeof(port));

					l = 0;

					if((bytes = recv(i, msg, sizeof(msg), 0)) < 0)
					{
						perror("Error at recv()!!!\n");

						return 0;
					}
					else
					{
						// Verific daca cererea e in regula.
						if((strstr(msg, "GET") || strstr(msg, "POST")) &&
						   (strstr(msg, "http://") || strstr(msg, "Host")) &&
						   (strstr(msg, "HTTP/1.0")))
						{
							sscanf(msg, "%s %s %s", p1, p2, p3);
							
							// Verific daca site-ul este in cache.
							for(j = 0; j < k; j++)
							{
								if(strstr(c[j].request, msg))
								{
									flag[i] = 1;

									break;
								}
							}

							// Il adaug in lista de clienti.
							c[k].socket = i;
							
							strcpy(c[k].request, msg);

							k++;
							
							// Extrag numele site-ului in temp.
							for(j = 0; j < strlen(p2) - 1; j++)
							{
								if(p2[j] == '/' && p2[j + 1] != '/')
								{
									break;
								}
							}

							j++;

							while(p2[j] != '/')
							{
								temp[l] = p2[j];
	
								j++;
								l++;
							}
							
							temp[l] = '\0';
							
							// Daca exista in cache.
							if(flag[i])
							{
								strcat(temp, ".html");

								fp = fopen(temp, "r");

								memset(msg, 0, sizeof(msg));

								while((bytes = fread(msg, 1, bytes, fp)) > 0)
								{
									send(i, msg, bytes, 0);
								}

								fclose(fp);

								FD_CLR(i, &read_fds);
								FD_CLR(i, &tmp_fds);

								FD_CLR(serv_sock, &read_fds);
								FD_CLR(serv_sock, &tmp_fds);

								close(i);
								close(serv_sock);

								flag[i] = 0;

								break;
							}

							serv_addr.sin_family = AF_INET;
							
							// Verific daca cererea contine port si o extrag, daca exista.
							if(strstr(temp, ":"))
							{
								for(j = 0; j < strlen(temp); j++)
								{
									if(temp[j] == ':')
									{
										y = j;
										
										break;
									}
								}
								
								j++;
								
								x = j;
								
								for(; j < strlen(temp); j++)
								{
									port[j - x] = temp[j];
								}

								port[j - x] = '\0';

								temp[y] = '\0';
								
								// Elimin portul din cerere.
								memmove(strstr(msg, port), strstr(msg, port) + strlen(port), 
								        strlen(strstr(msg, port) + strlen(port)));
								
								serv_addr.sin_port = htons(atoi(port));
							}
							else
							{
								serv_addr.sin_port = htons(80);
							}
							
							h = gethostbyname(temp);
							
							memcpy((char*)&serv_addr.sin_addr.s_addr, (char*)h->h_addr, h->h_length);

							serv_sock = socket(AF_INET, SOCK_STREAM, 0);

							if(serv_sock < 0)
							{
								printf("Error at socket()!!!\n");

								return 0;
							}

							FD_SET(serv_sock, &read_fds);
							FD_SET(serv_sock, &tmp_fds);

							if(serv_sock > fdmax)
							{
								fdmax = serv_sock;
							}
							
							// Ma conectez la server.
							printf("Trimit cererea: %s\n\n", msg);
							if(connect(serv_sock, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr)) < 0)
							{
								perror("Error in connecting to remote server!!!\n");

								return 0;
							}

							// Trimit cererea la server.
							if((bytes = send(serv_sock, msg, strlen(msg), 0)) < 0)
							{
								printf("Sending error!!!\n");

								return 0;
							}
						}
						else 	// Daca cererea nu e in regula.
						{
							strcpy(msg, "HTTP/1.0 400 Bad Request");
						
							send(i, msg, bytes, 0);
							
							FD_CLR(i, &read_fds);
							FD_CLR(i, &tmp_fds);

							close(i);
							
							break;
						}
					}
				}
			}
		}
	}
			
	return 0;
}
