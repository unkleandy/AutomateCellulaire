#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

typedef unsigned char Regle;
typedef bool Cellule;

const int taille{ 80 };
const int repetitions{ 24 };

void initialiserTab(Cellule *pt);
void afficherTab(Cellule *pt);
void appliquerRegleTab(Cellule *pt, Regle regle);
void afficherMatrice(Cellule *pt, Regle regle);
void afficherreglebinaire(Regle regle);
void afficherTab(Cellule *tab);
void afficherEneteteMatrice(Regle regle);
void appliquerRegleTab(Cellule *tab, Regle regle);
void appliquerRegleCellule(Cellule *tab, int position, Regle regle);
char menu();
bool menuQuitter();
void automate();

void main(void)
{
	char reponse = menu();
	if (reponse != 'Q' && reponse !='q')
	{
		automate();
	}
}

char menu()
{
	printf("Automate Cellulaire Evolutif appuyer une touche pour continuer Q pour quitter");
	return _getch();
}

void automate()
{
	srand(unsigned int(time(nullptr)));
	Regle regle{};
	Cellule tab[taille]{};
	initialiserTab(tab);
	afficherMatrice(tab, regle);
	char reponse = _getch();
	bool quitter = false;


	while (!quitter)
	{
		if (reponse != 'R' && reponse != 'r')
		{
			++regle;
		}

		initialiserTab(tab);
		afficherMatrice(tab, regle);
		reponse = _getch();

		if (reponse != 'Q' && reponse != 'q') 
		{

			quitter = menuQuitter();
		}
	}
	
}

bool menuQuitter() {
	printf("voulez vous quitter? (O/N)");
	char reponse = _getch();
	if (reponse == 'o' || reponse == 'O')
	{
		return true;
	}
	else
	{
		return false;
	}
}

void afficherEneteteMatrice(Regle regle)
{
	printf("regle No %i ", regle);
	afficherreglebinaire(regle);
	printf("\n");
}

void afficherreglebinaire(Regle regle)
{
	bool bit[8];
	for (int i{}; i < 8; ++i)
	{
		bit[7-i] = regle >> i & 1;
	}

	for (int i = 0; i < 8; ++i)
	{
		if (bit[i])
			printf("1");
		else
			printf("0");
	}
}


void afficherMatrice(Cellule *tab, Regle regle)
{
	if (tab != nullptr) {
		system("cls");
		afficherEneteteMatrice(regle);
		for (int i{}; i < repetitions; ++i)
		{
			afficherTab(tab);
			appliquerRegleTab(tab, regle);
		}
	}
}

//fct initialer tableau random
void initialiserTab(Cellule *tab)
{
	if (tab != nullptr)
	{
		for (int i{}; i < taille; ++i)
		{
			tab[i] = rand() % 2;
		}
	}
}

//fct affichage
void afficherTab(Cellule *tab)
{
	if (tab != nullptr) 
	{
		for (int i{}; i < taille; ++i)
		{
			/*
			char cell = tab[i] ? "*" : " ";
			printf(cell);
			*/

			if (tab[i])
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}


//fct appliquer la Regle
void appliquerRegleCellule(Cellule *tab, int position, Regle regle)
{
	if (tab != nullptr)
	{
		static Cellule gauche{};
		static Cellule milieu{};
		Cellule droite{};
		unsigned char combinaison{};

		if (position == 0)
		{
			droite = tab[taille-1];
			milieu = tab[position];
		}
		if (position == taille - 1)
		{
			gauche = tab[0];
		}
		else
		droite = tab[position + 1];

		combinaison = gauche | (milieu << 1) | (droite << 2);

		tab[position] = regle >> combinaison & 1;
		gauche = milieu;
		milieu = droite;
	}
}


void appliquerRegleTab(Cellule *tab, Regle regle)
{
	if (tab != nullptr) 
	{
		for (int i{}; i < taille; ++i)
		{
			appliquerRegleCellule(tab, i, regle);
		}
	}
}
