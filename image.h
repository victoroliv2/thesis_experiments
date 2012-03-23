struct rectangle
{
  int x, y, width, height;
};

template<typename T>
class Image
{
  public:
    int width, height;

    Image (int width, int height) : width(width), height(height) {}
    virtual ~Image();
    virtual void get (T *buf, rectangle r) = 0;
    virtual void set (T *buf, rectangle r) = 0;
};