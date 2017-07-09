/*!
 * @file      Engine.hpp
 * @class     Engine
 * @brief     Main class for graphic conception
 *
 *            This the base class of the project.
 *            You must inherit from this class to start using the graphic engine. Start by implementing the update and draw routine,
 *            related to the behaviour you expect in your game.
 *            In your main function, simply instantiate your child Engine, then call the mainLoop method to start the program.
 */

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <SFML/Graphics.hpp>
#include "Console.hh"
#include "Keybinds.hh"
#include "HUD.hh"

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

  sf::RenderWindow *getWindowHandle();
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
  static HUD *hud;

  static Engine *instance;

protected:
  bool _quit, _fullscreen, _vsync;
  sf::Vector2i _winsize;
  sf::RenderWindow *_win;
};

#endif /* !ENGINE_HPP_ */
