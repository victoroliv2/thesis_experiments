#include <vector>
#include <stdlib.h>
#include <string.h>

#include "tiledimage.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

bool rectangle_intersect (rectangle a, rectangle b, rectangle& out)
{
  if(a.y+a.height < b.y)            return false;
  if(a.y          > b.y+b.height)   return false;
  if(a.x+a.width  < b.x)            return false;
  if(a.x          > b.x+b.width)    return false;

  int x = MAX(a.x, b.x);
  int y = MAX(a.y, b.y);
  int k = MIN(a.x+a.width,  b.x+b.width);
  int w = MIN(a.y+a.height, b.y+b.height);

  out.x      = x;
  out.y      = y;
  out.width  = k-x;
  out.height = w-y;

  return true;
}

template<typename T>
TiledImage<T>::TiledImage (int w, int h, int tile_width, int tile_height)
  : Image<T>(w, h), tile_width(tile_width), tile_height(tile_height)
  {
    this->tiles = new std::vector< Tile<T> >();

    for (int y=0; y < this->height; y += this->tile_height)
      for (int x=0; x < this->width; x += this->tile_width)
        {
          rectangle r = {x, y, MIN(this->tile_width,  this->width - x),
                               MIN(this->tile_height, this->height - y)};
          Tile<T> t;
          t.data = new T[r.width * r.height];
          t.roi  = r;

          this->tiles->push_back(t);
        }
  }

template<typename T>
TiledImage<T>::~TiledImage ()
  {
    typename std::vector< Tile<T> >::iterator it;

    for (it = this->tiles->begin() ; it < this->tiles->end(); it++)
      {
        delete[] it->data;
      }

    delete this->tiles;
  }

template<typename T>
void TiledImage<T>::get (T *buf, rectangle r)
  {
    typename std::vector< Tile<T> >::iterator it;

    for (it=this->tiles->begin() ; it < this->tiles->end(); it++)
      {
        rectangle ri;
        if (rectangle_intersect (it->roi, r, ri))
          {
            T *buf_tmp = buf + ri.y * it->roi.width + ri.x;

            rectangle tmp = {ri.x - it->roi.x, ri.y - it->roi.y, ri.width, ri.height};
            size_t offset = (tmp.y * it->roi.width + tmp.x);
            for (int y = tmp.y; y < tmp.y + tmp.height; y++)
              {
                memcpy (it->data + offset, buf_tmp, tmp.width * sizeof(T));
                buf_tmp += r.width;
                offset  += it->roi.width;
              }
          }
      }
  }

template<typename T>
void TiledImage<T>::set (T *buf, rectangle r)
  {
    typename std::vector< Tile<T> >::iterator it;

    for (it=this->tiles->begin() ; it < this->tiles->end(); it++)
      {
        rectangle ri;
        if (rectangle_intersect (it->roi, r, ri))
          {
            T *buf_tmp = buf + ri.y * it->roi.width + ri.x;

            rectangle tmp = {ri.x - it->roi.x, ri.y - it->roi.y, ri.width, ri.height};
            size_t offset = (tmp.y * it->roi.width + tmp.x);;
            for (int y = tmp.y; y < tmp.y + tmp.height; y++)
              {
                memcpy (buf_tmp, it->data + offset, tmp.width * sizeof(T));
                buf_tmp += r.width;
                offset  += it->roi.width;
              }
          }
      }
  }

TiledImage<float> a (0, 0, 0, 0);
