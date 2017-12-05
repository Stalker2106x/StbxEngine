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

#include <list>
#include <deque>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Commands.hh"

namespace stb {

#define PROMPT		(">")
#define CURSOR		("_")
#define COLOR_ESC	("\\\\#")
#define COLOR_ERROR	("\\\\#240077077")
#define COLOR_SUCCESS	("\\\\#154205050")
#define COLOR_INFO	("\\\\#000191255")
#define CURSOR_DELAY	(500)

	class Console
	{
	public:
		Console(Engine &e);
		~Console();

		void initGraphics(const sf::Vector2i &winsize, tgui::Gui &gui);

		void toggle();
		void clear();

		bool isActive() const;
		void setLineCount(const unsigned int &count);
		void setColor(sf::Color bg, sf::Color input);
		void setCursor(char &c);
		void setLogEnabled(bool state);
		void writeToLog(std::string &msg);
		void setLogFile(const std::string &file);
		void setLogTimestamp(int);

		static sf::Color *convertColorCode(std::string code, std::string esc = "\\\\#");

		void output(std::string msg);
		void output(std::string color, std::string msg);
		void insertLastOutput(const std::string &msg);
		void input();

		void updateInput(const sf::Event &event);
		void updateInputValue();
		void updateOutput();
		void updateKeyboard(const sf::Event &event);
		void update(const sf::Event &event);
		void draw(sf::RenderWindow &win);

	private:
		Engine &_engine;

		bool _active, _logEnabled, _logTimestamp;
		sf::RectangleShape _bg;
		tgui::EditBox::Ptr _inputArea;
		sf::Font _font;
		sf::Text _inputValue, _cursor;
		std::string _logFile;
		std::ofstream _log;

		std::list<sf::Text *> _output;
		std::deque<std::string> _input;
		size_t _currentIndex, _outputIndex, _cursorIndex;
		unsigned int _fontSize, _lineCount;
	};

}

#endif /* !CONSOLE_HH_ */
