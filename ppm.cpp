#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ppm.h"

unsigned char *load_ppm(const char filename[], int *_w, int *_h)
{
  char line[256];
  int i;
  int w,h;
  int v;
  FILE* f = fopen(filename, "r");
  fgets(line, sizeof(line), f);
  fgets(line, sizeof(line), f);
  fgets(line, sizeof(line), f);
  sscanf(line, "%d %d", &w, &h);
  fgets(line, sizeof(line), f);
  printf("%d %d\n", w, h);
  unsigned char* img = (unsigned char*)malloc(sizeof(unsigned char)*w*h*3);
  for (i=0; i<w*h; i++)
    {
        int v[3];
        fgets(line, sizeof(line), f);
        sscanf(line, "%d", &v[0]);
        fgets(line, sizeof(line), f);
        sscanf(line, "%d", &v[1]);
        fgets(line, sizeof(line), f);
        sscanf(line, "%d", &v[2]);
        img[3*i+0] = (unsigned char) (v[0]);
        img[3*i+1] = (unsigned char) (v[1]);
        img[3*i+2] = (unsigned char) (v[2]);
    }
  fclose(f);
  *_w = w;
  *_h = h;
  return img;
}

void save_ppm(const char filename[], unsigned char *img, int w, int h)
{
  int i;
  FILE* f2 = fopen(filename, "w");
  fprintf(f2, "P3\n");
  fprintf(f2, "#\n");
  fprintf(f2, "%d %d\n", w, h);
  fprintf(f2, "255\n");
  for (i=0; i<w*h; i++)
    {
      fprintf(f2, "%d\n%d\n%d\n", img[3*i+0], img[3*i+1], img[3*i+2]);
    }
  fclose(f2);
}
