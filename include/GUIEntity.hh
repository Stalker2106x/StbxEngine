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
#include "defs.h"

namespace stb {

	class GUI; //Forward declaration

	/*!
	* @class GUISIndicator
	* @brief Abstract GUI Indicator Superclass
	*
	*        This class should not be instanciated. It is used as an abstract layer (Superclass) to store Panels and Indicators generically in Panels or GUI class.
	*/
	class GUISIndicator : public GUIElement
	{
	public:
		GUISIndicator(std::shared_ptr<GUIElement> parent, const std::string &fontResource);
		virtual ~GUISIndicator();

		virtual void initialUpdate();

		void setFontSize(int fontSize);
		virtual void setPosition(const sf::Vector2f &pos);
		

		virtual const sf::Vector2f getPosition() const;
		virtual const sf::Vector2f getSize() const;
		
		bool update(const sf::Event &e);
		void draw(sf::RenderWindow &win);

	protected:
		sf::Text _value;
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
		GUIIndicator(std::shared_ptr<GUIElement> parent, T &var, const std::string &fontResource = GUIDefaults.font) : GUISIndicator(parent, fontResource), _hook(var)
		{
			_value.setCharacterSize(GUIDefaults.fontSize);
			_value.setString(std::to_string(_hook));
			_value.setFont(*SFResolver<sf::Font>::resolve(fontResource));
		}

		virtual ~GUIIndicator()
		{

		}

		virtual bool updateRT() override
		{
			static T prev;
			static sf::Time stamp = Engine::instance->getGameTime();

			if ((Engine::instance->getGameTime() - stamp).asMilliseconds() < 15)
				return (false);
			stamp = Engine::instance->getGameTime();
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
		GUIEdit(std::shared_ptr<GUIElement> parent, char cursor, const std::string &fontResource);
		virtual ~GUIEdit();

		virtual void initialUpdate();

		void setText(const std::string &text);
		void setFocus(bool focus);
		void setFont(const std::string &fontResource);
		void setPosition(const sf::Vector2f &pos);
		void setColor(sf::Color inputColor);
		void setTextColor(sf::Color textColor);
		void setCursorPos(int index);
		void setFontsize(int fontsize);
		void setWidth(const float &length);
		virtual const sf::Vector2f getSize() const;
		virtual const sf::Vector2f getPosition() const;
		int getCursorPos();
		const std::string &getText();

		void clear();

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow &win);

	private:
		bool _focus;
		int _index;
		std::string _input;
		sf::Text _value, _cursor;
		sf::RectangleShape _container;
	};

	/*!
	* @class GUISprite
	* @brief Standard image
	*
	*        This class is used for drawing images
	*/

	class GUISprite : public GUIElement
	{
	public:
		GUISprite(std::shared_ptr<GUIElement> parent, const std::string &resource = "");
		virtual ~GUISprite();

		virtual void initialUpdate();

		void setPosition(const sf::Vector2f &pos);
		void setTexture(const std::string &resource);
		void setColor(sf::Color color);
		virtual const sf::Vector2f getSize() const;
		virtual const sf::Vector2f getPosition() const;

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow &win);

	private:
		sf::Sprite _sprite;
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
		GUIText(std::shared_ptr<GUIElement> parent, const std::string &text = "", const std::string &fontResource = GUIDefaults.font);
		virtual ~GUIText();

		virtual void initialUpdate();

		void setText(std::string text);
		void setFont(const std::string &fontResource);
		void setPosition(const sf::Vector2f &pos);
		void setColor(sf::Color color);
		void setFontSize(int fontsize);
		virtual const sf::Vector2f getSize() const;
		virtual const sf::Vector2f getPosition() const;

		const std::wstring getIconCode(const std::string &id);
		wchar_t convertUnicode(const std::string &unicode);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow &win);

	private:
		sf::Text _text;
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
		GUICheckbox(std::shared_ptr<GUIElement> parent);
		virtual ~GUICheckbox();

		virtual void initialUpdate();

		virtual void setPosition(const sf::Vector2f &pos);
		void setColor(const sf::Color *containerColor, const sf::Color *fillColor);
		virtual const sf::Vector2f getSize() const;
		virtual const sf::Vector2f getPosition() const;

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow &win);

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
		GUISlider(std::shared_ptr<GUIElement> parent);
		~GUISlider();

		virtual void initialUpdate();

		virtual void setPosition(const sf::Vector2f &pos);
		void setRange(int min, int max);
		void setBarWidth(int width);
		void setBarColor(const sf::Color *barColor, const sf::Color *fillColor);

		int getValue();
		virtual const sf::Vector2f getSize() const;
		virtual const sf::Vector2f getPosition() const;

		void updateSlider(const sf::Event &e, bool forceupdate = false);
		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow &);

	private:
		bool _sliding;
		int _value;
		int _range[2];
		sf::RectangleShape _bar, _fill;
	};

	/*!
	* @class GUISeparator
	* @brief Blank placeholder element
	*
	*        This item can be used to space elements insidd containers
	*/
	class GUISeparator : public GUIElement
	{
	public:
		GUISeparator(std::shared_ptr<GUIElement> parent, const sf::Vector2f &size);
		~GUISeparator();

		virtual void initialUpdate();

		virtual void setPosition(const sf::Vector2f &pos);
		virtual const sf::Vector2f getSize() const;
		virtual const sf::Vector2f getPosition() const;

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow &);

	private:
		sf::FloatRect _size;
	};
}

#endif /* GUIENTITY_HH_ */