#ifndef DECODE_FONCTION
#define DECODE_FONCTION

unsigned char bitFaible(unsigned char nb, int bits);
void extractionFichier(unsigned char *c);
void writeFile(unsigned char *fichier, char output);
void ecritureRGB(unsigned char* fichier,unsigned char* r, unsigned char *g, unsigned char *b, int *m, int *f, long taille);

#endif
