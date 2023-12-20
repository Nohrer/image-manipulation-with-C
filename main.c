#include <stdlib.h>
#include <stdio.h>
#include "traitement_image.h"
int main ()
{
Image *image =image_creation(10,10,3);

initialiser_image_aleatoire(image);
write_data_file("data.txt",image);
visualize_image_with_gnuplot("data.txt",0);
liberer_image(image);


return 0;
}