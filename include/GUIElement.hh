#ifndef GUIELEMENT_HH_
#define GUIELEMENT_HH_

#include <SFML/Graphics.hpp>

namespace stb {
	/*!
	* @class GUIElement
	* @brief Abstract GUI Element superclass.
	*
	*        This class should not be instanciated. It is used as an abstract layer (Superclass) to store Panels or Indicators generically in GUI class.
	*/
	class GUIElement
	{
	public:
		GUIElement(const std::string &id);
		virtual ~GUIElement() {};

		virtual void toggle();
		const std::string &getId();

		virtual void setPosition(const sf::Vector2f &pos) = 0;
		virtual const sf::Vector2f &getPosition() = 0;

		virtual bool updateRT() { return (true); }; //Real time update, called more than one time between frames
		virtual bool update(const sf::Event &e) = 0;
		virtual void draw(sf::RenderWindow *win) = 0;
	protected:
		std::string _id;
		bool _active;
	};

}

#endif /* !GUIELEMENT_HH_ */