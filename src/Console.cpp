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
	_logFile = "Data/log.txt";
	_logEnabled = false;
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
	_frame = new GUIPanel(NULL, sf::Vector2i(winsize.x, (_lineCount * _fontSize) + (_fontSize + 4)), sf::Color(50, 65, 90));
	_frame->setPosition(sf::Vector2f(0, -_frame->getSize().y));
	_edit = new GUIEdit(_frame, CURSOR, Engine::instance->gui->defaults.font);
	_edit->setWidth(winsize.x - 10);
	_edit->setPosition(sf::Vector2f(5, _frame->getPosition().y + ((_lineCount + 1) * _fontSize) - (_edit->getSize().y + 4)));
	_frame->addElement(_edit);
	setColor(sf::Color(50, 65, 90), sf::Color(80, 100, 135));
}

void Console::toggle()
{
	if (_active)
	{
		_targetPos = sf::Vector2f(0, -_frame->getSize().y);
		_edit->setFocus(false);
	}
	else
	{
		_active = true;
		_edit->setFocus(true);
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
	_edit->setColor(input);
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
	std::string input = _edit->getText();

	if (input.size() < 1)
		return;
	_edit->clear();
	output(PROMPT+input);
	Commands::parseCmd(input); //parse command
	_inputList.insert(_inputList.end(), input);
	if (_output.size() >= _lineCount)
    {
		_outputIndex = (_output.size() - _lineCount) + 1;
		updateOutput();
    }
	_currentIndex = _inputList.size();
}

void Console::updateEditValue()
{
	_edit->setText(_inputList[_currentIndex]);
	_edit->setCursorPos(_inputList[_currentIndex].size());
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
	else if (event.key.code == sf::Keyboard::Up && _currentIndex > 0)
	{
		_currentIndex--;
		updateEditValue();
	}
	else if (event.key.code == sf::Keyboard::Down && _currentIndex < _inputList.size() - 1)
	{
		_currentIndex++;
		updateEditValue();
	}
	else if (event.key.code == sf::Keyboard::PageUp && _outputIndex > 1)
		_outputIndex--;
	else if (event.key.code == sf::Keyboard::PageDown && _outputIndex + _lineCount <= _output.size())
		_outputIndex++;
	updateOutput();
}

void Console::updateRT()
{
	if (_frame->getPosition().y != _targetPos.y)
	{
		static sf::Time t = Engine::instance->getGameTime(); //get current time
		bool trigg = ((Engine::instance->getGameTime() - t).asMilliseconds() > 3);

		if (_frame->getPosition().y < _targetPos.y && trigg)
		{
			_frame->setPosition(_frame->getPosition() + sf::Vector2f(0, 5));
		}
		else if (_frame->getPosition().y > _targetPos.y && trigg)
		{
			_frame->setPosition(_frame->getPosition() - sf::Vector2f(0, 5));
		}
		if (trigg)
			t = Engine::instance->getGameTime(); //reset
		if (_frame->getPosition().y == _targetPos.y && _targetPos.y < 0)
			_active = false;
	}
}

void Console::update(const sf::Event &e)
{
	if (!_active)
		return;
	_frame->update(e);
	if (e.type == sf::Event::KeyPressed)
		updateKeyboard(e);
}

void Console::draw(sf::RenderWindow *win)
{
	std::list<sf::Text *>::iterator begIter;

	_frame->draw(win);
	_edit->draw(win);
	begIter = _output.begin();
	std::advance(begIter, _outputIndex);
	for (size_t i = 1; i < _lineCount && begIter != _output.end(); i++) //Draw output
    {
		win->draw(*(*begIter));
		begIter++;
    }
}
