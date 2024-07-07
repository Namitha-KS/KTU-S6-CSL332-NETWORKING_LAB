#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>

pthread_mutex_t mutex;
int clients[20];
int n=0;
char msg[500];

void sendtoall(char *msg, int curr)
{
	int i;
	pthread_mutex_lock(&mutex);
	for(i = 0; i < n; i++)
	{
		if(clients[i] != curr)
		{
			if(send(clients[i], msg, strlen(msg), 0) < 0)
			{
				printf("sending failure");
				continue;
			}
		}
	}
	pthread_mutex_unlock(&mutex);
}

void *recvmg(void *client_sock)
{
	int sock = *((int *)client_sock);
	int len;
	while((len = recv(sock, msg, 500, 0)) > 0) 
	{
		msg[len] = '\0';
		sendtoall(msg, sock);
	}
}
int main()
{
	struct sockaddr_in ServerIp;
	pthread_t recvt;
	int sock=0, Client_sock=0;
	ServerIp.sin_family = AF_INET;
	ServerIp.sin_port = htons(1234) ;
	ServerIp.sin_addr.s_addr = inet_addr("127.0.0.1");
	sock=socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		printf("Error in socket creation\n");
		exit(1);
	}
	int b = bind(sock,(struct sockaddr *)&ServerIp, sizeof(ServerIp)) ;
	if(b ==-1)
		printf("cannot bind, error! ! \n");
	else
		printf("Server Started\n");
	int ld= listen(sock ,5 );
	if(ld == -1)
		printf("listening failed \n");
	else
		printf("Server Listening...\n");
	while(1)
	{
		Client_sock = accept(sock, (struct sockaddr*)NULL, NULL) ;
		if(Client_sock < 0)
			printf("accept failed \n");
		else
			printf("Connection from client %d accepted n", n+1);
			
		pthread_mutex_lock(&mutex);
		clients[n]= Client_sock;
		n++;
		pthread_create(&recvt, NULL, (void *)recvmg, &Client_sock);
		pthread_mutex_unlock(&mutex) ;
	}
	return 0;
}
