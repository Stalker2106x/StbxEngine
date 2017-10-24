/*!
 * @file      GUIElementPair.hh
 * @brief     GUIElement Pairing class to associate two GUIElements together
 *
 *            This class provide an implementation of "pair" of elements, for example to attach
 *            a control with its label.
 */

#ifndef GUIELEMENTPAIR_HH_
#define GUIELEMENTPAIR_HH_

#include <SFML/Graphics.hpp>
#include "GUIElement.hpp"

namespace stb {

	class GUIElementPair : public GUIElement
	{
	public:
		GUIElementPair(GUIElement *first, GUIElement *second);
		~GUIElementPair();

		virtual void initialUpdate();

		virtual const sf::Vector2f &getPosition();
		virtual void setPosition(const sf::Vector2f &pos);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *);

	protected:
		GUIElement *_first;
		GUIElement *_second;
	};

}

#endif /* !GUIELEMENTPAIR_HH_ */