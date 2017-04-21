#ifndef ENGINE_HH_
#define ENGINE_HH_

#include <SFML/Graphics.hpp>

#include "Graphics.hh"
#include "Console.hh"

enum CharType {
  alphanumeric,
  alphabetic,
  numeric
};

class Engine
{
public:
  Engine();
  ~Engine();

  bool openWindow();

  void graphicsLoop();
  bool updateLoop();
  int mainLoop();

  static char getChar(sf::Event event, CharType type);
  
private:
  sf::Vector2i _winsize;
  sf::RenderWindow *_win;
  Console *_console;
};

#endif /* !ENGINE_HH_ */
