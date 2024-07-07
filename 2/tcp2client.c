#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<limits.h>
#include<fcntl.h>
#include<pthread.h>

/*socket
memset
thrimoorthi
connect
while loop*/

int main()
{
	int cli_sockfd;
	char buffer[256];
	
	cli_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(cli_sockfd<0)
	{
		perror("SOCKET CREATION FAILED\n");
		exit(1);
	}
	
	struct sockaddr_in server_addr, cli_addr;
	memset(&cli_addr, 0, sizeof(cli_addr)); 
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1234);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int c = connect(cli_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(c<0)
	{
		perror("CONNECTION FAILED\n");
		exit(1);
	}
	else
		printf("CONNECTION ESTABLISHED..");
	
	while(1)
	{
		// send break recv
		printf("ENTER MESSAGE FOR SERVER : ");
		fgets(buffer, 256, stdin);
		int n = send(cli_sockfd, buffer, 256, 0);
		
		if(strncmp(buffer, "bye", 3)==0)
			break;
		
		n = recv(cli_sockfd, buffer, 256, 0);
		printf("MESSAGE RECEIVED %s", buffer);
	}
	return 0;
}
		
		
		
	
