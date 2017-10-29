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

/**
 * Display the program's syntaxe.
 * @param argv program's command line arguments
 */

int convertDecimalToBinary(int n);

void usage(char **argv) {
	fprintf(stderr, "usage: %s [-ascii] input output\n"\
			"Where input and output are PPM files and the optional argument\n"\
            "-ascii specifies to write a plain text PPM file.\n", basename(argv[0]));
	exit(EXIT_FAILURE);
}

/**
 * Program entry point.
 * @param argc command line argument count
 * @param argv program's command line arguments
 */
int main(int argc, char **argv) {
	char *input, *output;
	enum PPM_TYPE type;
	int m = 0, f = 0;

	// Parse command line
	if (argc == 3) {
		type = PPM_BINARY;
		input = argv[1];
		output = argv[2];
	} else if (argc ==  4) {
		if (strcmp("-ascii", argv[1]) != 0) usage(argv);
		type = PPM_ASCII;
		input = argv[2];
		output = argv[3];
	} else {
		usage(argv);
	}

	// Load image
	img_t *img = load_ppm(input);
	if (!img) {
		fprintf(stderr, "Failed loading \"%s\"!\n", input);
		return EXIT_FAILURE;
	}

	printf("Height: %d\n", img->height);
	printf("Width: %d\n", img->width);
	
	long size = sizeFile("gulliver.txt");
	printf("taille :  %ld \n", size);

	unsigned char *fichier = NULL;
	fichier = malloc(size*sizeof(unsigned char));
    if (fichier == NULL) // Si l'allocation a échoué
    {
        exit(0); // On arrête immédiatement le programme
    }
    
    extractionFichier(fichier);

	//int test = 0;

	// 1) Il faudra vérifier que l'on peut coder tout le fichier dans l'image

	// Reduce image's first quadrant's brightness intensity
	for (int j = 0; j < img->height; j++) {
		for (int i = 0; i < img->width; i++) {
			pixel_t *p = &img->pix[j][i];
			
			/*printf("r avant : %x \n",p->r);
			printf("g avant : %x \n",p->g);
			printf("b avant : %x \n",p->b);
			printf("fichier : %x, numero : %d \n", fichier[f], f);
			scanf("%d", &test);
			printf("\n");*/
			
			ecritureRGB(fichier, &p->r,&p->g,&p->b,&m,&f);
			
			/*printf("r apres : %x \n",p->r);
			printf("g apres : %x \n",p->g);
			printf("b apres : %x \n",p->b);
			printf("fichier : %x, numero : %d \n", fichier[f], f);
			scanf("%d", &test);
			printf("\n");*/
			
		}
	}
	
	free(fichier);

	// Write image
	if (!write_ppm(output, img, type)) {
		fprintf(stderr, "Failed writing \"%s\"!\n", output);
		free_img(img);
		return EXIT_FAILURE;
	}

	free_img(img);
	return EXIT_SUCCESS;
}
