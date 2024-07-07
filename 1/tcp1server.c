#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
#include<fcntl.h>
#include<limits.h>

int main()
{
	int sockfd;
	struct sockaddr_in server_addr;
	char server_msg[] = "\nYOU HAVE REACHED THE SERVER\n";
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1234);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	listen(sockfd, 5);
	
	int client_sock;
	client_sock = accept(sockfd, NULL, NULL);
	send(client_sock, server_msg, sizeof(server_msg), 0);
	close(sockfd);
	return 0;
}
	
