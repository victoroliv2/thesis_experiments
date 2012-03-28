#ifndef __PPM_H__
#define __PPM_H__

unsigned char *load_ppm(const char filename[], int *_w, int *_h);
void save_ppm(const char filename[], unsigned char *img, int w, int h);

#endif
