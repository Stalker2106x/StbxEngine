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

  void bindEnv(Console *, Engine *);
  bool isBound(const Control &c);

  void unbindall();
  bool unbind(std::string element);
  bool bind(std::string ctrl, std::string action);
  void listAllBinds(Console &c);
  Control *getKey(const std::string &action);
  void update(sf::Event &e);

private:
  Console *_c;
  Engine *_e;
  std::map<Control, std::string> _binds;
};

#endif /* !KEYBINDS_HH_ */
