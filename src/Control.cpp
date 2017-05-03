#include "Control.hh"

Control::Control(const sf::Keyboard::Key key)
{
  _key = new sf::Keyboard::Key(key);
  _mbutton = NULL;
  _mwheel = NULL;
  _type = Key;
}

Control::Control(const sf::Mouse::Button btn)
{
  _key = NULL;
  _mbutton = new sf::Mouse::Button(btn);
  _mwheel = NULL;
  _type = MButton;
}

Control::Control(const sf::Mouse::Wheel whl)
{
  _key = NULL;
  _mbutton = NULL;
  _mwheel = new sf::Mouse::Wheel(whl);
  _type = MWheel;
}

Control::~Control()
{
  
}

bool Control::isTriggered(const sf::Event &e)
{
  switch(_type)
    {
    case Key:
      if (e.type == sf::Event::KeyPressed && e.key.code == *_key)
	return (true);
      else
	return (false);
      break;
    case MButton:
      if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == *_mbutton)
	return (true);
      else
	return (false);
      break;
    }
  return (false);
}

bool Control::isReleased(const sf::Event &e)
{
  switch(_type)
    {
    case Key:
      if (e.type == sf::Event::KeyReleased && e.key.code == *_key)
	return (true);
      else
	return (false);
      break;
    case MButton:
      if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == *_mbutton)
	return (true);
      else
	return (false);
      break;
    }
  return (false);
}
