/*!
* @file      GUIEntity.hh
* @brief     Implements standard GUI Entities
*
*            This classes set provide GUI elements to draw info over the renderer frame.
*            They should be managed through GUI module and its containers
*/
#ifndef GUIADVANCEDENTITY_HH_
#define GUIADVANCEDENTITY_HH_

#include <SFML/Graphics.hpp>
#include "GUIButton.hh"
#include "Resolver.hh"

namespace stb {

	class GUIScrollbar : GUIElement
	{
	public:
		GUIScrollbar(GUIElement *parent);
		~GUIScrollbar();

		virtual void initialUpdate();

		virtual void setPosition(const sf::Vector2f &pos);
		virtual const sf::Vector2f getSize();
		virtual const sf::Vector2f getPosition();

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *);
	private:
		sf::RectangleShape _container, _slider;
		GUISpriteButton<GUIButton> *_upBtn, *_dnBtn;
	};

}

#endif /* !GUIADVANCEDENTITY_HH_ */