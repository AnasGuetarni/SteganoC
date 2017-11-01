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
#include "decode_function.h"
#include "ppm.h"

/**
 * Display the program's syntaxe.
 * @param argv program's command line arguments
 */

int convertDecimalToBinary(int n);

void usage(char **argv) {
	fprintf(stderr, "usage: %s [-ascii] input output\n"\
			"Where input is a PPM file and output is a text file and the optional argument\n"\
            "-ascii specifies to write a plain text PPM file.\n", basename(argv[0]));
	exit(EXIT_FAILURE);
}

/**
 * Program entry point.
 * @param argc command line argument count
 * @param argv program's command line arguments
 */
int main() {

}
