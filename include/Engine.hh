#ifndef ENGINE_HH_
#define ENGINE_HH_

#include <SFML/Graphics.hpp>

#include "Console.hh"
#include "Keybinds.hh"

enum CharType {
  alphanumeric,
  alphabetic,
  numeric
};

class Engine
{
public:
  Engine(int width = 800, int height = 600);
  ~Engine();

  bool openWindow(int , int);

  sf::Vector2i getWindowSize() const;
  void videoParamSet(const std::string &, const int &);
  sf::Image capture();

  void graphicsLoop();
  bool updateLoop();
  int mainLoop();

  static char getChar(sf::Event event, CharType type);
  static struct tm *getTime();
  static std::string getTimestamp();
  
  void quit();

  static Keybinds *keybinds;

private:
  bool _quit;
  sf::Vector2i _winsize;
  sf::RenderWindow *_win;
  Console *_console;
};

#endif /* !ENGINE_HH_ */
