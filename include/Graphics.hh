#ifndef GRAPHICS_HH_
#define GRAPHICS_HH_

#include <SFML/Graphics.hpp>

typedef struct s_point
{
  int x;
  int y;
  
  s_point(int xa, int ya)
  {
    x = xa;
    y = ya;
  }

  s_point() {}
  
} t_point;

typedef struct s_size
{
  int width;
  int height;

  s_size(int w, int h)
  {
    width = w;
    height = h;
  }
  
  s_size() {}
  
} t_size;

class Graphics
{
public:
  Graphics();
  ~Graphics();

  void setTexture(sf::Texture texture);

  t_point pos;
  t_size size;
  sf::Color color;

private:
  sf::Sprite _sprite;
};

#endif /* !GRAPHICS_HH_ */
