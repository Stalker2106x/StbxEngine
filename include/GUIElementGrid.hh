/*!
* @file      GUIElementGrid.hh
* @brief     GUIElement Pairing class to associate two GUIElements together
*
*            This class provide an implementation of "pair" of elements, for example to attach
*            a control with its label.
*/

#ifndef GUIELEMENTGRID_HH_
#define GUIELEMENTGRID_HH_

#include <SFML/Graphics.hpp>
#include "GUIElement.hpp"

namespace stb {

	class GUIElementGrid : public GUIElement
	{
	public:
		GUIElementGrid(GUIElement *parent, const sf::Vector2i &size);
		~GUIElementGrid();

		virtual void initialUpdate();

		virtual const sf::Vector2f getPosition();
		virtual const sf::Vector2f getSize();

		void pushElement(GUIElement *element);
		void setSpacing(int spacing);
		virtual void setPosition(const sf::Vector2f &pos);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *);

	protected:
		int _spacing;
		sf::Vector2i _size;
		std::vector<GUIElement *> _elements;
	};

}

#endif /* !GUIELEMENTPAIR_HH_ */