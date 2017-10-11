/*!
* @file  GUIElement.hh
* @class stb::GUIElement
* @brief Abstract GUI Element superclass.
*
*        This class should not be instanciated. It is used as an abstract layer (Superclass) to store Panels or Indicators generically in GUI class.
*/
#ifndef GUIELEMENT_HPP_
#define GUIELEMENT_HPP_

#include <SFML/Graphics.hpp>

namespace stb {

	class GUIElement
	{
	public:
		GUIElement(const std::string &id) : _id(id), _active(true) {}
		virtual ~GUIElement() {};

		virtual void toggle() { _active = (_active ? false : true); };

		const std::string &getId() { return (_id); }
		virtual const sf::Vector2f &getPosition() = 0;


		void setId(const std::string &id) {	_id = id; };
		virtual void setPosition(const sf::Vector2f &pos) = 0;

		virtual bool updateRT() { return (true); }; //Real time update, called more than one time between frames
		virtual bool update(const sf::Event &e) = 0;
		virtual void draw(sf::RenderWindow *win) = 0;
	protected:
		std::string _id;
		bool _active;
	};

}

#endif /* !GUIELEMENT_HPP_ */