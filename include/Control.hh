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
  friend bool operator==(const Control &a, const Control &b);
public:
  Control(std::string);
  Control(std::string, const sf::Keyboard::Key key);
  Control(std::string, const sf::Mouse::Button btn);
  Control(std::string, const sf::Mouse::Wheel whl);
  Control(const Control &c);
  ~Control();

  const std::string &getBindStr();
  bool isTriggered(const sf::Event &e);
  bool isReleased(const sf::Event &e);


  static std::map<std::string, Control> keys;
  
private:
  std::string _bindstr;
  ControlType _type;
  sf::Keyboard::Key *_key;
  sf::Mouse::Button *_mbutton;
  sf::Mouse::Wheel *_mwheel;
};

#endif /* !CONTROL_HH_ */
