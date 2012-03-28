#include "linearimage.h"
#include "tiledimage.h"
#include "pgm.h"

int main (int argc, char *argv[])
{

int w, h;
unsigned char *img_u8 = load_pgm(argv[1], &w, &h);

float *img_f = new float [w * h];
for (int i=0; i < w * h; i++)
  {
    img_f[i] = (img_u8[i] / 255.0f);
  }

rectangle r = {0, 0, w, h};

/*
{
LinearImage<float> linear_img (w, h);
linear_img.set(img_f, r);
linear_img.get(img_f, r);

for (int i=0; i < w * h; i++)
  {
    img_u8[i] = (img_f[i] * 255.0f);
  }

save_pgm(argv[2], img_u8, w, h);
}
*/


{
TiledImage<float> tiled_img (w, h, 64, 64);
tiled_img.set(img_f, r);
tiled_img.get(img_f, r);

for (int i=0; i < w * h; i++)
  {
    img_u8[i] = (img_f[i] * 255.0f);
  }

save_pgm(argv[2], img_u8, w, h);
}


return 0;
}
