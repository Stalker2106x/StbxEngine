#include "Control.hh"

//public map
std::map<std::string, Control> Control::keys = {
  {"a", Control("a", sf::Keyboard::Key::A)},
  {"b", Control("b", sf::Keyboard::Key::B)},
  {"c", Control("c", sf::Keyboard::Key::C)},
  {"d", Control("d", sf::Keyboard::Key::D)},
  {"e", Control("e", sf::Keyboard::Key::E)},
  {"f", Control("f", sf::Keyboard::Key::F)},
  {"g", Control("g", sf::Keyboard::Key::G)},
  {"h", Control("h", sf::Keyboard::Key::H)},
  {"i", Control("i", sf::Keyboard::Key::I)},
  {"j", Control("j", sf::Keyboard::Key::J)},
  {"k", Control("k", sf::Keyboard::Key::K)},
  {"l", Control("l", sf::Keyboard::Key::L)},
  {"m", Control("m", sf::Keyboard::Key::M)},
  {"n", Control("n", sf::Keyboard::Key::N)},
  {"o", Control("o", sf::Keyboard::Key::O)},
  {"p", Control("p", sf::Keyboard::Key::P)},
  {"q", Control("q", sf::Keyboard::Key::Q)},
  {"r", Control("r", sf::Keyboard::Key::R)},
  {"s", Control("s", sf::Keyboard::Key::S)},
  {"t", Control("t", sf::Keyboard::Key::T)},
  {"u", Control("u", sf::Keyboard::Key::U)},
  {"v", Control("v", sf::Keyboard::Key::V)},
  {"w", Control("w", sf::Keyboard::Key::W)},
  {"x", Control("x", sf::Keyboard::Key::X)},
  {"y", Control("y", sf::Keyboard::Key::Y)},
  {"z", Control("z", sf::Keyboard::Key::Z)},
  {"num0", Control("num0", sf::Keyboard::Key::Num0)},
  {"num1", Control("num1", sf::Keyboard::Key::Num1)},
  {"num2", Control("num2", sf::Keyboard::Key::Num2)},
  {"num3", Control("num3", sf::Keyboard::Key::Num3)},
  {"num4", Control("num4", sf::Keyboard::Key::Num4)},
  {"num5", Control("num5", sf::Keyboard::Key::Num5)},
  {"num6", Control("num6", sf::Keyboard::Key::Num6)},
  {"num7", Control("num7", sf::Keyboard::Key::Num7)},
  {"num8", Control("num8", sf::Keyboard::Key::Num8)},
  {"num9", Control("num9", sf::Keyboard::Key::Num9)},
  {"escape", Control("escape", sf::Keyboard::Key::Escape)},
  {"lcontrol", Control("lcontrol", sf::Keyboard::Key::LControl)},
  {"lshift", Control("lshift", sf::Keyboard::Key::LShift)},
  {"lalt", Control("lalt", sf::Keyboard::Key::LAlt)},
  {"lsystem", Control("lsystem", sf::Keyboard::Key::LSystem)},
  {"rcontrol", Control("rcontrol", sf::Keyboard::Key::RControl)},
  {"rshift", Control("rshift", sf::Keyboard::Key::RShift)},
  {"ralt", Control("ralt", sf::Keyboard::Key::RAlt)},
  {"rsystem", Control("rsystem", sf::Keyboard::Key::RSystem)},
  {"menu", Control("menu", sf::Keyboard::Key::Menu)},
  {"lbracket", Control("lbracket", sf::Keyboard::Key::LBracket)},
  {"rbracket", Control("rbracket", sf::Keyboard::Key::RBracket)},
  {";", Control(";", sf::Keyboard::Key::SemiColon)},
  {",", Control(",", sf::Keyboard::Key::Comma)},
  {".", Control(".", sf::Keyboard::Key::Period)},
  {"'", Control("'", sf::Keyboard::Key::Quote)},
  {"/", Control("/", sf::Keyboard::Key::Slash)},
  {"\\", Control("\\", sf::Keyboard::Key::BackSlash)},
  {"~", Control("~", sf::Keyboard::Key::Tilde)},
  {"=", Control("=", sf::Keyboard::Key::Equal)},
  {"-", Control("-", sf::Keyboard::Key::Dash)},
  {"space", Control("space", sf::Keyboard::Key::Space)},
  {"enter", Control("enter", sf::Keyboard::Key::Return)},
  {"backspace", Control("backspace", sf::Keyboard::Key::BackSpace)},
  {"tab", Control("tab", sf::Keyboard::Key::Tab)},
  {"pgup", Control("pgup", sf::Keyboard::Key::PageUp)},
  {"pgdn", Control("pgdn", sf::Keyboard::Key::PageDown)},
  {"end", Control("end", sf::Keyboard::Key::End)},
  {"home", Control("home", sf::Keyboard::Key::Home)},
  {"inser", Control("inser", sf::Keyboard::Key::Insert)},
  {"delete", Control("delete", sf::Keyboard::Key::Delete)},
  {"+", Control("+", sf::Keyboard::Key::Add)},
  {"-", Control("-", sf::Keyboard::Key::Subtract)},
  {"*", Control("*", sf::Keyboard::Key::Multiply)},
  {"/", Control("/", sf::Keyboard::Key::Divide)},
  {"leftarrow", Control("leftarrow", sf::Keyboard::Key::Left)},
  {"rightarrow", Control("rightarrow", sf::Keyboard::Key::Right)},
  {"uparrow", Control("uparrow", sf::Keyboard::Key::Up)},
  {"downarrow", Control("downarrow", sf::Keyboard::Key::Down)},
  {"kp0", Control("kp0", sf::Keyboard::Key::Numpad0)},
  {"kp1", Control("kp1", sf::Keyboard::Key::Numpad1)},
  {"kp2", Control("kp2", sf::Keyboard::Key::Numpad2)},
  {"kp3", Control("kp3", sf::Keyboard::Key::Numpad3)},
  {"kp4", Control("kp4", sf::Keyboard::Key::Numpad4)},
  {"kp5", Control("kp5", sf::Keyboard::Key::Numpad5)},
  {"kp6", Control("kp6", sf::Keyboard::Key::Numpad6)},
  {"kp7", Control("kp7", sf::Keyboard::Key::Numpad7)},
  {"kp8", Control("kp8", sf::Keyboard::Key::Numpad8)},
  {"kp9", Control("kp9", sf::Keyboard::Key::Numpad9)},
  {"f1", Control("f1", sf::Keyboard::Key::F1)},
  {"f2", Control("f2", sf::Keyboard::Key::F2)},
  {"f3", Control("f3", sf::Keyboard::Key::F3)},
  {"f4", Control("f4", sf::Keyboard::Key::F4)},
  {"f5", Control("f5", sf::Keyboard::Key::F5)},
  {"f6", Control("f6", sf::Keyboard::Key::F6)},
  {"f7", Control("f7", sf::Keyboard::Key::F7)},
  {"f8", Control("f8", sf::Keyboard::Key::F8)},
  {"f9", Control("f9", sf::Keyboard::Key::F9)},
  {"f10", Control("f10", sf::Keyboard::Key::F10)},
  {"f11", Control("f11", sf::Keyboard::Key::F11)},
  {"f12", Control("f12", sf::Keyboard::Key::F12)},
  {"f13", Control("f13", sf::Keyboard::Key::F13)},
  {"f14", Control("f14", sf::Keyboard::Key::F14)},
  {"f15", Control("f15", sf::Keyboard::Key::F15)},
  {"pause", Control("pause", sf::Keyboard::Key::Pause)}
};

Control::Control(std::string bindstr)
{
  _bindstr = bindstr;
  _type = Null;
  _key = NULL;
  _mbutton = NULL;
  _mwheel = NULL;
}

Control::Control(std::string bind, const sf::Keyboard::Key key) : Control(bind)
{
  _key = new sf::Keyboard::Key(key);
  _type = Key;
}

Control::Control(std::string bind, const sf::Mouse::Button btn) : Control(bind)
{
  _mbutton = new sf::Mouse::Button(btn);
  _type = MButton;
}

Control::Control(std::string bind, const int whl) : Control(bind)
{
  _mwheel = new int(whl);
  _type = MWheel;
}

Control::Control(const Control &c) : Control("default")
{
  _bindstr = c._bindstr;
  _type = c._type;
  if (c._key != NULL)
    _key = new sf::Keyboard::Key((*c._key));
  else if (c._mbutton != NULL)
    _mbutton = new sf::Mouse::Button((*c._mbutton));
  else if (c._mwheel != NULL)
    _mwheel = new int((*c._mwheel));
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
    case MWheel:
      delete (_mwheel);
      break;
    default:
      break;
    }  
}

std::string Control::getBindStr() const
{
  return (_bindstr);
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
    case MWheel:
      if (e.type == sf::Event::MouseWheelMoved && e.mouseWheel.delta >= 0)
	return ((*_mwheel) == Up ? true : false);
      else
	return ((*_mwheel) == Up ? false : true);
      break;
    default:
      return (false);
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
    case MWheel:
      if (e.type != sf::Event::MouseWheelMoved)
	return (true);
      else
	return (false);
      break;
    default:
      return (false);
    }
  return (false);
}

//Can be optimized with types use.
bool operator==(const Control &a, const Control &b)
{
  if (((a._key != NULL && b._key != NULL) && (*a._key) == (*b._key))
      || ((a._mbutton != NULL && b._mbutton != NULL)  && (*a._mbutton) == (*b._mbutton))
      || ((a._mwheel != NULL && b._mwheel != NULL)  && (*a._mwheel) == (*b._mwheel)))
    return (true);
  return (false);
}

bool operator<(const Control &a, const Control &b)
{
  if (((a._key != NULL && b._key != NULL) && (*a._key) < (*b._key))
      || ((a._mbutton != NULL && b._mbutton != NULL)  && (*a._mbutton) < (*b._mbutton))
      || ((a._mwheel != NULL && b._mwheel != NULL)  && (*a._mwheel) < (*b._mwheel)))
    return (true);
  return (false);  
}
