/*!
 * @file      Keybinds.hh
 * @class     Keybinds
 * @brief     Dictionnary of current bound keys at runtime
 *
 *            This class is designed to manipulate all the Control associations in your program with actions.
 *            It contains all the keys bound since the program was ran, and does NOT save state to files.
 *            For key memorizing, you must store binds in your config file, and execute it at startup
 */

#ifndef KEYBINDS_HH_
#define KEYBINDS_HH_

#include <SFML/Graphics.hpp>
#include <map>
#include "Console.hh"
#include "Control.hh"

#define BINDREF(x) (Engine::keybinds->getKey(x))
#define BINDTRIGGERED(x, evn) (Engine::keybinds->getKey(x)->isTriggered(evn))

class Keybinds
{
public:
  Keybinds();
  ~Keybinds();

  void bindEnv(Engine *);
  bool isBound(const Control &c);

  void unbindall();
  bool unbind(std::string element);
  bool bind(std::string ctrl, std::string action);
  void listAllBinds();
  Control *getKey(const std::string &action);
  void update(sf::Event &e);

private:
  Console *_c;
  Engine *_e;
  std::map<Control, std::string> _binds;
};

#endif /* !KEYBINDS_HH_ */
