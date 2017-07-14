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

class HUD
{
public:
	HUD();
	~HUD();

	bool isActive();

	void toggle();

	void addPanel(const sf::Vector2f &pos, const sf::Vector2i &size, const sf::Color &color);
	void addPanel(const sf::Vector2f &pos, const sf::Vector2i &size, const std::string &resource);
	void addDraggablePanel(const sf::Vector2f &pos, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor);
	void addDraggablePanel(const sf::Vector2f &pos, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource);
	template <typename T>
	void addIndicator(const sf::Vector2f &pos, const int &fontSize, std::string *label, T &var)
	{
		_elements.push_back(new HUDIndicator<T>(label, var));
		_elements.back()->setPosition(pos);
		_elements.back()->setFontsize(fontSize);
	}

	void toggleHideElement(const int &id);

	bool update(sf::Event &e);
	void draw(sf::RenderWindow *win);

private:
	bool _active;
	std::vector<HUDElement *> _elements;
};

#endif /* !DRAWABLE_HH_ */