/*
 * @author Group12 - Guetarni Anas - Gay Melvin - Keraim Marwan
 * @date 18 Oct 2017
 * @brief Routines to read and write PPM files.
 *
 * Both binary (P6 type) and plain ASCII (P3 type) PPM file types are supported.
 * The PPM file format is described here: http://netpbm.sourceforge.net/doc/ppm.html
 * To convert a JPG image into a binary PPM file (P6) with ImageMagick:
 * convert image.jpg output.ppm
 * To convert a JPG image into a plain ASCII PPM file (P3) with ImageMagick:
 * convert -compress none image.jpg output.ppm
 */

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include "encode_function.h"
#include "ppm.h"
#include <pthread.h>

/**
 * Display the program's syntaxe.
 * @param argv program's command line arguments
 */

void usage(char **argv) {
	fprintf(stderr, "usage: %s -- encode text_file input_image output_image thread_count where input_image and output_image are PPM files and thread_count the number of threads to use\n", basename(argv[0]));
	exit(EXIT_FAILURE);
}

void *thread(void *thread_id) {
        int id = *((int *) thread_id);
        printf("Hello from thread %d\n", id);

        return NULL;
}

int main(int argc, char **argv) {
	char *input = NULL, *output = NULL;
	long nbT = 0;
	char *fileInput = NULL;
	enum PPM_TYPE type;
	int m = 0, f = 0;
	
	// Parse command line
	if (argc == 5) {
		//type = PPM_BINARY;
		fileInput = argv[1];
		input = argv[2];
		output = argv[3];
	} else if (argc ==  6) {
		if (strcmp("-ascii", argv[1]) != 0) usage(argv);
		//type = PPM_ASCII;
		fileInput = argv[1];
		input = argv[2];
		output = argv[3];
	} else {
		usage(argv);
	}

	nbT = strtol(argv[4], NULL, 10); // Convertie la chaine de caractère qui contient le chiffre en entier

	struct intervalle {
		int intervalMin[nbT];
		int intervalMax[nbT];
	};

	struct intervalle intervalleT;

	type = PPM_BINARY;

	long size = sizeFile(fileInput);

	double value = size / nbT; /* problème si le nombre d'itération est un nombre a virgule ???? */
	printf("Size: %ld\n", size);
	printf("La valeur pour chaque thread est de: %f\n",value);
	printf("nbT : %ld \n", nbT);

	for(int i=0;i<nbT;i++){
		intervalleT.intervalMin[i] = value * i;
		intervalleT.intervalMax[i] = value * (i+1);
		printf("intervalMin: %i / intervalMax: %i\n",intervalleT.intervalMin[i],intervalleT.intervalMax[i]);
	}
	intervalleT.intervalMax[nbT-1] = size;
	printf("intervalMax: %i\n",intervalleT.intervalMax[nbT-1]);

	pthread_t threads[nbT];
	for (int i = 0; i < nbT; i++) {
	    if (pthread_create(&threads[i], NULL, thread, &i) != 0) {
            fprintf(stderr, "pthread_create failed!\n");
            return EXIT_FAILURE;
        }
	    
		if(pthread_join(threads[i], NULL) != 0) {
		     fprintf(stderr, "pthread_join failed!\n");
		     return EXIT_FAILURE;
		}

    }
    
	// Load image
	img_t *img = load_ppm(input);
	if (!img) {
		fprintf(stderr, "Failed loading \"%s\"!\n", input); // Si l'on arrive pas a charger l'image
		return EXIT_FAILURE; // On retourne une erreur
	}

	// On affiche la taille de l'image
	printf("Height: %d\n", img->height);
	printf("Width: %d\n", img->width);

	printf("taille :  %ld \n", size);

	unsigned char *fichier = NULL;
	fichier = malloc(size*sizeof(unsigned char));
    if (fichier == NULL) // Si l'allocation a échoué
    {
        exit(0); // On arrête immédiatement le programme
    }

	if ((size*2)>=(img->height*img->width)){ // si la taille du fichier est plus petite que la taille de l'image
		printf("La taille du texte est plus grande que la capacité de l'image\n");
		exit(0); // si c'est plus plus grand on arrete le programme
	}
	else
		printf("La taille du texte est plus petite que la taille de l'image (C'est bon !)\n"); // sinon on continue le programme

	// On va alors extraire les caractères du fichier
    extractionFichier(fichier);

	// On parcours toute l'image et applique la fonction ecritureRGB
	for (int j = 0; j < img->height; j++) { // On parcours l'image sur la hauteur
		for (int i = 0; i < img->width; i++) { // On parcours l'image dans sa largeur
			pixel_t *p = &img->pix[j][i]; //On place dans une structure les valeurs des pixels
			ecritureRGB(fichier, &p->r,&p->g,&p->b,&m,&f,size); // On écrit l'encodage sur le fichier en question
		}
	}

	free(fichier); // On libère le fichier

	// Write image
	if (!write_ppm(output, img, type)) {
		fprintf(stderr, "Failed writing \"%s\"!\n", output); // Si l'on arrive pas a écrire sur l'image
		free_img(img); // On libere l'espace alloué a l'image
		return EXIT_FAILURE; // On retourne une erreur
	}

	// Si l'on arrive a écrire sur l'image
	free_img(img); // On libere l'espace alloué à l'image
	return EXIT_SUCCESS; // On retourne un succès
}
