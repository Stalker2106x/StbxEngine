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
		virtual ~GUISIndicator();

		void setFontsize(int fontSize);
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
			_label = NULL;
			_value.setCharacterSize(12);
			_value.setString(std::to_string(_hookValue));
		}

		GUIIndicator(const std::string &label, T &var) : GUISIndicator(label), _hook(var)
		{
			_hookValue = _hook;
			_label = new sf::Text();
			_label->setString(label);
			_label->setFont(*Resolver<sf::Font>::resolve("glitch"));
			_label->setCharacterSize(12);
			_value.setCharacterSize(12);
			_value.setString(std::to_string(_hookValue));
		}

		virtual ~GUIIndicator()
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
	* @brief Input box element to insert characters
	*
	*        This class is an input box where user can type
	*/

	class GUIEdit : public GUIElement
	{
	public:
		GUIEdit();
		GUIEdit(const std::string &id);
		virtual ~GUIEdit();
		void initialUpdate();

		void setFont(const std::string &fontResource);
		void setPosition(const sf::Vector2f &pos);
		void setColor(sf::Color *inputColor, sf::Color *valueColor);
		void setFontsize(int fontsize);
		void setWidth(const float &length);
		const sf::Vector2f &getSize();
		const sf::Vector2f &getPosition();
		const std::string &getInput();

		bool onHover(bool triggered);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);

	private:
		bool _focus;
		std::string _input;
		sf::Text _value;
		sf::RectangleShape _container;
	};

	/*!
	* @class GUITextArea
	* @brief Frame for drawing paragraphs of text
	*
	*        This class represents a container for text paragraphs
	*/

	class GUITextArea : public GUIElement
	{
	public:
		GUITextArea();
		GUITextArea(const std::string &id);
		virtual ~GUITextArea();
		void initialUpdate();

		void setFont(const std::string &fontResource);
		void setPosition(const sf::Vector2f &pos);
		void setColor(sf::Color *inputColor, sf::Color *valueColor);
		void setFontsize(int fontsize);
		void setWidth(const float &length);
		const sf::Vector2f &getSize();
		const sf::Vector2f &getPosition();

		bool onHover(bool triggered);

		virtual void draw(sf::RenderWindow *win);

	private:
		sf::Text _value;
		sf::RectangleShape _container;
	};

	/*!
	* @class GUICheckbox
	* @brief Draggable implementation of panel
	*
	*        This class is a Panel, that can be moved around in interface.
	*/

	class GUICheckbox : public GUIElement
	{
	public:
		GUICheckbox();
		GUICheckbox(const std::string &id);
		virtual ~GUICheckbox();
		void initialUpdate();

		void setPosition(const sf::Vector2f &pos);
		void setColor(const sf::Color *containerColor, const sf::Color *fillColor);
		void setSize(int length);
		const sf::Vector2f &getSize();
		const sf::Vector2f &getPosition();

		bool onHover(bool triggered);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);

	private:
		bool _checked;
		sf::RectangleShape _container, _fill;
	};
}

#endif /* GUIENTITY_HH_ */