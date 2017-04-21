#include "Console.hh"
#include "Engine.hh"

Console::Console(const sf::Vector2i &winsize)
{
  _active = false;

  if (!_font.loadFromFile("Data/font/console.ttf"))
    throw std::runtime_error("Resource not found");
  _fontSize = 12;
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
  _inputValue.setPosition(6, winsize.x / 4 - _inputArea.getLocalBounds().height - 4);
  bg.create(winsize.x, winsize.y / 4);
  _bg.setTexture(bg);
  _bg.setColor(sf::Color(48,48,48));
  inputArea.create(winsize.x - 10, _fontSize + 2);
  _inputArea.setTexture(inputArea);
  _inputArea.setColor(sf::Color(128,128,128));
  _inputArea.setPosition(5, winsize.y / 4 - _inputArea.getLocalBounds().height - 5);
}

void Console::toggle()
{
  _active ? _active = false : _active = true;
}

bool Console::isActive()
{
  return (_active);
}

void Console::update(const sf::Event &event)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && _currentIndex > 0)
    _currentIndex--;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && _currentIndex < _input.size())
    _currentIndex++;
  else
    {
      char c;

      c = Engine::getChar(event, alphanumeric);
      if (c != '\0')
	_input.back() += c;
      if (c == '\b')
	_input.back().pop_back();
    }
  _inputValue.setString(_input[_currentIndex]);
  std::cout << _input[_currentIndex] << "\n";
}

void Console::draw(sf::RenderWindow *win)
{
  win->draw(_bg);
  win->draw(_inputArea);
  win->draw(_inputValue);
}
