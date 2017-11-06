#include <cstring>
#include <stdexcept>
#include "Engine.hpp"
#include "Console.hh"

using namespace stb;

Console::Console(Engine &e) : _engine(e)
{
	_active = false;
	_lineCount = 16;
	_fontSize = 18;
	_currentIndex = 0;
	_outputIndex = 0;
	_cursorIndex = 0;
	_input.push_back("");
	_logFile = "Data/log.txt";
	_logEnabled = false;
	_cursor.setString(CURSOR);
	e.keybinds->bind("f1", "toggleconsole");
}

Console::~Console()
{
	if (_log.is_open())
	_log.close();
}

void Console::initGraphics(const sf::Vector2i &winsize)
{
	//FONT SET
	_font = *SFResolver<sf::Font>::resolve(Engine::instance->gui->defaults.font);
	_inputValue.setFont(_font);
	_cursor.setFont(_font);
	//FONT SIZE
	_inputValue.setCharacterSize(_fontSize);
	_cursor.setCharacterSize(_fontSize);
	_frame = new GUIPanel(NULL, sf::Vector2i(winsize.x, (_lineCount * _fontSize) + (_fontSize + 4)), sf::Color(50, 65, 90));
	_frame->setPosition(sf::Vector2f(0, -_frame->getSize().y));
	_inputArea.setSize(sf::Vector2f(static_cast<float>(winsize.x - 10), static_cast<float>(_fontSize + 2)));
	_inputArea.setPosition(5, _frame->getPosition().y + ((_lineCount + 1) * _fontSize) - (_inputArea.getLocalBounds().height + 4));
	_inputValue.setPosition(6, ((_lineCount + 1) * _fontSize) - ((_inputArea.getLocalBounds().height + 4)));
	_cursor.setPosition(static_cast<float>(5 + (_fontSize * _cursorIndex)), static_cast<float>(_inputValue.getPosition().y));
	setColor(sf::Color(50, 65, 90), sf::Color(80, 100, 135));
}

void Console::toggle()
{
	if (_active)
	{
		_targetPos = sf::Vector2f(0, -_frame->getSize().y);
	}
	else
	{
		_active = true;
		_targetPos = sf::Vector2f(0, 0);
	}
}

void Console::clear()
{
	_outputIndex = 0;
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
	_inputArea.setFillColor(input);
	_inputValue.setOutlineColor(sf::Color::White);
	_inputValue.setFillColor(sf::Color::Cyan);
	_cursor.setFillColor(sf::Color::White);
}

void Console::setCursor(char &c)
{
	_cursor.setString(c);
}

void Console::setLogEnabled(bool state)
{
	_logEnabled = state;
	if (_logEnabled)
	{
		if (!_log.is_open())
		{
			_log.open(_logFile, std::ofstream::out | std::ofstream::app);
		}
	}
	else
	{
		if (_log.is_open())
		{
			_log.close();
		}
	}
}

void Console::writeToLog(std::string &msg)
{
	if (!_log.is_open())
		_log.open(_logFile, std::ofstream::out | std::ofstream::app);
	if (_logTimestamp)
		_log << _engine.getTimestamp() << msg << "\n";
	else
		_log << msg << "\n";
	if (!_log.is_open())
		_log.close();
}

void Console::setLogFile(const std::string &file)
{
	if (_log.is_open())
		_log.close();
	_logFile = file;
}

void Console::setLogTimestamp(int toggle)
{
  if (toggle != -1)
    _logTimestamp = static_cast<bool>(toggle);
  else
    _logTimestamp = (_logTimestamp ? false : true);
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
	if (_logEnabled)
		writeToLog(msg);
	updateOutput();
}

void Console::output(std::string color, std::string msg)
{
	output(color+msg);
}

void Console::insertLastOutput(const std::string &msg)
{
	sf::Text *text = new sf::Text(msg, _font, _fontSize);

	if ((_output.back()->getLocalBounds().width+text->getLocalBounds().width) > _engine.getWindowSize().x)
		_output.push_back(text);
	else
    {
		delete (text);
		_output.back()->setString(_output.back()->getString()+msg);
    }

}

void Console::input()
{
	if (_input[_currentIndex].size() < 1)
		return;
	output(PROMPT+_input[_currentIndex]);
	Commands::parseCmd(_input[_currentIndex]);
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
	char c;

	c = Engine::getChar(event, alphanumeric);
	if (c == '\b')
	{
		if (_input[_currentIndex].length() > 0)
			_input[_currentIndex].erase((_cursorIndex--) - 1, 1);
	}
	else if (c == '\n')
		return;
	else if (c != '\0')
	{
		std::string::iterator it;

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
	updateInputValue();
}

void Console::updateInputValue()
{
	_inputValue.setString(_input[_currentIndex]);
	_cursor.setPosition(5 + ((_inputValue.getLocalBounds().width / _input[_currentIndex].length()) * _cursorIndex), _inputValue.getPosition().y);
}

void Console::updateOutput()
{
	std::list<sf::Text *>::iterator begIter = _output.begin();
	float posy = 0;

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
	else if (event.key.code == sf::Keyboard::Delete && _cursorIndex - _input[_currentIndex].size() > 0)
		_input[_currentIndex].erase(_cursorIndex, 1);
	else if (event.key.code == sf::Keyboard::Up && _currentIndex > 0)
		_cursorIndex = _input[--_currentIndex].size();
	else if (event.key.code == sf::Keyboard::Down && _currentIndex < _input.size() - 1)
		_cursorIndex = _input[++_currentIndex].size();
	else if (event.key.code == sf::Keyboard::Left && _cursorIndex > 0)
	    _cursorIndex--;
	else if (event.key.code == sf::Keyboard::Right && _cursorIndex < _input[_currentIndex].size())
		_cursorIndex++;
	else if (event.key.code == sf::Keyboard::PageUp && _outputIndex > 1)
		_outputIndex--;
	else if (event.key.code == sf::Keyboard::PageDown && _outputIndex + _lineCount <= _output.size())
		_outputIndex++;
	updateOutput();
	updateInputValue();
}

void Console::updateRT()
{
	if (_frame->getPosition().y != _targetPos.y)
	{
		static sf::Time t = Engine::instance->getGameTime().getElapsedTime(); //get current time
		bool trigg = ((Engine::instance->getGameTime().getElapsedTime() - t).asMilliseconds() > 4);

		if (_frame->getPosition().y < _targetPos.y && trigg)
		{
			_frame->setPosition(_frame->getPosition() + sf::Vector2f(0, 5));
			_inputArea.setPosition(_inputArea.getPosition() + sf::Vector2f(0, 5));
		}
		else if (_frame->getPosition().y > _targetPos.y && trigg)
		{
			_frame->setPosition(_frame->getPosition() - sf::Vector2f(0, 5));
			_inputArea.setPosition(_inputArea.getPosition() - sf::Vector2f(0, 5));
		}
		if (trigg)
			t = Engine::instance->getGameTime().getElapsedTime(); //reset
		if (_frame->getPosition().y == _targetPos.y && _targetPos.y < 0)
			_active = false;
	}
}

void Console::update(const sf::Event &event)
{
	if (!_active)
		return;
	if (event.type == sf::Event::KeyPressed)
		updateKeyboard(event);
	updateInput(event);
}

void Console::draw(sf::RenderWindow *win)
{
	static sf::Clock cursorDelay;
	static bool drawCursor = false;
	std::list<sf::Text *>::iterator begIter;

	_frame->draw(win);
	win->draw(_inputArea);
	win->draw(_inputValue);
	if (drawCursor)
		win->draw(_cursor);
	if (cursorDelay.getElapsedTime().asMilliseconds() >= CURSOR_DELAY)
    {
		drawCursor = (drawCursor ? false : true);
		cursorDelay.restart();
    }
	begIter = _output.begin();
	std::advance(begIter, _outputIndex);
	for (size_t i = 1; i < _lineCount && begIter != _output.end(); i++)
    {
		win->draw(*(*begIter));
		begIter++;
    }
}
