#include "Keybinds.hh"

Keybinds::Keybinds()
{

}

Keybinds::~Keybinds()
{

}

bool Keybinds::bind(std::string action, std::string control)
{
  try {
    if (_binds.find(action) != _binds.end())
      _binds.erase(action);
    _binds.emplace(action, Control::keys.at(control));
  }
  catch (...)
    {
      return (false);
    }
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
