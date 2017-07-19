/*!
* @file      HUD.hh
* @class     HUD
* @brief     Heads up display module
*
*            This classes set provide usable GUI to draw info over the renderer frame.
*            It acts as a container for HUD Elements like static or dynamic Panels and Indicators to be added anywhere on screen.
*/
#ifndef HUD_HH_
#define HUD_HH_

#include <SFML/Graphics.hpp>
#include <vector>
#include "HUDElement.hh"

namespace stb {

	class HUD
	{
	public:
		HUD();
		~HUD();

		bool isActive();
		HUDElement *getElement(const std::string &id);

		void toggle();

		HUDPanel *addPanel(const std::string &id, const sf::Vector2i &size, const sf::Color &color);
		HUDPanel *addPanel(const std::string &id, const sf::Vector2i &size, const std::string &resource);
		HUDDraggablePanel *addDraggablePanel(const std::string &id, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor);
		HUDDraggablePanel *addDraggablePanel(const std::string &id, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource);
		template <typename T>
		void addIndicator(const sf::Vector2f &pos, const int &fontSize, std::string *label, T &var)
		{
			_elements.push_back(new HUDIndicator<T>(label, var));
			static_cast<HUDSIndicator *>(_elements.back())->setPosition(pos);
			static_cast<HUDSIndicator *>(_elements.back())->setFontsize(fontSize);
		}

		void toggleHideElement(const std::string &id);

		bool update(sf::Event &e);
		void draw(sf::RenderWindow *win);

	private:
		bool _active;
		std::vector<HUDElement *> _elements;
	};

}

#endif /* !DRAWABLE_HH_ */
