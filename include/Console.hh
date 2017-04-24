#ifndef CONSOLE_HH_
#define CONSOLE_HH_

#include <list>
#include <deque>
#include <stdexcept>
#include <iostream>
#include "Graphics.hh"

class Console
{
public:
  Console(const sf::Vector2i &winsize);
  ~Console();

  void initGraphics(const sf::Vector2i &winsize);
  
  void toggle();

  bool isActive() const;

  void output(const std::string &msg);
  void input();

  void updateInput(const sf::Event &event);
  void update(const sf::Event &event);
  void draw(sf::RenderWindow *win);
  
private:
  bool _active;
  sf::Sprite _bg, _inputArea;
  sf::Font _font;
  sf::Text _inputValue;

  std::deque<sf::Text *> _output;
  std::deque<std::string> _input;
  int _currentIndex, _fontSize;
};

#endif /* !CONSOLE_HH_ */
