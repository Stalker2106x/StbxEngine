#ifndef CONTROL_HH_
#define CONTROL_HH_

#include <SFML/Graphics.hpp>

enum ControlType {
  Key,
  MButton,
  MWheel
};

class Control
{
public:
  Control(const sf::Keyboard::Key key);
  Control(const sf::Mouse::Button btn);
  Control(const sf::Mouse::Wheel whl);
  Control(const Control &c);
  ~Control();

  bool isTriggered(const sf::Event &e);
  bool isReleased(const sf::Event &e);


  static std::map<std::string, Control> keys;
  
private:
  ControlType _type;
  sf::Keyboard::Key *_key;
  sf::Mouse::Button *_mbutton;
  sf::Mouse::Wheel *_mwheel;
};

#endif /* !CONTROL_HH_ */
