#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<fcntl.h>
#include<limits.h>

int main()
{
	int cli_sockfd;
	char buffer[256];
	struct sockaddr_in server_addr;
	cli_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1234);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	int conn_status = connect(cli_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	if(conn_status == -1)
	{
		perror("ERROR IN CONNECTING");
		exit(1);
	}
	
	recv(cli_sockfd, &buffer, sizeof(buffer) , 0);
	printf("MESSAGE RECEIVED FROM SERVER IS %s\n", buffer);
	close(cli_sockfd);
	return 0;
}
	
	
