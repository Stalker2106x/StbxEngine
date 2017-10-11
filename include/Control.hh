/*!
 * @file      Control.hh
 * @class     stb::Control
 * @brief     Key, or Mouse event
 *
 *            This class is a layer above SFML Controls, allowing usage of mouse and keyboard events generically,
 *	          thanks to the implementation of generic callbacks at top level.
 */

#ifndef CONTROL_HH_
#define CONTROL_HH_

#include <SFML/Graphics.hpp>

namespace stb {

	enum ControlType {
		Null,
		Key,
		MButton,
		MWheel
	};

	enum WheelMove {
		Up = -1,
		Down = 1
	};

	class Control
	{
		friend bool operator==(const Control &a, const Control &b);
		friend bool operator<(const Control &a, const Control &b);
	public:

		Control(std::string);
		Control(std::string, const sf::Keyboard::Key key);
		Control(std::string, const sf::Mouse::Button btn);
		Control(std::string, const int whl);
		Control(const Control &c);
		~Control();

		std::string getBindStr() const;
		bool isTriggered(const sf::Event &e);
		bool isReleased(const sf::Event &e);


		static std::map<std::string, Control> keys;

	private:
		std::string _bindstr;
		ControlType _type;
		sf::Keyboard::Key *_key;
		sf::Mouse::Button *_mbutton;
		int *_mwheel;
	};

}

#endif /* !CONTROL_HH_ */
