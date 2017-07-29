/*!
* @file      GUIElement.hh
* @brief     Heads up display module
*
*            This classes set provide GUI elements to draw info over the renderer frame.
*            They should be managed through GUI module and its containers
*/
#ifndef GUIENTITY_HH_
#define GUIENTITY_HH_

#include <SFML/Graphics.hpp>
#include "GUIButton.hh"
#include "Resolver.hh"

namespace stb {

	/*!
	* @class GUISIndicator
	* @brief Abstract GUI Indicator Superclass
	*
	*        This class should not be instanciated. It is used as an abstract layer (Superclass) to store Panels and Indicators generically in Panels or GUI class.
	*/
	class GUISIndicator : public GUIElement
	{
	public:
		GUISIndicator(const std::string &label);
		~GUISIndicator();

		void setFontsize(const int &fontSize);
		void setPosition(const sf::Vector2f &pos);
		bool update(const sf::Event &e);
		void draw(sf::RenderWindow *win);

	protected:
		sf::Text *_label, _value;
	};

	/*!
	* @class GUIIndicator
	* @brief Templated class to track a variable value on screen
	*
	*        This class requires a reference to templated type at construction, and draw its always updated value on screen
	*/
	template <typename T>
	class GUIIndicator : public GUISIndicator
	{

	public:
		GUIIndicator(T &var) : GUISIndicator(""), _hook(var)
		{
			_hookValue = _hook;
			_value.setString(std::to_string(_hookValue));
			_label = NULL;
		}

		GUIIndicator(const std::string &label, T &var) : GUISIndicator(label), _hook(var)
		{
			_label = new sf::Text();
			_label->setString(label);
			_label->setFont(*Resolver<sf::Font>::resolve("glitch"));
		}

		~GUIIndicator()
		{
			delete (_label);
		}

		virtual bool updateRT() override
		{
			if (_hookValue != _hook)
			{
				_hookValue = _hook;
				_value.setString(std::to_string(_hookValue));
			}
			return (true);
		}

		virtual bool update(const sf::Event &e)
		{
			if (!GUISIndicator::update(e))
				return (false);
			return (true);
		}

	private:
		T _hookValue;
		T &_hook;
	};

	/*!
	* @class GUIEdit
	* @brief Draggable implementation of panel
	*
	*        This class is a Panel, that can be moved around in interface.
	*/

	class GUIEdit : public GUIElement
	{
	public:
		GUIEdit();
		GUIEdit(const std::string &id);
		~GUIEdit();
		void initialUpdate();

		void setFont(const std::string &fontResource);
		void setPosition(const sf::Vector2f &pos);
		void setColor(sf::Color *inputColor, sf::Color *valueColor);
		void setFontsize(const int &fontsize);
		void setWidth(const int &length);
		const sf::Vector2f &getSize();
		const sf::Vector2f &getPosition();
		const std::string &getInput();

		bool onHover(const bool &triggered);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);

	private:
		bool _focus;
		std::string _input;
		sf::Text _value;
		sf::RectangleShape _container;
	};
}

#endif /* GUIENTITY_HH_ */