// Voir www.bien-programmer.fr/bits.htm
#include <stdio.h>                                                    
#include <stdlib.h>

// Cette fonction remplace par 0 ou par 1 le bit de poids faible dans 
// un nombre binaire donnée
// nb : nombre binaire , bits: 0 ou 1
unsigned char bitFaible(unsigned char nb, int bits)
{
	unsigned char resultat = 0x00;
	unsigned char un = 0x01; // 0000 0001(2)
	unsigned char ze = 0xFE; // 1111 1110(2)

	if (bits)
		// met a 1 le bit de poids faible
		resultat = nb | un; // opérateur OU
	else
		// met a 0 le bit de poids faible
		resultat = nb & ze; // opérateur ET

    return resultat;
}

// ouverture fichier + extraction 
void extractionFichier(unsigned char *c)
{
	int i =0;
    int caractere = 0;
    FILE* fichier = NULL;
    fichier = fopen("coucou.txt", "r");

    if (fichier != NULL)
    {
	while (caractere != EOF)
	{
		caractere = fgetc(fichier);
		c[i] = caractere;
		i++;
	}
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier coucou.txt");
    }

	fclose(fichier);
}

void ecritureRGB(unsigned char* fichier,unsigned char* r, unsigned char* g, unsigned char* b)
{
	// masque pour extraire les bits des valeurs RGB une par une  UTILISATION D'UN (ET) LOGIQUE
	// Ces masques serviront a extraire chaque bits d'un caractère
	unsigned char masq[7] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40};

	// BOUCLE UNIQUEMENT POUR LE PREMIER CARACTERE fichier[0]  a modifier pour faire tous les carctères
	// On considére que le bits 2^0 du caractére ira dans le bit de poids faible de R. L'ordre est le suivant R->G->B
	int bits=0;

		if ((masq[0]&fichier[0]) != 0)// si le nombre vaut une valeure différente de zero c'est que le bits restant vaut 1
			bits = 1;
		else // si tous les bits sont a zero c'est que le bits rechercher vaut 0
			bits = 0;
 
		// On enregistre le bit 2^0 du caractère dans le nombre binaire R (RGB)
		*r = bitFaible(*r,bits);

		if ((masq[1]&fichier[0]) != 0)// si le nombre vaut une valeure différente de zero c'est que le bits restant vaut 1
			bits = 1;
		else
			bits = 0;

		
		*g = bitFaible(*g,bits);

		if ((masq[2]&fichier[0]) != 0)// si le nombre vaut une valeure différente de zero c'est que le bits restant vaut 1
                        bits = 1;
                else
                        bits = 0;

		*b = bitFaible(*b,bits);

// TROUVER UN MOYEN DE DONNER LES VALEURS RGB DU PROCHAIN PIXEL

}

int main() {
	// simulation de (r,g,b)
	unsigned char r = 0x52; // 0101 0010(2)
	unsigned char g = 0x64; // (2)
	unsigned char b = 0x98; // (2)

	printf("r avant : %x \n",r);
	printf("g avant : %x \n",g);
	printf("b avant : %x \n",b);

	unsigned char fichier[15];
	extractionFichier(fichier);
	ecritureRGB(fichier, &r,&g,&b);

	printf("r apres : %x \n",r);
	printf("g apres : %x \n",g);
	printf("b apres : %x \n",b);

    return 0;
}
