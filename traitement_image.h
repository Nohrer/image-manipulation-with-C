#ifndef __TRAITEMENT_IMAGE__H__
#define __TRAITEMENT_IMAGE__H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Création de la structure de données Image qui contient les différents composente de l'image
typedef struct {
   int longueur;
   int hauteur;
   int resolution;
   unsigned char ***img;
} Image;

Image* image_creation(int l, int h, int r);
void initialiser_image_aleatoire(Image *image);
void initialiser_image_clavier(Image *image);
void initialiser_image_fichier(Image *image, const char *filename);
void afficher_image(Image *image);
void liberer_image(Image *image);

void write_data_file(const char *filename, Image *image) ;
void visualize_image_with_gnuplot(const char *data_filename, int index) ;


#endif