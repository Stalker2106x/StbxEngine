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

  void unbindall();
  bool unbind(std::string element);
  bool bind(std::string action, std::string control);
  void listAllBinds(Console &c);
  Control *getKey(const std::string &action);
  
private:
  std::map<std::string, Control> _binds;
};

#endif /* !KEYBINDS_HH_ */
