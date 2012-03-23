#include <string.h>
#include <stdio.h>

unsigned char *load_pgm(const char filename[], int *_w, int *_h)
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
  unsigned char* img = (unsigned char*)malloc(sizeof(unsigned char)*w*h);
  for (i=0; i<w*h; i++)
    {
        fgets(line, sizeof(line), f);
        sscanf(line, "%d", &v);
        img[i] = (unsigned char) (v);
    }
  fclose(f);
  *_w = w;
  *_h = h;
  return img;
}

void save_pgm(const char filename[], unsigned char *img, int w, int h)
{
  int i;
  FILE* f2 = fopen(filename, "w");
  fprintf(f2, "P2\n");
  fprintf(f2, "#\n");
  fprintf(f2, "%d %d\n", w, h);
  fprintf(f2, "255\n");
  for (i=0; i<w*h; i++)
    {
      fprintf(f2, "%d\n", img[i]);
    }
  fclose(f2);
}
