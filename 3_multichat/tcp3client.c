#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>

char msg[500];

void *recvmg(void *my_sock)
{
	int sock = *((int*)my_sock);
	int len;
	while((len = recv(sock, msg, 500, 0)) > 0) 
	{
		msg[len] = '\0';
		fputs(msg, stdout);
	}
}

int main (int argc, char *argv[])
{
	pthread_t recvt;
	int len;
	int sock;
	char send_msg[500];
	struct sockaddr_in ServerIp;
	char client_name[100];
	
	if (argc != 2)
	{ 
		printf("Usage: client <clientname>\n");
		exit(1);
	}
	else
		strcpy(client_name, argv[1]);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{ 
		printf("Error in socket creation \n" );
		exit(1);
	}
	ServerIp.sin_port = htons(1234) ;
	ServerIp.sin_family= AF_INET;
	ServerIp.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if((connect(sock ,(struct sockaddr *)&ServerIp, sizeof(ServerIp))) == -1)
		printf("\n connection to socket failed \n");
	
	pthread_create(&recvt, NULL, (void *)recvmg, &sock);
	while(fgets (msg, 500, stdin) > 0) 
	{
		strcpy(send_msg, client_name);
		strcat(send_msg,":");
		strcat(send_msg, msg);
		len = write(sock, send_msg, strlen(send_msg));
		if(len < 0)
			printf("\n message not sent \n");
	}
	pthread_join(recvt, NULL) ;
	close(sock);
	return 0;
}
