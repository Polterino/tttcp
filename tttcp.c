/* Polterino
	A simple tic tac toe game
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define dim 3
char griglia[dim][dim];
char carattere;
char caratterebot = 'O';

void inserisci(int x, int y, char scelta)
{
	griglia[x][y] = scelta;
}

void inserisciRandom()
{
	int x, y;
	do
	{
		x = rand() % 3;
		y = rand() % 3;
	} while(posizione_occupata(x, y) == 1);
	griglia[x][y] = caratterebot;
}

int posizione_occupata(int i, int j)
{
	if(griglia[i][j] == carattere || griglia[i][j] == caratterebot)
		return 1;
	return 0;
}

void stampagriglia()
{
	printf("   1   2   3\n");
	for(int i = 0; i < dim; ++i)
	{
		printf("%c ", i + 97);
		for(int j = 0; j < dim; ++j)
		{
			if(griglia[i][j] != NULL)
			{
				if(j != dim - 1)
					printf(" %c |", griglia[i][j]);
				else
					printf(" %c\n", griglia[i][j]);
			}
			else
			{
				if(j != dim - 1)
					printf("   |");
				else
					printf("\n");
			}
		}
	}
}

int charToInt(char var)
{
	if(var == 'a')
		return 0;
	else if(var == 'b')
		return 1;
	return 2;
}

int vinto(char c)
{
	/* Controlla le righe */
	for(int i = 0; i < dim; ++i)
	{
		if(griglia[i][0] == c && griglia[i][1] == c && griglia[i][2] == c)
			return 1;
	}

	/* Controlla le colonne */
	for(int i = 0; i < dim; ++i)
	{
		if(griglia[0][i] == c && griglia[1][i] == c && griglia[2][i] == c)
			return 1;
	}

	/* Controlla le diagonali */
	if(griglia[0][0] == c && griglia[1][1] == c && griglia[2][2] == c)
		return 1;
	if(griglia[0][2] == c && griglia[1][1] == c && griglia[2][0] == c)
		return 1;
	return 0;
}

int caselle_finite()
{
	for(int i = 0; i < dim; ++i)
	{
		for(int j = 0; j < dim; ++j)
		{
			if(griglia[i][j] != carattere && griglia[i][j] != caratterebot)
				return 0;
		}
	}
	return 1;
}

int main(int argc, char **argv)
{
	bool gioco = true, occupato;
	char x;
	int y;

	srand(time(NULL));

	printf("Benvenuto nel programma tttcp\n");
	printf("Scegli che carattere vuoi usare: ");
	scanf("%c", &carattere);
	stampagriglia();

	while(gioco)
	{
		/* Resetto le variabili ogni volta */
		occupato = true;
		x = 'a';
		y = 1;
		do
		{
			do
			{
				if(x != 'a' && x != 'b' && x != 'c')
					printf("Attenzione! Devi scegliere a, b oppure c\n");
				printf("Inserisci la x (a, b, c): ");
				scanf(" %c", &x);
			} while(x != 'a' && x != 'b' && x != 'c');

			do
			{
				if(y != 1 && y != 2 && y != 3)
					printf("Attenzione! Devi scegliere 1, 2 oppure 3\n");
				printf("Inserisci la y (1, 2, 3): ");
				scanf("%d", &y);
			} while(y != 1 && y != 2 && y != 3);
			y--;

			if(griglia[charToInt(x)][y] != carattere && griglia[charToInt(x)][y] != caratterebot)
				occupato = false;
			else
				printf("Attenzione! Posizione occupata, perfavore scegline un'altra\n");
		} while(occupato);
		
		inserisci(charToInt(x), y, carattere);
		stampagriglia();

		/* Dato che l'utente ha sempre l'ultima mossa, controlla che le caselle non siano finite */
		if(caselle_finite() == 1)
			gioco = false;

		if(vinto(carattere) == 1)
		{
			gioco = false;
			printf("\nHai vinto!\n");
			return 0;
		}
		else
		{
			if(gioco)
			{
				inserisciRandom();
				stampagriglia();
			}
			if(vinto(caratterebot) == 1)
			{
				gioco = false;
				printf("\nHai perso!\n");
				return 0;
			}
		}
	}
	printf("\nHai pareggiato\n");
	return 0;
}