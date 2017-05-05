#include "Control.hh"

//public map
std::map<std::string, Control> keys = {
  {"a", Control(sf::Keyboard::Key::A)},
  {"b", Control(sf::Keyboard::Key::B)},
  {"c", Control(sf::Keyboard::Key::C)},
  {"d", Control(sf::Keyboard::Key::D)},
  {"e", Control(sf::Keyboard::Key::E)},
  {"f", Control(sf::Keyboard::Key::F)},
  {"g", Control(sf::Keyboard::Key::G)},
  {"h", Control(sf::Keyboard::Key::H)},
  {"i", Control(sf::Keyboard::Key::I)},
  {"j", Control(sf::Keyboard::Key::J)},
  {"k", Control(sf::Keyboard::Key::K)},
  {"l", Control(sf::Keyboard::Key::L)},
  {"m", Control(sf::Keyboard::Key::M)},
  {"n", Control(sf::Keyboard::Key::N)},
  {"o", Control(sf::Keyboard::Key::O)},
  {"p", Control(sf::Keyboard::Key::P)},
  {"q", Control(sf::Keyboard::Key::Q)},
  {"r", Control(sf::Keyboard::Key::R)},
  {"s", Control(sf::Keyboard::Key::S)},
  {"t", Control(sf::Keyboard::Key::T)},
  {"u", Control(sf::Keyboard::Key::U)},
  {"v", Control(sf::Keyboard::Key::V)},
  {"w", Control(sf::Keyboard::Key::W)},
  {"x", Control(sf::Keyboard::Key::X)},
  {"y", Control(sf::Keyboard::Key::Y)},
  {"z", Control(sf::Keyboard::Key::Z)},
  {"num0", Control(sf::Keyboard::Key::Num0)},
  {"num1", Control(sf::Keyboard::Key::Num1)},
  {"num2", Control(sf::Keyboard::Key::Num2)},
  {"num3", Control(sf::Keyboard::Key::Num3)},
  {"num4", Control(sf::Keyboard::Key::Num4)},
  {"num5", Control(sf::Keyboard::Key::Num5)},
  {"num6", Control(sf::Keyboard::Key::Num6)},
  {"num7", Control(sf::Keyboard::Key::Num7)},
  {"num8", Control(sf::Keyboard::Key::Num8)},
  {"num9", Control(sf::Keyboard::Key::Num9)},
  {"escape", Control(sf::Keyboard::Key::Escape)},
  {"lcontrol", Control(sf::Keyboard::Key::LControl)},
  {"lshift", Control(sf::Keyboard::Key::LShift)},
  {"lalt", Control(sf::Keyboard::Key::LAlt)},
  {"lsystem", Control(sf::Keyboard::Key::LSystem)},
  {"rcontrol", Control(sf::Keyboard::Key::RControl)},
  {"rshift", Control(sf::Keyboard::Key::RShift)},
  {"ralt", Control(sf::Keyboard::Key::RAlt)},
  {"rsystem", Control(sf::Keyboard::Key::RSystem)},
  {"menu", Control(sf::Keyboard::Key::Menu)},
  {"lbracket", Control(sf::Keyboard::Key::LBracket)},
  {"rbracket", Control(sf::Keyboard::Key::RBracket)},
  {";", Control(sf::Keyboard::Key::SemiColon)},
  {",", Control(sf::Keyboard::Key::Comma)},
  {".", Control(sf::Keyboard::Key::Period)},
  {"'", Control(sf::Keyboard::Key::Quote)},
  {"/", Control(sf::Keyboard::Key::Slash)},
  {"\\", Control(sf::Keyboard::Key::BackSlash)},
  {"~", Control(sf::Keyboard::Key::Tilde)},
  {"=", Control(sf::Keyboard::Key::Equal)},
  {"-", Control(sf::Keyboard::Key::Dash)},
  {"space", Control(sf::Keyboard::Key::Space)},
  {"enter", Control(sf::Keyboard::Key::Return)},
  {"backspace", Control(sf::Keyboard::Key::BackSpace)},
  {"tab", Control(sf::Keyboard::Key::Tab)},
  {"pgup", Control(sf::Keyboard::Key::PageUp)},
  {"pgdn", Control(sf::Keyboard::Key::PageDown)},
  {"end", Control(sf::Keyboard::Key::End)},
  {"home", Control(sf::Keyboard::Key::Home)},
  {"inser", Control(sf::Keyboard::Key::Insert)},
  {"delete", Control(sf::Keyboard::Key::Delete)},
  {"+", Control(sf::Keyboard::Key::Add)},
  {"-", Control(sf::Keyboard::Key::Subtract)},
  {"*", Control(sf::Keyboard::Key::Multiply)},
  {"/", Control(sf::Keyboard::Key::Divide)},
  {"leftarrow", Control(sf::Keyboard::Key::Left)},
  {"rightarrow", Control(sf::Keyboard::Key::Right)},
  {"uparrow", Control(sf::Keyboard::Key::Up)},
  {"downarrow", Control(sf::Keyboard::Key::Down)},
  {"kp0", Control(sf::Keyboard::Key::Numpad0)},
  {"kp1", Control(sf::Keyboard::Key::Numpad1)},
  {"kp2", Control(sf::Keyboard::Key::Numpad2)},
  {"kp3", Control(sf::Keyboard::Key::Numpad3)},
  {"kp4", Control(sf::Keyboard::Key::Numpad4)},
  {"kp5", Control(sf::Keyboard::Key::Numpad5)},
  {"kp6", Control(sf::Keyboard::Key::Numpad6)},
  {"kp7", Control(sf::Keyboard::Key::Numpad7)},
  {"kp8", Control(sf::Keyboard::Key::Numpad8)},
  {"kp9", Control(sf::Keyboard::Key::Numpad9)},
  {"f1", Control(sf::Keyboard::Key::F1)},
  {"f2", Control(sf::Keyboard::Key::F2)},
  {"f3", Control(sf::Keyboard::Key::F3)},
  {"f4", Control(sf::Keyboard::Key::F4)},
  {"f5", Control(sf::Keyboard::Key::F5)},
  {"f6", Control(sf::Keyboard::Key::F6)},
  {"f7", Control(sf::Keyboard::Key::F7)},
  {"f8", Control(sf::Keyboard::Key::F8)},
  {"f9", Control(sf::Keyboard::Key::F9)},
  {"f10", Control(sf::Keyboard::Key::F10)},
  {"f11", Control(sf::Keyboard::Key::F11)},
  {"f12", Control(sf::Keyboard::Key::F12)},
  {"f13", Control(sf::Keyboard::Key::F13)},
  {"f14", Control(sf::Keyboard::Key::F14)},
  {"f15", Control(sf::Keyboard::Key::F15)},
  {"pause", Control(sf::Keyboard::Key::Pause)}
};

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

Control::Control(const Control &c)
{
  _type = c._type;
  _key = new sf::Keyboard::Key(*c._key);
  _mbutton = new sf::Mouse::Button(*c._mbutton);
  _mwheel = new sf::Mouse::Wheel(*c._mwheel);
}

Control::~Control()
{
  switch(_type)
    {
    case Key:
      delete (_key);
      break;
    case MButton:
      delete (_mbutton);
      break;
    }  
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

