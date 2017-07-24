#include "Engine.hpp"
#include "Keybinds.hh"

using namespace stb;

Keybinds::Keybinds()
{

}

Keybinds::~Keybinds()
{

}

void Keybinds::bindEnv(Engine *e)
{
  _e = e;
}

bool Keybinds::isBound(const Control &c)
{
  return (_binds.find(c) != _binds.end());
}

void Keybinds::unbindall()
{
  _binds.clear();
}

bool Keybinds::unbind(std::string element)
{
  std::map<Control, std::string>::iterator it;

  try {
  if ((it = _binds.find(Control::keys.at(element))) != _binds.end())
    {
      _binds.erase(it);
      return (true);
    }
  else if (Commands::cmdlist.find(element) != Commands::cmdlist.end())
    {
      for (it = _binds.begin(); it != _binds.end(); it++)
	{
	  if ((*it).second == element)
	    {
	      _binds.erase(it);
	      return (true);
	    }
	}
    }
  }
  catch (...) { return (false); }
  return (false);
}

bool Keybinds::bind(std::string control, std::string action)
{
  Control *b;
  try {
    b = &Control::keys.at(control);
    if (_binds.find(*b) != _binds.end())
      _binds.erase(*b);
    _binds.emplace(*b, action);
  }
  catch (...) { return (false); }
  return (true);
}

void Keybinds::listAllBinds()
{
	_e->console->output("");
  for (std::map<Control, std::string>::iterator it = _binds.begin(); it != _binds.end(); it++)
    {
      _e->console->insertLastOutput(it->second+" = "+it->first.getBindStr());
      if (std::next(it, 1) != _binds.end())
	  _e->console->insertLastOutput(", ");
    }
}

Control *Keybinds::getKey(const std::string &action)
{
  try {
    if (Commands::cmdlist.find(action) != Commands::cmdlist.end())
      {
	for (std::map<Control, std::string>::iterator it = _binds.begin(); it != _binds.end(); it++)
	  {
	    if ((*it).second == action)
	      {
		return (new Control(it->first.getBindStr()));
	      }
	  }
      }
  }
  catch (...) { return (NULL); }
  return (NULL);
}

void Keybinds::update(sf::Event &e)
{
  try {
    switch (e.type)
      {
      case sf::Event::KeyPressed:
	Commands::parseCmd(*_e, _binds.at(Control("", e.key.code)));
	break;
      case sf::Event::MouseButtonPressed:
	break;
      case sf::Event::MouseWheelMoved:
	break;
      default:
	return;
	break;
      }
  }
  catch(...) { return; }
}
