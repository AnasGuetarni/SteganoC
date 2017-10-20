// Voir www.bien-programmer.fr/bits.htm
#include <stdio.h>                                                    
#include <stdlib.h>

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

void ecritureRGB(unsigned char* fichier,unsigned char r, unsigned char g, unsigned char b)
{
	// masque pour extraire les bits des valeurs rgb une par une  UTILISATION D'UN (ET) LOGIQUE
	unsigned char masq[7];
	masq[0]=0x01; // extraction du bit au rang 2^0
	masq[1]=0x02; // extraction du bit au rang 2^1
	masq[2]=0x04; // extraction du bit au rang 2^2
	masq[3]=0x08;
	masq[4]=0x10;
	masq[5]=0x20;
	masq[6]=0x40;

	printf("cara : %x \n",fichier[0]);


	// BOUCLE UNIQUEMENT POUR LE PREMIER CARACTERE fichier[0]  a modifier pour faire tous les carcteres
	int i, bits=0;
	for (i=0; i < 3; i++)
	{
		if ((masq[i]&fichier[0]) != 0)// si le nombre vaut une valeure différente de zero c'est que le bits restant vaut 1
			bits = 1;
		else // si tous les bits sont a zero c'est que le bits rechercher vaut 0
			bits = 0;
 
		r = bitFaible(r,bits);

		if ((masq[i+1]&fichier[0]) != 0)// si le nombre vaut une valeure différente de zero c'est que le bits restant vaut 1
                        bits = 1;
                else
                        bits = 0;

		g = bitFaible(g,bits);

		if ((masq[i+2]&fichier[0]) != 0)// si le nombre vaut une valeure différente de zero c'est que le bits restant vaut 1
                        bits = 1;
                else
                        bits = 0;
		b = bitFaible(b,bits);

// TROUVER UN MOYEN DE DONNER LES VALEURS RGB DU PROCHAIN PIXEL

/*	if ((masq[i]&fichier[1]) != 0)// si le nombre vaut une valeure différente de zero c'est que le bits restant vaut 1
                        bits = 1;
                else
                        bits = 0;

                r = bitFaible(r,bits);

                if ((masq[i+1]&fichier[1]) != 0)// si le nombre vaut une valeure différente de zero c'est que le bits restant vaut 1
                        bits = 1;
                else
                        bits = 0;

                g = bitFaible(g,bits);

                if ((masq[i+2]&fichier[1]) != 0)// si le nombre vaut une valeure différente de zero c'est que le bits restant vaut 1
                        bits = 1;
                else
                        bits = 0;
                b = bitFaible(b,bits);



if ((masq[i]&fichier[1]) != 0)// si le nombre vaut une valeure différente de zero c'est que le bits restant vaut 1
                        bits = 1;
                else
                        bits = 0;

                r = bitFaible(r,bits);*/

	}



}




int main() {
	// simulation de (r,g,b)
	unsigned char r = 0x52; // 0101 0010(2)
	unsigned char g = 0x64; // (2)
	unsigned char b = 0x98; // (2)

	r = bitFaible(r, 1);
	printf("r avant : %x \n",r);
	printf("g avant : %x \n",g);
	printf("b avant : %x \n",b);

	unsigned char *fichier[15];
        extractionFichier(fichier);
	ecritureRGB(fichier, r,g,b);

	printf("r apres : %x \n",r);
	printf("g apres : %x \n",g);
	printf("b apres : %x \n",b);

    return 0;
}

