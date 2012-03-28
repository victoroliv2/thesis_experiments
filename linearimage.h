#ifndef LINEARIMAGE_H
#define LINEARIMAGE_H

#include "image.h"

template<typename T>
class LinearImage : public Image<T>
{
  public:
    T *data;

    LinearImage (int w, int h);
    ~LinearImage ();

    void get (T *buf, rectangle r);
    void set (T *buf, rectangle r);
};

#endif
