#include <stdio.h>
#include <vector>
#include <sys/time.h>

#include "types.h"
#include "linearimage.h"
#include "tiledimage.h"
#include "ppm.h"

timeval t1, t2;
double elapsedTime;

#define START_TIME gettimeofday(&t1, NULL)
#define STOP_TIME(msg)  gettimeofday(&t2, NULL), \
                        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0, \
                        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0, \
                        printf ("%s: %f ms\n", msg, elapsedTime)

void rgbu8_to_rgbaf (unsigned char *img_u8, rgbaf *img_f, int w, int h)
{
  int i;
  for (int i=0; i < w * h; i++)
    {
      img_f[i].r = (img_u8[3*i+0] / 255.0f);
      img_f[i].g = (img_u8[3*i+1] / 255.0f);
      img_f[i].b = (img_u8[3*i+2] / 255.0f);
      img_f[i].a = 1.0f;
    }
}

void rgbaf_to_rgbu8 (rgbaf *img_f, unsigned char *img_u8, int w, int h)
{
  int i;

  for (int i=0; i < w * h; i++)
    {
      img_u8[3*i+0] = (img_f[i].r * img_f[i].a * 255.0f);
      img_u8[3*i+1] = (img_f[i].g * img_f[i].a * 255.0f);
      img_u8[3*i+2] = (img_f[i].b * img_f[i].a * 255.0f);
    }
}


int main (int argc, char *argv[])
{

  if (argc < 4)
  {
    printf ("error\n");
    return 1;
  }

  int w, h;
  unsigned char *img_u8 = load_ppm(argv[1], &w, &h);

  float brightness = 1.5f;
  float contrast   = 0.5f;

  rgbaf *img_f      = new rgbaf [w * h];
  rgbaf *img_linear = new rgbaf [w * h];
  rgbaf *img_tiled  = new rgbaf [w * h];

  rgbu8_to_rgbaf (img_u8, img_f, w, h);

  rectangle r = {0, 0, w, h};


  {
  LinearImage<rgbaf> linear_in  (w, h);
  LinearImage<rgbaf> linear_out (w, h);
  linear_in.set(img_f, r);

  float *in  = (float *)(linear_in.data);
  float *out = (float *)(linear_out.data);

  START_TIME;

  int size = w * h;
  int i = 0;
  while (size--)
    {
      out[0] = (in[0] - 0.5f) * contrast + brightness + 0.5f;
      out[1] = (in[1] - 0.5f) * contrast + brightness + 0.5f;
      out[2] = (in[2] - 0.5f) * contrast + brightness + 0.5f;
      out[3] = in[3];
      in  += 4;
      out += 4;
    }

  STOP_TIME("linear");

  linear_out.get(img_linear, r);
  rgbaf_to_rgbu8 (img_linear, img_u8, w, h);
  save_ppm(argv[2], img_u8, w, h);
  }


  {
  TiledImage<rgbaf> tiled_in  (w, h, 512, 512);
  TiledImage<rgbaf> tiled_out (w, h, 512, 512);
  tiled_in.set(img_f, r);

  typename std::vector< Tile<rgbaf> >::iterator iter_in;
  typename std::vector< Tile<rgbaf> >::iterator iter_out;

  iter_in  = tiled_in .tiles->begin();
  iter_out = tiled_out.tiles->begin();

  START_TIME;

  while (iter_in  != tiled_in .tiles->end() &&
         iter_out != tiled_out.tiles->end())
    {
      float *in  = (float *)(iter_in->data);
      float *out = (float *)(iter_out->data);
      int size = iter_in->roi.width * iter_in->roi.height;
      int i = 0;
      while (size--)
        {
          out[0] = (in[0] - 0.5f) * contrast + brightness + 0.5f;
          out[1] = (in[1] - 0.5f) * contrast + brightness + 0.5f;
          out[2] = (in[2] - 0.5f) * contrast + brightness + 0.5f;
          out[3] = in[3];
          in  += 4;
          out += 4;
        }

      iter_in ++;
      iter_out ++;
    }

  STOP_TIME("tiled");

  tiled_out.get(img_tiled, r);
  rgbaf_to_rgbu8 (img_tiled, img_u8, w, h);
  save_ppm(argv[3], img_u8, w, h);
  }

  return 0;
}
