#include <stdlib.h>

#include "linearimage.h"

template<typename T>
LinearImage<T>::LinearImage (int w, int h) : Image<T>(w, h)
  {
    this->data = new T[w * h];
  }

template<typename T>
LinearImage<T>::~LinearImage ()
  {
    delete[] this->data;
  }

template<typename T>
LinearImage<T>::get (T *buf, rectangle r)
  {
      size_t offset = (r.y * this->width + r.x);
      for (int y = r.y; y < r.y + r.height; y++)
        {
          memcpy (buf, this->data + offset, r.width * sizeof(T));
          buf    += r.width;
          offset += this->width;
        }
    }

template<typename T>
LinearImage<T>::set (T *buf, rectangle r)
  {
    size_t offset = (r.y * this->width + r.x);
    for (int y = r.y; y < r.y + r.height; y++)
      {
        memcpy (this->data + offset, buf, r.width * sizeof(T));
        buf    += r.width;
        offset += this->width;
      }
  }
