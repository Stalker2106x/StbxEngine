/*!
* @file      GUIEntity.hh
* @brief     Implements standard GUI Entities
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
		GUISIndicator(const std::string &fontResource);
		virtual ~GUISIndicator();

		virtual void initialUpdate();

		void setFontsize(int fontSize);
		virtual void setPosition(const sf::Vector2f &pos);
		

		virtual const sf::Vector2f getPosition();
		virtual const sf::Vector2f getSize();
		
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
		GUIIndicator(T &var, const std::string &fontResource) : GUISIndicator(fontResource), _hook(var)
		{
			_label = NULL;
			_value.setCharacterSize(12);
			_value.setString(std::to_string(_hook));
			if (_label != NULL)
				_label->setFont(*SFResolver<sf::Font>::resolve(fontResource));
			_value.setFont(*SFResolver<sf::Font>::resolve(fontResource));
		}

		GUIIndicator(const std::string &label, const std::string &fontResource, T &var) : GUISIndicator(fontResource), _hook(var)
		{
			_label = new sf::Text();
			_label->setString(label);
			_label->setFont(*SFResolver<sf::Font>::resolve("glitch"));
			_label->setCharacterSize(12);
			_value.setCharacterSize(12);
			_value.setString(std::to_string(_hook));
			if (_label != NULL)
				_label->setFont(*SFResolver<sf::Font>::resolve(fontResource));
			_value.setFont(*SFResolver<sf::Font>::resolve(fontResource));
		}

		virtual ~GUIIndicator()
		{
			delete (_label);
		}

		virtual bool updateRT() override
		{
			static T prev;

			if (_hook != prev)
			{
				_value.setString(std::to_string(_hook));
			}
			prev = _hook;
			return (true);
		}

		virtual bool update(const sf::Event &e)
		{
			if (!GUISIndicator::update(e))
				return (false);
			return (true);
		}

	private:
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
		GUIEdit(const std::string &id = "");
		virtual ~GUIEdit();

		virtual void initialUpdate();

		void setFont(const std::string &fontResource);
		void setPosition(const sf::Vector2f &pos);
		void setColor(sf::Color inputColor);
		void setTextColor(sf::Color textColor);
		void setFontsize(int fontsize);
		void setWidth(const float &length);
		virtual const sf::Vector2f getSize();
		virtual const sf::Vector2f getPosition();
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
	* @class GUIText
	* @brief One line text area
	*
	*        This class is used for labels, titles, or drawing single lines of text
	*/

	class GUIText : public GUIElement
	{
	public:
		GUIText(const std::string &text = "");
		virtual ~GUIText();

		virtual void initialUpdate();

		void setFont(const std::string &fontResource);
		void setPosition(const sf::Vector2f &pos);
		void setColor(sf::Color color);
		void setFontsize(int fontsize);
		void setWidth(const float &length);
		virtual const sf::Vector2f getSize();
		virtual const sf::Vector2f getPosition();

		bool onHover(bool triggered);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);

	private:
		sf::Text _text;
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
		GUITextArea(const std::string &id = "");
		virtual ~GUITextArea();

		virtual void initialUpdate();

		void setFont(const std::string &fontResource);
		void setPosition(const sf::Vector2f &pos);
		void setColor(sf::Color *inputColor, sf::Color *valueColor);
		void setFontsize(int fontsize);
		void setWidth(const float &length);
		virtual const sf::Vector2f getSize();
		virtual const sf::Vector2f getPosition();

		bool onHover(bool triggered);

		virtual bool update(const sf::Event &e);
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
		GUICheckbox(const std::string &id = "");
		virtual ~GUICheckbox();

		virtual void initialUpdate();

		virtual void setPosition(const sf::Vector2f &pos);
		void setColor(const sf::Color *containerColor, const sf::Color *fillColor);
		void setSize(int length);
		virtual const sf::Vector2f getSize();
		virtual const sf::Vector2f getPosition();

		bool onHover(bool triggered);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);

	private:
		bool _checked;
		sf::RectangleShape _container, _fill;
	};

	/*!
	* @class GUISlider
	* @brief Slider Setting item, accept any value within defined range
	*
	*        This item is a setting bar moving horizontally to get values from user.
	*/
	class GUISlider : public GUIElement
	{
	public:
		GUISlider();
		~GUISlider();

		virtual void initialUpdate();

		virtual void setPosition(const sf::Vector2f &pos);
		void setRange(int min, int max);
		void setBarWidth(int width);
		void setBarColor(const sf::Color *barColor, const sf::Color *fillColor);

		int getValue();
		virtual const sf::Vector2f getSize();
		virtual const sf::Vector2f getPosition();

		void updateSlider(const sf::Event &e, bool forceupdate = false);
		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *);

	private:
		bool _sliding;
		int _value;
		int _range[2];
		sf::RectangleShape _bar, _fill;
	};

}

#endif /* GUIENTITY_HH_ */