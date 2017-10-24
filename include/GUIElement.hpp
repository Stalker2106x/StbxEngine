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
#include <string>

namespace stb {

	enum GUIElementType {
		Pair,
		Button,
		ButtonBar,
		Checkbox,
		Edit,
		Panel,
		DraggablePanel,
		Menu,
		Screen,
		SIndicator,
		Text,
		TextArea,
		//tmp
		MenuItem,
		Link,
		Setting,
		DynamicSetting,
		Slider
	};

	class GUIElement
	{
	public:
		GUIElement(const std::string &id, GUIElementType type) : _id(id), _type(type), _active(true) { }
		virtual ~GUIElement() {};

		virtual void initialUpdate() = 0;

		const std::string &getId() { return (_id); };
		const GUIElementType &getType() { return (_type); };
		virtual const sf::Vector2f &getPosition() = 0;

		bool isActive() { return (_active); };

		void setId(const std::string &id) {	_id = id; };
		virtual void setX(float x) { setPosition(sf::Vector2f(x, getPosition().y)); };
		virtual void setY(float y) { setPosition(sf::Vector2f(getPosition().x, y)); };
		virtual void setPosition(const sf::Vector2f &pos) = 0;

		virtual void toggle() { _active = (_active ? false : true); };

		virtual bool updateRT() { return (true); }; //Real time update, called more than one time between frames
		virtual bool update(const sf::Event &e) = 0;
		virtual void draw(sf::RenderWindow *win) = 0;
	protected:
		GUIElementType _type;
		std::string _id;
		bool _active;
	};

}

#endif /* !GUIELEMENT_HPP_ */