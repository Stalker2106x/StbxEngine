#include <cstring>
#include <stdexcept>
#include "Engine.hpp"
#include "Console.hh"
#include "Resolver.hh"

using namespace stb;

Console::Console(Engine &e) : _engine(e)
{
	_font = *SFResolver<sf::Font>::resolve("console");
	_lineCount = 16;
	_fontSize = 18;
	_currentIndex = 0;
	_outputIndex = 0;
	_cursorIndex = 0;
	_input.push_back("");
	_logFile = "Data/log.txt";
	_logEnabled = false;
	e.keybinds->bind("f1", "toggleconsole");
}

Console::~Console()
{
	if (_log.is_open())
		_log.close();
}

void Console::initGraphics(const sf::Vector2i &winsize, tgui::Gui &gui)
{
	_console = tgui::Panel::create();
	_console->setPosition(0, 0);
	_console->setSize(400, 400);
	gui.add(_console);
	_console->add(tgui::Picture::create("./Data/texture/background.jpg"));
	_inputArea = tgui::EditBox::create();
	_inputArea->setSize("95%", _fontSize + 2);
	_inputArea->setPosition(5, ((_lineCount + 1) * _fontSize) - (_inputArea->getSize().y + 4));
	_console->add(_inputArea);
	setColor(sf::Color(50, 65, 90), sf::Color(80, 100, 135));
	toggle();
}

void Console::toggle()
{
	_active ? _active = false : _active = true;
	if (_active)
	{
		_inputArea->show();
		_inputArea->focus();
	}
	else
	{
		_inputArea->hide();
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
	//_bg.setFillColor(bg);
	//_inputArea->setColor(input);
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

sf::Color *Console::convertColorCode(std::string code, std::string esc)
{
	sf::Color *color = new sf::Color;

	if (code.length() < (9 + esc.length()))
		return (NULL);
	if (code.find(esc) == 0)
		code = code.substr(strlen(COLOR_ESC), 9);
	color->r = atoi(code.substr(0, 3).c_str());
	color->g = atoi(code.substr(3, 3).c_str());
	color->b = atoi(code.substr(6, 3).c_str());
	if (code.length() >= (12 + esc.length()))
		color->a = atoi(code.substr(9, 3).c_str());
	else
		color->a = 255;
	return (color);
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
		_output.back()->setFillColor(*convertColorCode(msg));
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
	output(color + msg);
}

void Console::insertLastOutput(const std::string &msg)
{
	sf::Text *text = new sf::Text(msg, _font, _fontSize);

	if ((_output.back()->getLocalBounds().width + text->getLocalBounds().width) > _engine.getWindowSize().x)
		_output.push_back(text);
	else
	{
		delete (text);
		_output.back()->setString(_output.back()->getString() + msg);
	}

}

void Console::input()
{
	if (_input[_currentIndex].size() < 1)
		return;
	output(PROMPT + _input[_currentIndex]);
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
}

void Console::update(const sf::Event &event)
{
	if (!_active)
		return;
	if (event.type == sf::Event::KeyPressed)
		updateKeyboard(event);
}

void Console::draw(sf::RenderWindow &win)
{
	std::list<sf::Text *>::iterator begIter;

	begIter = _output.begin();
	std::advance(begIter, _outputIndex);
	for (size_t i = 1; i < _lineCount && begIter != _output.end(); i++)
	{
		win.draw(*(*begIter));
		begIter++;
	}
}
