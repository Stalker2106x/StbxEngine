/*!
 * @file      Engine.hpp
 * @class     stb::Engine
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

#ifdef STBXENGINE_CORE
#include "imgui.h"
#include "imgui-SFML.h"
#endif

namespace stb {

	enum CharType {
		alphanumeric,
		alphabetic,
		numeric
	};

	class Engine
	{
	public:
		Engine();
		~Engine();

		void init(int width = 800, int height = 600);
		bool openWindow(int, int);

		sf::RenderWindow &getWindowHandle();
		sf::Vector2i &getWindowSize();
		int &getFramerate();
		sf::Vector2f &getMouse();
		sf::Time getGameTime();
		float getElapsedSeconds();
		void handleArgs(int argc, char **argv);
		void videoParamSet(const std::string &, int);
		sf::Image capture();

		virtual bool update(const sf::Event &) = 0; //Overloaded by user
		virtual void draw(sf::RenderWindow &) = 0; //Overloaded by user

		bool updateLoop();
		void updateFramerate();
		int mainLoop();

		static char getChar(sf::Event event, CharType type);
		static struct tm *getTime();
		static std::string getTimestamp();
		static sf::Vector2f getMousePosition();

		void quit();

		Keybinds *keybinds;
		Console *console;

		static Engine *instance; //Public hook on engine instance

	protected:
		bool _quit, _fullscreen, _vsync;
		int _framerate, _frames;
		sf::Clock _gametime, _delta;
		sf::Time _lastSecondTick;
		sf::Vector2i _winsize;
		sf::Vector2f _mouse;
		sf::RenderWindow *_win;
	};

}

#endif /* !ENGINE_HPP_ */
