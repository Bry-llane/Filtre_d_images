#include <stdio.h>
#include <stdlib.h>
#include "image.h"

///=========================================================

image *AloueImg (int X, int Y)
{
    image *I = (image *)malloc(sizeof(image));

    pixel **Img = (pixel**)malloc(Y*sizeof(pixel*));
    for (int i=0; i<Y; i++){
        Img[i] = (pixel*)malloc(X*sizeof(pixel));
    }

    I->sizeX = X;
    I->sizeY = Y;
    I->tab = Img;

    return I;
}

///=========================================================

image *ReadImg(char *fichier)
{
    int X, Y, size, r, v, b;
	char mot[255];
	image *I;
	FILE *fd = fopen(fichier, "r");

	if (fd == NULL) {
        printf ("erreur lecture fichier\n");
        return NULL;
	}

	fscanf(fd, "%s", mot);
	if (mot[0] == 'P' && mot[1] == '3' ) {
        printf ("image en cours de lecture\n");
	} else {
	    printf ("erreur lecture fichier\n");
	    return NULL;
	}

	fgets(mot, 255, fd);
	fgets(mot, 255, fd);
	printf ("le commentaire de l'image est : %s\n", mot);

	fscanf(fd, "%d %d", &X, &Y);
	printf ("resolution de l'image: %d %d\n", X, Y);
	fgets(mot, 255, fd);

	fscanf(fd, "%d", &size);
	if (size == 255) {
        printf ("taille max: %d\n", size);
	} else {
	    printf ("erreur lecture fichier\n");
	    return NULL;
	}
	fgets(mot, 255, fd);

	I = AloueImg(X, Y);

	for (int j = 0; j < I->sizeY; j++){
        for (int i = 0; i < I->sizeX; i++){
            fscanf(fd, "%d %d %d", &r, &v, &b);
            I->tab[j][i].r = (octet) r;
            I->tab[j][i].v = (octet) v;
            I->tab[j][i].b = (octet) b;
        }
	}
	fclose(fd);

	return I;

}

///=========================================================

void SaveImg(image *I, char *tab)
{
    FILE *fd = fopen(tab, "w");
    fprintf(fd, "P3 \n#image modifiee\n%d %d \n255\n", I->sizeX, I->sizeY);

    for (int j = 0; j < I->sizeY; j++){
        for (int i = 0; i < I->sizeX; i++){
            fprintf(fd, "%d ", (int) I->tab[j][i].r);
            fprintf(fd, "%d ", (int) I->tab[j][i].v);
            fprintf(fd, "%d ", (int) I->tab[j][i].b);
        }
        fprintf(fd, "\n");
    }
    fclose(fd);
}

///=========================================================

image *Gris(image *I)
{
    for (int j = 0; j < I->sizeY; j++){
        for (int i = 0; i < I->sizeX; i++){
            int moyenne = 0.2126*I->tab[j][i].r + 0.7152*I->tab[j][i].v + 0.0722*I->tab[j][i].b;
            I->tab[j][i].r = (octet) moyenne;
            I->tab[j][i].v = (octet) moyenne;
            I->tab[j][i].b = (octet) moyenne;
        }
	}
	return I;
}

///=========================================================

image *Sepia(image *I)
{
  int seuil = 100;

  for (int j = 0; j < I->sizeY; j++){
        for (int i = 0; i < I->sizeX; i++){
            int moyenne = 0.2126*I->tab[j][i].r + 0.7152*I->tab[j][i].v + 0.0722*I->tab[j][i].b;
            if (moyenne<seuil){
                int k = moyenne/seuil;
                I->tab[j][i].r = (octet) 94*k;
                I->tab[j][i].v = (octet) 38*k;
                I->tab[j][i].b = (octet) 18*k;
            } else {
                int k = (moyenne - seuil)/(255 - seuil);
                I->tab[j][i].r = (octet) 94+k*(255-94);
                I->tab[j][i].v = (octet) 38+k*(255-38);
                I->tab[j][i].b = (octet) 18+k*(255-18);
            }
        }
	}
	return I;
}

///=========================================================

image *Negatif(image *I)
{
    for (int j = 0; j < I->sizeY; j++){
        for (int i = 0; i < I->sizeX; i++){
            I->tab[j][i].r = (octet) 255 - I->tab[j][i].r;
            I->tab[j][i].v = (octet) 255 - I->tab[j][i].v;
            I->tab[j][i].b = (octet) 255 - I->tab[j][i].b;
        }
	}
	return I;
}

///=========================================================

image *Seuillage(image *I)
{
  int seuil = 100;

  for (int j = 0; j < I->sizeY; j++){
        for (int i = 0; i < I->sizeX; i++){
            int moyenne = 0.2126*I->tab[j][i].r + 0.7152*I->tab[j][i].v + 0.0722*I->tab[j][i].b;
            if (moyenne<seuil){
                I->tab[j][i].r = (octet) 255;
                I->tab[j][i].v = (octet) 255;
                I->tab[j][i].b = (octet) 255;
            } else {
                I->tab[j][i].r = (octet) 0;
                I->tab[j][i].v = (octet) 0;
                I->tab[j][i].b = (octet) 0;
            }
        }
	}
	return I;
}

///=========================================================

image *Pixellisation(image *I)
{
    for (int j = 0; j < I->sizeY; j++){
        for (int i = 0; i < I->sizeX; i++){
            int r = I->tab[j][i].r;
            int v = I->tab[j][i].v;
            int b = I->tab[j][i].b;
            if (r > v && r > b){
                I->tab[j][i].r = (octet) 255;
                I->tab[j][i].v = (octet) 0;
                I->tab[j][i].b = (octet) 0;
            } else if (v > r && v > b) {
                I->tab[j][i].r = (octet) 0;
                I->tab[j][i].v = (octet) 255;
                I->tab[j][i].b = (octet) 0;
            } else if (b > r && b > v) {
                I->tab[j][i].r = (octet) 0;
                I->tab[j][i].v = (octet) 0;
                I->tab[j][i].b = (octet) 255;
            } else {
                I->tab[j][i].r = (octet) r;
                I->tab[j][i].v = (octet) v;
                I->tab[j][i].b = (octet) b;
            }
        }
	}
	return I;
}

///=========================================================

image *FiltreLissage(image *I)
{
    return I;
}

///=========================================================

image *FiltreAccentuation(image *I)
{
    return I;
}

///=========================================================
