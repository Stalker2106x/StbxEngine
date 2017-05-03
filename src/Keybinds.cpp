#include "Keybinds.hh"

Keybinds::Keybinds()
{

}

Keybinds::~Keybinds()
{

}

bool Keybinds::bind(std::string &action, Control &ctrl)
{
  return (_binds.emplace(action, ctrl).second);
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
