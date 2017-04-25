#include "Console.hh"
#include "Engine.hh"

Console::Console(const sf::Vector2i &winsize, Engine &e) : _engine(e)
{
  _active = false;

  if (!_font.loadFromFile("Data/font/console.ttf"))
    throw std::runtime_error("Resource not found");
  _lineCount = 16;
  _fontSize = 25;
  _currentIndex = 0;

  initGraphics(winsize);
  
  _input.push_back("");
}

Console::~Console()
{

}

void Console::initGraphics(const sf::Vector2i &winsize)
{
  sf::Texture bg, inputArea;

  _inputValue.setFont(_font);
  _inputValue.setCharacterSize(_fontSize);
  _inputValue.setColor(sf::Color::White);
  bg.create(winsize.x, (_lineCount * _fontSize));
  _bg.setTexture(bg);
  _bg.setColor(sf::Color(48,48,48));
  inputArea.create(winsize.x - 10, _fontSize + 2);
  _inputArea.setTexture(inputArea);
  _inputArea.setColor(sf::Color(128,128,128));
  _inputArea.setPosition(5, (_lineCount * _fontSize) - (_inputArea.getLocalBounds().height + 4));
  _inputValue.setPosition(6, (_lineCount * _fontSize) - ((_inputArea.getLocalBounds().height + 4)));
}

void Console::toggle()
{
  _active ? _active = false : _active = true;
}

void Console::clear()
{
  _output.clear();
}

bool Console::isActive() const
{
  return (_active);
}

void Console::output(const std::string &msg)
{
  if (_output.size() == (_lineCount - 2))
    _output.pop_front();
  _output.push_back(new sf::Text());
  _output.back()->setFont(_font);
  _output.back()->setCharacterSize(_fontSize);
  _output.back()->setColor(sf::Color::White);
  _output.back()->setString(msg);
  updateOutput();
}

void Console::input()
{
  output(">"+_input.back());
  Commands::parseCmd(*this, _engine, _input.back());
  _input.push_back("");
  _currentIndex++;
}

void Console::updateInput(const sf::Event &event)
{
  char c;

  c = Engine::getChar(event, alphanumeric);
  if (c != '\0')
    {
      if (c == '\b' && _input.back().length() > 0)
	_input.back().pop_back();
      else
	_input.back() += c;
    }
  _inputValue.setString(_input[_currentIndex]);
}

void Console::updateOutput()
{
  std::list<sf::Text *>::iterator iter;
  unsigned int posy = 0;
  
  for (iter = _output.begin(); iter != _output.end(); iter++)
    {
      (*iter)->setPosition(5, posy);
      posy += _fontSize;
    }
}

void Console::update(const sf::Event &event)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
    toggle();
  else if (_input.back().size() > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    input();
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && _currentIndex > 0)
    _currentIndex--;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && _currentIndex < _input.size())
    _currentIndex++;
  else
    updateInput(event);
}

void Console::draw(sf::RenderWindow *win)
{
  std::list<sf::Text *>::iterator iter;
  
  win->draw(_bg);
  win->draw(_inputArea);
  win->draw(_inputValue);
  for (iter = _output.begin(); iter != _output.end(); iter++)
    win->draw(*(*iter));
}
