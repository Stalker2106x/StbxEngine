#include "Keybinds.hh"

Keybinds::Keybinds()
{

}

Keybinds::~Keybinds()
{

}

bool Keybinds::bind(std::string &action, std::string &control)
{
  _binds.emplace(action, (*Control::keys.find(control)).second);
  return (true);
}

Control *Keybinds::getKey(const std::string &action)
{
  Control *ctrl;
  
  try {
    ctrl = &_binds.at(action);
      }
  catch (...)
    {
      return (NULL);
    }
  return (ctrl);
}
