/* Polterino
	Client application for tttcp
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#define DIM 128

char *indirizzoServer, input[DIM], output[DIM];
int PORTA;

void pulisciinput()
{
	for(int i = 0; i < DIM; ++i)
	{
		input[DIM] = 0;
	}
}

void puliscioutput()
{
	for(int i = 0; i < DIM; ++i)
	{
		output[DIM] = 0;
	}
}

int main(int argc, char **argv)
{
	char *cPORTA;
	int serversize, sock;
	struct sockaddr_in server;
	
	if(argc == 3)
	{
		indirizzoServer = argv[1];
		cPORTA = argv[2];
		PORTA = atoi(cPORTA);
	}
	else
	{
		printf("Sintassi: ./tttcpclient [ipserver] [porta]\n");
		return 0;
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(PORTA);
	server.sin_addr.s_addr = inet_addr(indirizzoServer);
	
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Errore nel socket()\n");
		exit(0);
	}
	
	serversize = sizeof(server);
	if(connect(sock, (struct sockaddr *)&server, serversize) < 0)
	{
		printf("Errore nella connessione\n");
		exit(0);
	}
	
	pulisciinput();
	recv(sock, input, DIM, 0);
	printf("Server: %s\n", input);	

	puliscioutput();
	sprintf(output, "OK mi chiudo %d\n", getpid());
	send(sock, output, DIM, 0);

	close(sock);
	return 0;
}