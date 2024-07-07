//UDPechoserver program

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


int main(int argc, char * argv[])
{
	int sockfd;
	struct sockaddr_in serveraddr, clientaddr;
	char serv_msg[1024], clt_msg[1024] ;
	socklen_t addrsize;
	
	if(argc!=3)
	{
		printf( "Usage: udpechoserver ipaddress port\n");
		exit(1);
	}
	
	sockfd=socket (AF_INET, SOCK_DGRAM, 0);
	if (sockfd<0)
	{ 
		perror("Error: ");
		exit(1) ;
	}
	else
		printf("Server socket created\n");
		
	memset(&serveraddr, '\0', sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	int b= bind (sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if( b < 0)
	{ 
		perror("Binding error: ");
		exit(1) ;
	}
	else
		printf("Binding done\n") ;
	
	memset(clt_msg, '\0', sizeof (clt_msg)) ;
	memset (serv_msg, '\0',sizeof(serv_msg));
	
	addrsize=sizeof(clientaddr);
	
	int bytes_read=recvfrom(sockfd, clt_msg, sizeof(clt_msg),0, (struct sockaddr*)&clientaddr , &addrsize);
	if(bytes_read<0)
	{ 
		perror ("Reading error: ");
		exit (1);
	}
	clt_msg[bytes_read]='\0';
	
	printf("[Server] Received data that is %d bytes long \n", bytes_read) ;
	printf("[Server] Data from client : %s\n",clt_msg);
	
	strcpy(serv_msg, clt_msg);
	
	int sentbytes = sendto(sockfd, serv_msg, strlen(serv_msg),0, (struct sockaddr*)&clientaddr, addrsize);
	if (sentbytes < 0)
	{
		perror("Error: ");
		exit (1) ;
	}
	close (sockfd) ;
	return 0;
}	
	
