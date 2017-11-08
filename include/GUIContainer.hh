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
		GUIElementPair(std::shared_ptr<GUIElement> parent, std::shared_ptr<GUIElement> first = NULL, std::shared_ptr<GUIElement> second = NULL);
		~GUIElementPair();

		virtual void initialUpdate();

		virtual const sf::Vector2f getPosition();
		virtual const sf::Vector2f getSize();

		void setFirst(std::shared_ptr<GUIElement> element);
		void setSecond(std::shared_ptr<GUIElement> element);
		void setSpacing(int spacing);
		virtual void setPosition(const sf::Vector2f &pos);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *);

	protected:
		int _spacing;
		std::shared_ptr<GUIElement> _first;
		std::shared_ptr<GUIElement> _second;
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
		GUIElementGrid(std::shared_ptr<GUIElement> parent, const sf::Vector2i &size);
		~GUIElementGrid();

		virtual void initialUpdate();

		virtual const sf::Vector2f getPosition();
		virtual const sf::Vector2f getSize();

		void pushElement(std::shared_ptr<GUIElement> element);
		void setSpacing(int spacing);
		virtual void setPosition(const sf::Vector2f &pos);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *);

	protected:
		int _spacing;
		sf::Vector2i _size;
		std::vector<std::shared_ptr<GUIElement>> _elements;
	};

}

#endif /* !GUICONTAINER_HH_ */