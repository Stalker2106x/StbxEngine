/*!
 * @file      Engine.hpp
 * @class     Engine
 * @brief     Main class for graphic conception
 *
 *            This the base class of the project.
 *            You must inherit from this class to start using the graphic engine. Start by implementing the update and draw routine,
 *            related to the behaviour you expect in your game.
 *            In your main function, simply instantiate your child Engine, then call the mainLoop method to start the program.
 */

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <SFML/Graphics.hpp>
#include "Console.hh"
#include "Keybinds.hh"
#include "GUI.hh"

namespace stb {

	enum CharType {
		alphanumeric,
		alphabetic,
		numeric
	};

	class Engine
	{
	public:
		Engine(int width = 800, int height = 600);
		~Engine();

		bool openWindow(int, int);

		sf::RenderWindow *getWindowHandle();
		sf::Vector2i &getWindowSize();
		int &getFramerate();
		sf::Vector2f &getMouse();
		sf::Clock &getGameTime();
		float &getElapsedSeconds();
		void handleArgs(int argc, char **argv);
		void videoParamSet(const std::string &, const int &);
		sf::Image capture();

		virtual void draw() = 0;
		bool updateLoop();
		virtual bool update(const sf::Event &) = 0;
		void updateFramerate();
		int mainLoop();

		static char getChar(sf::Event event, CharType type);
		static struct tm *getTime();
		static std::string getTimestamp();
		static sf::Vector2f getMousePosition();

		void quit();

		Keybinds *keybinds;
		Console *console;
		GUI *gui;

		static Engine *instance; //Public hook on engine instance

	protected:
		bool _quit, _fullscreen, _vsync;
		int _framerate, _frames;
		sf::Clock _gametime;
		float _elapsedSeconds;
		sf::Time _lastSecondTick;
		sf::Vector2i _winsize;
		sf::Vector2f _mouse;
		sf::RenderWindow *_win;
	};

}

#endif /* !ENGINE_HPP_ */
