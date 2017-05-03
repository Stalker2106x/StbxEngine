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
  _cursorIndex = 0;
  _input.push_back("");
  //FONT SET
  _inputValue.setFont(_font);
  _cursor.setFont(_font);
  //FONT SIZE
  _inputValue.setCharacterSize(_fontSize);
  _cursor.setCharacterSize(_fontSize);
  _cursor.setString(CURSOR);
}

Console::~Console()
{

}

void Console::initGraphics(const sf::Vector2i &winsize)
{
  sf::Texture bg, inputArea;

  bg.create(winsize.x, (_lineCount * _fontSize) + (_fontSize + 2));
  _bg.setTexture(bg);
  inputArea.create(winsize.x - 10, _fontSize + 2);
  _inputArea.setTexture(inputArea);
  _inputArea.setPosition(5, ((_lineCount + 1) * _fontSize) - (_inputArea.getLocalBounds().height + 4));
  _inputValue.setPosition(6, ((_lineCount + 1) * _fontSize) - ((_inputArea.getLocalBounds().height + 4)));
  _cursor.setPosition(5 + (_fontSize * _cursorIndex), _inputValue.getPosition().y);
  setColor(sf::Color(50, 65, 90), sf::Color(80, 100, 135));
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

void Console::setColor(sf::Color bg, sf::Color input)
{
  _bg.setColor(bg);
  _inputArea.setColor(input);
  _inputValue.setOutlineColor(sf::Color::White);
  _inputValue.setFillColor(sf::Color::Cyan);
  _cursor.setFillColor(sf::Color::White);
}

sf::Color Console::convertColorCode(std::string code)
{
  sf::Color color;

  if (code.find(COLOR_ESC) == 0)
    code = code.substr(strlen(COLOR_ESC), 9);
  color.r = atoi(code.substr(0, 3).c_str());
  color.g = atoi(code.substr(3, 3).c_str());
  color.b = atoi(code.substr(6, 3).c_str());
  return (sf::Color(color.r, color.g, color.b, 255));
}

void Console::output(std::string msg)
{ 
  if (_output.size() >= _lineCount)
    _outputIndex++;
  _output.push_back(new sf::Text());
  _output.back()->setFont(_font);
  _output.back()->setCharacterSize(_fontSize);
  if (msg.find(COLOR_ESC) == 0)
    {
      if (msg.length() < strlen(COLOR_ESC) + 9)
	{
	  _output.pop_back();
	  output("Syntax: Invalid color code");
	  return;
	}
      _output.back()->setFillColor(convertColorCode(msg));
      msg.erase(0, strlen(COLOR_ESC) + 9);
    }
  else
    _output.back()->setFillColor(sf::Color::White);
  _output.back()->setString(msg);
  updateOutput();
}

void Console::output(std::string color, std::string msg)
{
  output(color+msg);
}

void Console::insertLastOutput(const std::string &msg)
{
  _output.back()->setString(_output.back()->getString()+msg);
}

void Console::input()
{
  if (_input[_currentIndex].size() < 1)
    return;
  output(PROMPT+_input[_currentIndex]);
  Commands::parseCmd(*this, _engine, _input[_currentIndex]);
  if (_currentIndex == _input.size() - 1)
    _input.push_back("");
  else
    _input.insert(--_input.end(), _input[_currentIndex]);
  if (_output.size() >= _lineCount)
    {
      _outputIndex = (_output.size() - _lineCount) + 1;
      updateOutput();
    }
  _currentIndex = _input.size() - 1;
  _cursorIndex = 0;
}

void Console::updateInput(const sf::Event &event)
{
  std::string::iterator it;
  char c;

  c = Engine::getChar(event, alphanumeric);
  if (c != '\0')
    {
      if (_currentIndex != _input.size() - 1)
	{
	  _input.back() = _input[_currentIndex];
	  _currentIndex = _input.size() - 1;
	  _cursorIndex = _input.back().size();
	}
      it = _input.back().begin();
      std::advance(it, _cursorIndex);
      _input.back().insert(it, c);
      _cursorIndex++;
    }
  _inputValue.setString(_input[_currentIndex]);
  _cursor.setPosition(5 + ((_fontSize * 0.62f) * _cursorIndex), _inputValue.getPosition().y);
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

void Console::updateKeyboard(const sf::Event &event)
{
  if (event.key.code == sf::Keyboard::Return)
    input();
  else if (event.key.code == sf::Keyboard::BackSpace && _input[_currentIndex].length() > 0)
    {
      _input[_currentIndex].erase(_cursorIndex - 1, 1);
      _cursorIndex--;
    }
  else if (event.key.code == sf::Keyboard::Delete && _cursorIndex - _input[_currentIndex].size() > 0)
    _input[_currentIndex].erase(_cursorIndex, 1);
  else if (event.key.code == sf::Keyboard::Up && _currentIndex > 0)
    {
      _currentIndex--;
      _cursorIndex = _input[_currentIndex].size();
    }
  else if (event.key.code == sf::Keyboard::Down && _currentIndex < _input.size())
    {
      _currentIndex++;
      _cursorIndex = _input[_currentIndex].size();
    }
  else if (event.key.code == sf::Keyboard::Left && _cursorIndex > 0)
    _cursorIndex--;
  else if (event.key.code == sf::Keyboard::Right && _cursorIndex < _input[_currentIndex].size())
    _cursorIndex++;
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

void Console::update(const sf::Event &event)
{
  updateInput(event);
  if (event.key.code == sf::Keyboard::F1)
    toggle();
  else if (!_active || event.type != sf::Event::KeyPressed)
    return;
  else
    updateKeyboard(event);
}

void Console::draw(sf::RenderWindow *win)
{
  std::list<sf::Text *>::iterator begIter;

  win->draw(_bg);
  win->draw(_inputArea);
  win->draw(_inputValue);
  win->draw(_cursor);
  begIter = _output.begin();
  std::advance(begIter, _outputIndex);
  for (size_t i = 1; i < _lineCount && begIter != _output.end(); i++)
    {
      win->draw(*(*begIter));
      begIter++;
    }
}
