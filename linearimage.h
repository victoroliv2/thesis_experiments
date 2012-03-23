#include "image.h"

template<typename T>
class LinearImage : public Image<T>
{
  T *data;

  public:
    LinearImage (int w, int h);
    ~LinearImage ();

    void get (T *buf, rectangle r);
    void set (T *buf, rectangle r);
}