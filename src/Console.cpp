#include <cstring>
#include <stdexcept>
#include "Engine.hpp"
#include "Console.hh"
#include "Resolver.hh"

using namespace stb;

Console::Console(Engine &e) : _engine(e)
{
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
	_console->setSize("100%", "33%");
	_console->getRenderer()->setBackgroundColor(tgui::Color(25, 39, 51));
	gui.add(_console);
	_inputArea = tgui::EditBox::create();
	_inputArea->setSize(winsize.x - 10, 22);
	_inputArea->setPosition(5, _console->getSize().y - _inputArea->getSize().y - 5);
	_inputArea->connect("ReturnKeyPressed", [&]() { input(_inputArea->getText()); });
	_console->add(_inputArea);
	_outputArea = tgui::ListBox::create();
	_outputArea->setSize(winsize.x - 10, _console->getSize().y - _inputArea->getSize().y - 15);
	_outputArea->setPosition(5, 5);
	_outputArea->connect("ItemSelected", [&]() { _outputArea->deselectItem(); });
	auto renderer = _outputArea->getRenderer();
	renderer->setBackgroundColor(tgui::Color(51, 65, 76));
	renderer->setBackgroundColorHover(tgui::Color(51, 65, 76));
	renderer->setTextColor(tgui::Color::White);
	_console->add(_outputArea);
	setColor(sf::Color(50, 65, 90), sf::Color(80, 100, 135));
	toggle();
}

void Console::toggle()
{
	_active ? _active = false : _active = true;
	if (_active)
	{
		_console->show();
		_inputArea->focus();
	}
	else
	{
		_console->hide();
	}
}

void Console::clear()
{
	_output.clear();
}

bool Console::isActive() const
{
	return (_active);
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

void Console::writeToLog(const std::string &msg)
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

void Console::output(const std::string &msg)
{
	_output.push_back(msg);
	_outputArea->addItem(msg);
	if (_logEnabled)
		writeToLog(msg);
}

void Console::input(const std::string &msg)
{
	_input.push_back(msg);
	_inputArea->setText("");
	Commands::parseCmd(_input.back());
}

void Console::updateKeyboard(const sf::Event &event)
{

}

void Console::update(const sf::Event &event)
{
	if (!_active)
		return;
}

void Console::draw(sf::RenderWindow &win)
{

}
