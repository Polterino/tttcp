/* Polterino
	Server application for tttcp
*/
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>
#include <ctype.h>
#include <unistd.h>

#define PORTA 8080
int serversocket, c1socket, c2socket;

int main(int argc, char **argv)
{
	int l1, l2;	/* La grandezza della struct sockaddr_in dei due client */
	struct sockaddr_in server, client1, client2;
	
	server.sin_family = AF_INET;
	server.sin_port = htons(PORTA);
	server.sin_addr.s_addr = INADDR_ANY;
	
	/* I controlli sono < 0 perchè se ritorna -1, l'operazione ha riscontrato un errore */
	if((serversocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Errore nel socket()\n");
		return 0;
	}
	
	if(bind(serversocket, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("Errore nel bind()\n");
		return 0;
	}
	
	listen(serversocket, 1);
	printf("Sono in ascolto sulla porta %d per il primo client\n", PORTA);

	/* Accetto la connessione */
	l1 = sizeof(client1);
	if((c1socket = accept(serversocket, (struct sockaddr *)&client1, &l1)) < 0)
	{
		perror("Errore nel accept()\n");
		return 0;
	}
	
	close(serversocket);
	server.sin_family = AF_INET;
	server.sin_port = htons(9999);
	server.sin_addr.s_addr = INADDR_ANY;
	
	/* I controlli sono < 0 perchè se ritorna -1, l'operazione ha riscontrato un errore */
	if((serversocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Errore nel socket()\n");
		return 0;
	}

	if(bind(serversocket, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("Errore nel bind()\n");
		return 0;
	}
	
	listen(serversocket, 1);
	printf("Sono in ascolto sulla porta %d per il secondo client\n", PORTA);

	/* Accetto la connessione */
	l2 = sizeof(client2);
	if((c2socket = accept(serversocket, (struct sockaddr *)&client2, &l2)) < 0)
	{
		perror("Errore nel accept()\n");
		return 0;
	}

	close(c1socket);
	close(c2socket);
	close(serversocket);

	return 0;
}