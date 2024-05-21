// GO BACK N - SERVER SIDE

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

void itoa(int number, char numberString[])
{
	numberString[0] = (char)(number + 48);
	numberString[1] = '\0';
}

int main()
{
	int sockfd, newsockfd, windowStart = 1, windowCurrent = 1, windowEnd=4, oldwindowStart;
	char buffer[100];
	socklen_t len;
	struct sockaddr_in server, client;
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = 3300;
	sockfd = (AF_INET, SOCK_STREAM, 0);
	
	int k;
	k = bind(sockfd, (struct sockaddr*)&server, sizeof(server));
	
	len = sizeof(client);
	listen(sockfd, 1);
	printf("LISTENING TO 1 ACTIVE CONNECTION");
	
	newsockfd = accept(sockfd, (struct sockaddr*)&client, &len);
	recv(newsockfd, buffer, 100, 0);
	fcntl(newsockfd, F_SETFL, O_NONBLOCK);
	
	printf("Received a request from client\n Sending packets one by one\n");
	
	do
	{
		if(windowCurrent != windowEnd)
		{
			itoa(windowCurrent, buffer);
			send(newsockfd, buffer, 100, 0);
			printf("Pacet send : %d\n", windowCurrent);
			windowCurrent++;
			recv(newsockfd, buffer, 100, 0);
			
			if(buffer[0] == 'R')
			{
				printf("RETRANSMITTED PACKET, Resnding from packet no. %c\n", buffer[1]);
				itoa(atoi(&buffer[0]), buffer);
				windowCurrent = atoi(&buffer[1]);
				windowCurrent++;
			}
			else if(buffer[0] == 'A')
			{
				oldwindowStart = windowStart;
				windowStart = atoi(&buffer[1])+1;
				windowEnd += (windowStart - oldwindowStart);
				printf("RECEIVED ACKOWLEDGEMENT %c MOving window boundary", buffer[1]);
			}
		}
	}while(windowCurrent!=10);
	
	close(sockfd);
	close(newsockfd);
	return 0;
}	
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
