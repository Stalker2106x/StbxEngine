/*!
 * @file      Console.hh
 * @class     stb::Console
 * @brief     Integrated toggleable developer console
 *
 *            This console is designed to provide to developer and advanced users a way to easily configure
 *            the engine the way they want, by allowing anything that the Engine support to be altered by a command
 *            including keybinds, and graphical properties.
 */

#ifndef CONSOLE_HH_
#define CONSOLE_HH_

#include <SFML/Graphics.hpp>
#include <list>
#include <deque>
#include <fstream>
#include "GUIPanel.hh"
#include "GUIEntity.hh"
#include "Commands.hh"
#include "utils.h"

namespace stb {

#define PROMPT		('>')
#define CURSOR		('_')
#define CURSOR_DELAY	(500)

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
		void setColor(sf::Color bg, sf::Color input);
		void setLogEnabled(bool state);
		void writeToLog(std::string &msg);
		void setLogFile(const std::string &file);
		void setLogTimestamp(int);

		void output(std::string msg);
		void output(std::string color, std::string msg);
		void insertLastOutput(const std::string &msg);
		void input();

		void updateEditValue();
		void updateOutput();
		void updateKeyboard(const sf::Event &event);

		void updateRT();
		void update(const sf::Event &event);
		void draw(sf::RenderWindow &win);

	private:
		Engine &_engine;

		bool _active, _logEnabled, _logTimestamp;
		std::shared_ptr<GUIPanel> _frame;
		std::shared_ptr<GUIEdit> _edit;
		sf::Font _font;
		std::string _logFile;
		std::ofstream _log;
		sf::Vector2f _targetPos;

		std::list<sf::Text *> _output;
		std::deque<std::string> _inputList;
		size_t _currentIndex, _outputIndex;
		unsigned int _fontSize, _lineCount;
	};

}

#endif /* !CONSOLE_HH_ */
