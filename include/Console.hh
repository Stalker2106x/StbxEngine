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

#define PROMPT			(">")
#define COLOR_ESC		("\\\\#")
#define COLOR_ERROR		("\\\\#240077077")
#define COLOR_SUCCESS	("\\\\#154205050")
#define COLOR_INFO		("\\\\#000191255")

	class Engine; //Forward

	class Console
	{
	public:
		Console(Engine &e);
		~Console();

		void initGraphics(tgui::Gui &gui);

		void toggle();
		void clear();

		bool isActive() const;
		void setColor(sf::Color bg, sf::Color input);
		void setLogEnabled(bool state);
		void writeToLog(const std::string &msg);
		void setLogFile(const std::string &file);
		void setLogTimestamp(int);

		static sf::Color *convertColorCode(std::string code, std::string esc = "\\\\#");

		void output(const std::string &msg);
		void input(const std::string &msg);

		void updateKeyboard(const sf::Event &event);
		void update(const sf::Event &event);
		void draw(sf::RenderWindow &win);

	private:
		Engine &_engine;

		bool _active, _logEnabled, _logTimestamp;
		tgui::Panel::Ptr _console;
		tgui::ListBox::Ptr _outputArea;
		tgui::EditBox::Ptr _inputArea;
		std::string _logFile;
		std::ofstream _log;
		std::deque<std::string> _input, _output;
	};

}

#endif /* !CONSOLE_HH_ */
