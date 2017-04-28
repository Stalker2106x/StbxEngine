#include "Console.hh"
#include "Engine.hh"

Console::Console(Engine &e) : _engine(e)
{
  _active = false;

  if (!_font.loadFromFile("Data/font/console.ttf"))
    throw std::runtime_error("Resource not found");
  _lineCount = 16;
  _fontSize = 18;
  _currentIndex = 0;
  _outputIndex = 0;
  _input.push_back("_");
}

Console::~Console()
{

}

void Console::initGraphics(const sf::Vector2i &winsize)
{
  sf::Texture bg, inputArea;

  _inputValue.setFont(_font);
  _inputValue.setCharacterSize(_fontSize);
  _inputValue.setOutlineColor(sf::Color::White);
  _inputValue.setFillColor(sf::Color::Cyan);
  bg.create(winsize.x, (_lineCount * _fontSize) + (_fontSize + 2));
  _bg.setTexture(bg);
  _bg.setColor(sf::Color(48,48,48));
  inputArea.create(winsize.x - 10, _fontSize + 2);
  _inputArea.setTexture(inputArea);
  _inputArea.setColor(sf::Color(128,128,128));
  _inputArea.setPosition(5, ((_lineCount + 1) * _fontSize) - (_inputArea.getLocalBounds().height + 4));
  _inputValue.setPosition(6, ((_lineCount + 1) * _fontSize) - ((_inputArea.getLocalBounds().height + 4)));
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

void Console::setLineCount(const unsigned int &count)
{
  _lineCount = count;
  updateOutput();
}

void Console::output(const std::string &msg)
{
  if (_output.size() >= _lineCount)
    _outputIndex++;
  _output.push_back(new sf::Text());
  _output.back()->setFont(_font);
  _output.back()->setCharacterSize(_fontSize);
  _output.back()->setFillColor(sf::Color::White);
  _output.back()->setString(msg);
  updateOutput();
}

void Console::insertLastOutput(const std::string &msg)
{
  _output.back()->setString(_output.back()->getString()+msg);
}

void Console::input()
{
  if (_input[_currentIndex].size() < 1)
    return;
  _input[_currentIndex].pop_back();
  output(">"+_input[_currentIndex]);
  Commands::parseCmd(*this, _engine, _input[_currentIndex]);
  if (_currentIndex == _input.size() - 1)
    _input.push_back("_");
  else
    _input.insert(--_input.end(), _input[_currentIndex]);
  if (_output.size() >= _lineCount)
    {
      _outputIndex = (_output.size() - _lineCount) + 1;
      updateOutput();
    }
  _currentIndex = _input.size() - 1;
}

void Console::updateInput(const sf::Event &event)
{
  char c;

  c = Engine::getChar(event, alphanumeric);
  if (c != '\0')
    {
      if (_currentIndex != _input.size() - 1)
	{
	  _input.back() = _input[_currentIndex]+"_";  
	  _currentIndex = _input.size() - 1;
	}
      _input.back().insert(--_input.back().end(), c);
    }
  _inputValue.setString(_input[_currentIndex]);
}

void Console::updateOutput()
{
  std::list<sf::Text *>::iterator begIter = _output.begin();
  unsigned int posy = 0;

  std::advance(begIter, _outputIndex);
  for (size_t i = 1; i < _lineCount && begIter != _output.end(); i++)
    {
      (*begIter)->setPosition(5, posy);
      posy += _fontSize;
      begIter++;
    }
}

void Console::update(const sf::Event &event)
{
  updateInput(event);
  if (event.type != sf::Event::KeyPressed)
    return;
  if (event.key.code == sf::Keyboard::F1)
    toggle();
  else if (event.key.code == sf::Keyboard::Return)
    input();
  else if (event.key.code == sf::Keyboard::BackSpace && _input[_currentIndex].length() > 0)
    _input[_currentIndex].pop_back();
  else if (event.key.code == sf::Keyboard::Up && _currentIndex > 0)
    _currentIndex--;
  else if (event.key.code == sf::Keyboard::Down && _currentIndex < _input.size())
    _currentIndex++;
  else if (event.key.code == sf::Keyboard::PageUp && _outputIndex > 0)
    {
      _outputIndex--;
      updateOutput();
    }
  else if (event.key.code == sf::Keyboard::PageDown && _outputIndex + _lineCount <= _output.size())
    {
      _outputIndex++;
      updateOutput();
    }
}

void Console::draw(sf::RenderWindow *win)
{
  std::list<sf::Text *>::iterator begIter = _output.begin();
  
  win->draw(_bg);
  win->draw(_inputArea);
  win->draw(_inputValue);
  std::advance(begIter, _outputIndex);
  for (size_t i = 1; i < _lineCount && begIter != _output.end(); i++)
    {
      win->draw(*(*begIter));
      begIter++;
    }
}
