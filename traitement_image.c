#include "traitement_image.h"



// Création d'image contient 3 couche de la méme taille qui représente les couleurs RGB 
Image* image_creation(int l, int h, int r) {
  Image* image = malloc(sizeof(Image));
  image->longueur = l;
  image->hauteur = h;
  image->resolution = r;

  image->img = malloc(3 * sizeof(unsigned char**));
  for (int i = 0; i < 3; i++) {
    image->img[i] = malloc((r*l) * sizeof(unsigned char*));
    for (int j = 0; j < r*l; j++) {
      image->img[i][j] = malloc((r*h) * sizeof(unsigned char));
    }
  }

  return image;
}

// Initialiser l'image avec  des valeurs aléatoires

 void initialiser_image_aleatoire(Image *image) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < image->resolution * image->longueur; j++) {
      for (int k = 0; k < image->resolution * image->hauteur; k++) {
        image->img[i][j][k] = rand() % 256;
      }
    }
  }}


//intialiser l'image avec clavier
void initialiser_image_clavier(Image *image) {
  for (int i = 0; i < 3; i++) {
    printf("Enter pixel values for Layer %d:\n", i + 1);

    for (int j = 0; j < image->resolution * image->longueur; j++) {
      for (int k = 0; k < image->resolution * image->hauteur; k++) {
        printf("Enter value for pixel at position (%d, %d): ", j, k);
        scanf("%hhu", &image->img[i][j][k]);
      }
    }
  }
}

// intialiser avec un fichier
void initialiser_image_fichier(Image *image, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening the file.\n");
        exit(EXIT_FAILURE);
  }


    for (int j = 0; j < image->resolution * image->longueur; j++) {
        for (int k = 0; k < image->resolution * image->hauteur; k++) {
             unsigned int r, g, b;
            if (fscanf(file, "%u,%u,%u ", &r,&g,&b) == 3) {

                image->img[0][j][k] = (unsigned char)r;
                image->img[1][j][k] = (unsigned char)g;
                image->img[2][j][k] = (unsigned char)b;
            } 
        }
    }

    fclose(file);
}



void afficher_image(Image *image) {

    for (int j = 0; j < image->longueur * image->resolution; j++) {
      for (int k = 0; k < image->hauteur * image->resolution; k++) {
       
        printf("%d,%d,%d ", 
          image->img[0][image->resolution * j][image->resolution * k],
          image->img[1][image->resolution * j][image->resolution * k],
          image->img[2][image->resolution * j][image->resolution * k]);
      }
      printf("\n");
    }

    printf("\n");
  }



void liberer_image(Image *image) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < image->resolution * image->longueur; j++) {
      free(image->img[i][j]);
    }
    free(image->img[i]);
  }

  free(image->img);

  free(image);
}

void write_data_file(const char *filename, Image *image) {
    FILE *data_file = fopen(filename, "w");

    if (data_file == NULL) {
        fprintf(stderr, "Error opening the data file for writing.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < image->resolution * image->longueur; i++) {
        for (int j = 0; j < image->resolution * image->hauteur; j++) {
            fprintf(data_file, "%d %d %d\n", image->img[0][i][j], image->img[1][i][j], image->img[2][i][j]);
        }
        fprintf(data_file,"\n");
    }

    fclose(data_file);
}


void visualize_image_with_gnuplot(const char *data_filename,int index) {
    FILE *gnuplot = popen("C:\\gnuplot\\bin\\gnuplot -persistent", "w");
    FILE *fp = fopen("data.txt", "r");
    if (gnuplot == NULL) {
        fprintf(stderr, "Error opening gnuplot.\n");
          fclose(fp);

        exit(EXIT_FAILURE);
    }

fprintf(gnuplot, "unset pm3d\n");  
fprintf(gnuplot, "set palette rgbformulae 3,12,15\n"); 
fprintf(gnuplot, "set view map\n");
fprintf(gnuplot, "set size ratio -1\n");  

fprintf(gnuplot, "set size square\n");  
fprintf(gnuplot, "splot '-' matrix with image\n"); 
int r, g, b;
while (fscanf(fp, "%d %d %d", &r, &g, &b) == 3) {
    fprintf(gnuplot, "%d %d %d\n", r, g, b);
}
fprintf(gnuplot, "e\n"); 


   fclose(fp);
pclose(gnuplot);
    
}