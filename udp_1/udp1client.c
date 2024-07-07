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

int main(int argc, char * argv[])
{
	int clientsockfd;
	struct sockaddr_in serveraddr;
	socklen_t serveraddrsize;
	char clientmsg[1024], servermsg[1024];
	
	if(argc!=3)
	{
		printf( "Usage : udpechoclient ipaddress port\n");
		exit (1);
	}
	
	clientsockfd=socket(AF_INET, SOCK_DGRAM, 0) ;
	if(clientsockfd < 0)
	{ 
		perror("Error: ");
		exit(1);
	}
	else
		printf("Client Socket created success fully\n");
	
	memset(&serveraddr, '\0',sizeof(serveraddr));
	
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port = htons(atoi (argv[2]));
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	printf("Enter message to send: \n");
	fgets(clientmsg, sizeof(clientmsg), stdin);
	
	printf("[Client ] Data sent to Server : %s\n", clientmsg);
	int sentbytes = sendto(clientsockfd, clientmsg, strlen(clientmsg),0,(struct sockaddr*) &serveraddr, sizeof(serveraddr));
	
	if(sentbytes < 0)
	{
		perror("Error: ");
		exit(1) ;
	}
	serveraddrsize = sizeof(serveraddr);
	int readbytes= recvfrom(clientsockfd, servermsg, sizeof(servermsg),0,(struct sockaddr*) &serveraddr,&serveraddrsize) ;
	if(readbytes<0)
	{ 
		perror ("Reading error: ");
		exit(1);
	}
	servermsg[readbytes]= '\0';
	printf("[Client] Server's response: %s\n", servermsg);
	close(clientsockfd);
	return 0;
}
	
