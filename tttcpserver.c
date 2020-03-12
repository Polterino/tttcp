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
#include <string.h>

#define PORTA1 1111
#define PORTA2 2222
#define DIM 128
int c1socket, c2socket;
char input[DIM], output[DIM];

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
	int l1, l2;	/* La grandezza della struct sockaddr_in dei due client */
	struct sockaddr_in client1, client2;

	client1.sin_family = AF_INET;
	client1.sin_port = htons(PORTA1);
	client1.sin_addr.s_addr = INADDR_ANY;

	client2.sin_family = AF_INET;
	client2.sin_port = htons(PORTA2);
	client2.sin_addr.s_addr = INADDR_ANY;
	printf("Avvio programma\n");

	/* I controlli sono < 0 perchè se ritorna -1, l'operazione ha riscontrato un errore */
	if((c1socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Errore nel socket()\n");
		return 0;
	}
	
	if(bind(c1socket, (struct sockaddr *)&client1, sizeof(client1)) < 0)
	{
		perror("Errore nel bind()\n");
		return 0;
	}
	
	listen(c1socket, 1);
	printf("Sono in ascolto sulla porta %d per il primo client\n", PORTA1);

	l1 = sizeof(client1);
	if((c1socket = accept(c1socket, (struct sockaddr *)&client1, &l1)) < 0)
	{
		perror("Errore nel accept()\n");
		return 0;
	}
	printf("Il primo client si e' connesso\n");

	/* I controlli sono < 0 perchè se ritorna -1, l'operazione ha riscontrato un errore */
	if((c2socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Errore nel socket()\n");
		return 0;
	}

	if(bind(c2socket, (struct sockaddr *)&client2, sizeof(client2)) < 0)
	{
		perror("Errore nel bind()\n");
		return 0;
	}
	
	listen(c2socket, 1);
	printf("Sono in ascolto sulla porta %d per il secondo client\n", PORTA2);

	l2 = sizeof(client2);
	if((c2socket = accept(c2socket, (struct sockaddr *)&client2, &l2)) < 0)
	{
		perror("Errore nel accept()\n");
		return 0;
	}
	printf("I due client si sono connessi\n");

	puliscioutput();
	sprintf(output, "L'altro client si e' connesso\nLa partita e' iniziata");
	send(c1socket, output, DIM, 0);
	send(c2socket, output, DIM, 0);

	pulisciinput();
	recv(c1socket, input, DIM, 0);
	printf("Client1: %s", input);
	
	pulisciinput();
	recv(c2socket, input, DIM, 0);
	printf("Client2: %s", input);

	close(c1socket);
	close(c2socket);
	
	printf("Ho chiuso tutto\n");
	return 0;
}