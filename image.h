///====================Octet==============================

typedef unsigned char octet;

///====================Pixel==============================

typedef struct pixel {
    octet r;
    octet v;
    octet b;
} pixel;

///====================Image==============================

typedef struct image {
    int sizeX;
    int sizeY;
    pixel **tab;
} image;

///====================Fonctions==============================

image *AloueImg (int X, int Y);
image *ReadImg(char *fichier);
void SaveImg(image *I, char *tab);
image *Gris(image *I);
image *Sepia(image *I);
image *Negatif(image *I);
image *Seuillage(image *I);
image *Pixellisation(image *I);
image *FiltreLissage(image *I);
image *FiltreAccentuation(image *I);
