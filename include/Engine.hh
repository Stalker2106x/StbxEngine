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
  void handleArgs(int argc, char **argv);
  void videoParamSet(const std::string &, const int &);
  sf::Image capture();

  void graphicsLoop();
  virtual void draw() = 0;
  bool updateLoop();
  virtual bool update(sf::Event &) = 0;
  int mainLoop();

  static char getChar(sf::Event event, CharType type, bool useBinds = true);
  static struct tm *getTime();
  static std::string getTimestamp();

  void quit();

  static Keybinds *keybinds;
  static Console *console;
  
private:
  bool _quit, _fullscreen, _vsync;
  sf::Vector2i _winsize;
  sf::RenderWindow *_win;
};

#endif /* !ENGINE_HH_ */
