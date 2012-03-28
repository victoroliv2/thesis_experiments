#include <stdio.h>

#include "types.h"
#include "linearimage.h"
#include "tiledimage.h"
#include "ppm.h"

int main (int argc, char *argv[])
{

if (argc < 4)
{
  printf ("error\n");
  return 1;
}

int w, h;
unsigned char *img_u8 = load_ppm(argv[1], &w, &h);

rgb *img_f = new rgb [w * h];
rgb *img_g = new rgb [w * h];
for (int i=0; i < w * h; i++)
  {
    img_f[i].r = (img_u8[3*i+0] / 255.0f);
    img_f[i].g = (img_u8[3*i+1] / 255.0f);
    img_f[i].b = (img_u8[3*i+2] / 255.0f);
    img_f[i].a = 1.0f;
  }

rectangle r = {0, 0, w, h};

{
LinearImage<rgb> linear_img (w, h);
linear_img.set(img_f, r);
linear_img.get(img_g, r);

for (int i=0; i < w * h; i++)
  {
    img_u8[3*i+0] = (img_f[i].r * img_f[i].a * 255.0f);
    img_u8[3*i+1] = (img_f[i].g * img_f[i].a * 255.0f);
    img_u8[3*i+2] = (img_f[i].b * img_f[i].a * 255.0f);
  }

save_ppm(argv[2], img_u8, w, h);
}


{
TiledImage<rgb> tiled_img (w, h, 64, 64);
tiled_img.set(img_f, r);
tiled_img.get(img_g, r);

for (int i=0; i < w * h; i++)
  {
    img_u8[3*i+0] = (img_f[i].r * img_f[i].a * 255.0f);
    img_u8[3*i+1] = (img_f[i].g * img_f[i].a * 255.0f);
    img_u8[3*i+2] = (img_f[i].b * img_f[i].a * 255.0f);
  }

save_ppm(argv[3], img_u8, w, h);
}


return 0;
}
