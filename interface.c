#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

///============================================================

image *Image_a_modifie()
{
    image *I;
    char *chemin_vers_image[100];
    printf("Quelle image voulez-vous modifier ?\n");
    printf("Exemple de reponse attendu : images/NomImage.ppm\n");
    scanf("%s", chemin_vers_image);
    I = ReadImg(chemin_vers_image);

    return I;
}

///============================================================

int Choix ()
{
    int choix;
    printf("Que voulez-vous faire de l'image ?\n");
    printf("1 - Filtre gris\n");
    printf("2 - Filtre sepia\n");
    printf("3 - Filtre negatif\n");
    printf("4 - Filtre noir et blanc\n");
    printf("5 - Pixelisation de l'image \n");
    printf("6 - Filtre de lissage\n");
    printf("7 - Filtre d'accentuation\n");
    printf("8 - Quitter\n");
    printf("Entrez le numero de votre choix\n");
    scanf("%d", &choix);
    return choix;
}

///============================================================

bool Traiter_choix(image *I, int choix)
{
    bool end = false;
    char *chemin_vers_image_modifiee[100];

    switch (choix)
    {
        case 1 :
            I = Gris(I);
            printf("Quel nom voulez-vous donner a l'image modifier?\n");
            printf("Si vous voulez ecraser l'image d'origine il suffit de rentrer le meme nom(images/NomImage.ppm)\n");
            scanf("%s", chemin_vers_image_modifiee);
            SaveImg(I, chemin_vers_image_modifiee);
        break;

        case 2 :
            I = Sepia(I);
            printf("Quel nom voulez-vous donner a l'image modifier?\n");
            printf("Si vous voulez ecraser l'image d'origine il suffit de rentrer le meme nom(images/NomImage.ppm)\n");
            scanf("%s", chemin_vers_image_modifiee);
            SaveImg(I, chemin_vers_image_modifiee);
        break;

        case 3 :
            I = Negatif(I);
            printf("Quel nom voulez-vous donner a l'image modifier?\n");
            printf("Si vous voulez ecraser l'image d'origine il suffit de rentrer le meme nom(images/NomImage.ppm)\n");
            scanf("%s", chemin_vers_image_modifiee);
            SaveImg(I, chemin_vers_image_modifiee);
        break;

        case 4 :
            I = Seuillage(I);
            printf("Quel nom voulez-vous donner a l'image modifier?\n");
            printf("Si vous voulez ecraser l'image d'origine il suffit de rentrer le meme nom(images/NomImage.ppm)\n");
            scanf("%s", chemin_vers_image_modifiee);
            SaveImg(I, chemin_vers_image_modifiee);
        break;

        case 5 :
            I = Pixellisation(I);
            printf("Quel nom voulez-vous donner a l'image modifier?\n");
            printf("Si vous voulez ecraser l'image d'origine il suffit de rentrer le meme nom(images/NomImage.ppm)\n");
            scanf("%s", chemin_vers_image_modifiee);
            SaveImg(I, chemin_vers_image_modifiee);
        break;

        case 6 :
            I = FiltreLissage(I);
            printf("Quel nom voulez-vous donner a l'image modifier?\n");
            printf("Si vous voulez ecraser l'image d'origine il suffit de rentrer le meme nom(images/NomImage.ppm)\n");
            scanf("%s", chemin_vers_image_modifiee);
            SaveImg(I, chemin_vers_image_modifiee);
        break;

        case 7 :
            I = FiltreAccentuation(I);
            printf("Quel nom voulez-vous donner a l'image modifier?\n");
            printf("Si vous voulez ecraser l'image d'origine il suffit de rentrer le meme nom(images/NomImage.ppm)\n");
            scanf("%s", chemin_vers_image_modifiee);
            SaveImg(I, chemin_vers_image_modifiee);
        break;

        case 8 :
            end = true;
        break;
    }
    return end;
}

///============================================================

void menu()
{
    bool end = false;
    int i;
    image *I;

    do {
        do {
            I = Image_a_modifie();
        } while (I == NULL);

        i = Choix();
        end = Traiter_choix(I, i);

    } while (end == false);

    printf("fin programme\n");
}
