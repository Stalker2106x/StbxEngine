/*!
* @file      GUI.hh
* @class     stb::GUI
* @brief     Heads up display module
*
*            This classes set provide usable GUI to draw info over the renderer frame.
*            It acts as a container for GUI Elements like static or dynamic Panels and Indicators to be added anywhere on screen.
*/
#ifndef GUI_HH_
#define GUI_HH_

#include <SFML/Graphics.hpp>
#include <deque>
#include <stack>
#include "GUIButton.hh"
#include "GUIEntity.hh"
#include "GUIPanel.hh"
#include "utils.h"

namespace stb {

	struct GUIDefaults
	{
		int fontSize;
		std::string font;
		std::string fontColor;
		int panelSpacing;
		int pairSpacing;
		int gridSpacing;
	};

	class GUI
	{
	public:
		GUI();
		~GUI();

		bool isActive();
		void resetDefaults();
		GUIElement *getElement(const std::string &id);
		bool removeElement(const std::string &id, bool del = false);
		bool removeElement(int index, bool del = false);
		void drop();
		void changeScreen(const std::string &resource, const std::string &location = "");

		void toggle();

		void addElement(GUIElement *element);

		template <typename T>
		void addIndicator(const sf::Vector2f &pos, int fontSize, std::string *label, T &var)
		{
			_elements.push_back(new GUIIndicator<T>(label, var));
			static_cast<GUISIndicator *>(_elements.back())->setPosition(pos);
			static_cast<GUISIndicator *>(_elements.back())->setFontsize(fontSize);
		}

		void toggleHideElement(const std::string &id);

		bool updateRT();
		bool update(const sf::Event &e);
		void draw(sf::RenderWindow *win);

		GUIDefaults defaults;

	private:
		bool _active;
		std::deque<GUIElement *> _elements;
		std::stack<std::pair<size_t, bool>> _drop;
	};

}

#endif /* !DRAWABLE_HH_ */
