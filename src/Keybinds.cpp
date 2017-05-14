#include "Keybinds.hh"

Keybinds::Keybinds()
{

}

Keybinds::~Keybinds()
{

}

void Keybinds::unbindall()
{
  _binds.clear();
}

bool Keybinds::unbind(std::string element)
{
  std::map<std::string, Control>::iterator it;
  
  if ((it = _binds.find(element)) != _binds.end())
    {
      _binds.erase(it);
      return (true);
    }
  else if (Control::keys.find(element) != Control::keys.end())
    {
      for (it = _binds.begin(); it != _binds.end(); it++)
	{
	  if ((*it).second == Control::keys.at(element))
	    {
	      _binds.erase(it);
	      return (true);
	    }
	}
    }
  return (false);
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

void Keybinds::listAllBinds(Console &c)
{
  c.output("");
  for (std::map<std::string, Control>::iterator it = _binds.begin(); it != _binds.end(); it++)
    {
      c.insertLastOutput(it->first+" = "+it->second.getBindStr());
    }
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
