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
#include <TGUI/TGUI.hpp>
#include "Console.hh"
#include "Keybinds.hh"
#include "Keybinds.hh"

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

		void init(int width = 800, int height = 600, const std::string &windowTitle = "StbxEngine Window");
		bool openWindow(int, int);

		sf::RenderWindow &getWindowHandle();
		static tgui::Layout &getWindowWidth();
		static tgui::Layout &getWindowHeight();
		int &getFramerate();
		sf::Vector2f &getMouse();
		sf::Time getGameTime();
		float getElapsedSeconds();
		void handleArgs(int argc, char **argv);
		void videoParamSet(const std::string &, int);
		sf::Image capture();

		void GUIAdd(const tgui::Widget::Ptr widget);
		void GUIAddTo(const tgui::Widget::Ptr widget, const tgui::Widget::Ptr parent);
		void GUIRemove(const tgui::Widget::Ptr widget);
		void GUIRemoveFrom(const tgui::Widget::Ptr widget, const tgui::Widget::Ptr parent);

		static char getChar(sf::Event event, CharType type);
		static struct tm *getTime();
		static std::string getTimestamp();
		static sf::Vector2f getMousePosition();

		template <typename T>
		static T *getInstance() { return (dynamic_cast<T *>(instance)); };

		int mainLoop();
		virtual void quit();

		Keybinds *keybinds;
		static Console *console;
		static tgui::Gui *gui;
		static Engine *instance; //Public hook on engine instance

	protected:
		void GUISafeProcess();
		void GUISafeRemove();		
		void GUISafeAdd();

		virtual bool update(const sf::Event &) = 0; //Overloaded by user
		virtual void draw(sf::RenderWindow &) = 0; //Overloaded by user

		bool updateLoop();
		void updateFramerate();

		bool _quit, _fullscreen, _vsync;
		int _framerate, _frames;
		std::queue<std::pair<tgui::Widget::Ptr, tgui::Widget::Ptr>> _widgetsStack, _widgetsDrop;
		std::string _windowTitle;
		sf::Clock _gametime;
		sf::Time _lastSecondTick;
		tgui::Layout _winWidth, _winHeight;
		sf::Vector2f _mouse;
		sf::RenderWindow *_win;
	};

}

#endif /* !ENGINE_HPP_ */
