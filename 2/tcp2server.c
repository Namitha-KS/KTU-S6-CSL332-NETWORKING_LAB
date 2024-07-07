#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<limits.h>
#include<netdb.h>
/* create socket
memset
thrimoorthi
bind
listen
newsockfd = accpt
while loop*/

int main()
{
	int sockfd, newsockfd;
	char buffer[256];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0)
	{
		perror("ERROR IN SOCKET CREATION\n");
		exit(1);
	}
	
	struct sockaddr_in server_addr, cli_addr;
	socklen_t cli_len = sizeof(cli_addr);
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1234);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int b = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(b<0)
	{
		perror("ERROR IN BINDING...\n");
		exit(1);
	}
	else
		printf("BINDING STARTED...\n");
		
	int l = listen(sockfd, 5);
	if(l<0)
	{
		perror("ERROR IN LISTENING...\n");
		exit(1);
	}
	else
		printf("SERVER LISTENING...\n");
		
	newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len);
	if(newsockfd<0)
	{
		perror("ACCEPTING FAILED\n");
		exit(1);
	}
	else
		printf("SERVER ACCEPTING...\n");
	
	while(1)
	{
		int n = recv(newsockfd, buffer, 256, 0);
		printf("MESSAGE RECEIVED FROM CLIENT IS %s\n", buffer);
		
		if(strncmp(buffer, "bye", 3)==0)
			break;
		
		printf("MESSAGE FOR CLIENT : ");
		fgets(buffer, 256, stdin);
		n = send(newsockfd, buffer, 256, 0);
	}
	close(sockfd);
	close(newsockfd);
	return 0;
}
	
