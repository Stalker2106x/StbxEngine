#ifndef CONSOLE_HH_
#define CONSOLE_HH_

#include <list>
#include <deque>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "Commands.hh"

#define PROMPT		(">")
#define CURSOR		("_")
#define COLOR_ESC	("\\\\#")
#define COLOR_ERROR	("\\\\#240077077")

typedef struct s_color
{
  int r;
  int g;
  int b;
} t_color;

class Console
{
public:
  Console(Engine &e);
  ~Console();

  void initGraphics(const sf::Vector2i &winsize);

  void toggle();
  void clear();

  bool isActive() const;
  void setLineCount(const unsigned int &count);
  sf::Color convertColorCode(std::string code);
  
  void output(std::string msg);
  void output(std::string color, std::string msg);
  void insertLastOutput(const std::string &msg);
  void input();

  void updateInput(const sf::Event &event);
  void updateOutput();
  void update(const sf::Event &event);
  void draw(sf::RenderWindow *win);

private:
  Engine &_engine;

  bool _active;
  sf::Sprite _bg, _inputArea;
  sf::Font _font;
  sf::Text _inputValue, _cursor;

  std::list<sf::Text *> _output;
  std::deque<std::string> _input;
  size_t _currentIndex, _outputIndex, _cursorIndex;
  unsigned int _fontSize, _lineCount;
};

#endif /* !CONSOLE_HH_ */
