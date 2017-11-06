/*!
* @file      GUIContainer.hh
* @brief     Contains definition for GUIElement aggregators
*
*/

#ifndef GUICONTAINER_HH_
#define GUICONTAINER_HH_

#include <SFML/Graphics.hpp>
#include "GUIElement.hpp"

namespace stb {

	/*
	* @class	GUIElementPair
	* @brief    GUIElement Pairing class to associate two GUIElements together
	*
	*           This class provide an implementation of "pair" of elements, for example to attach
	*           a control with its label.
	*/
	class GUIElementPair : public GUIElement
	{
	public:
		GUIElementPair(GUIElement *parent, GUIElement *first = NULL, GUIElement *second = NULL);
		~GUIElementPair();

		virtual void initialUpdate();

		virtual const sf::Vector2f getPosition();
		virtual const sf::Vector2f getSize();

		void setFirst(GUIElement *element);
		void setSecond(GUIElement *element);
		void setSpacing(int spacing);
		virtual void setPosition(const sf::Vector2f &pos);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *);

	protected:
		int _spacing;
		GUIElement *_first;
		GUIElement *_second;
	};

	/*
	* @class	GUIElementGrid
	* @brief    GUIElement Pairing class to associate two GUIElements together
	*
	*           This container is a grid, arranging elements within a defined number of rows and columns
	*/
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

#endif /* !GUICONTAINER_HH_ */