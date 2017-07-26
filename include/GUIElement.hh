/*!
* @file      GUIElement.hh
* @brief     Heads up display module
*
*            This classes set provide GUI elements to draw info over the renderer frame.
*            They should be managed through GUI module and its containers
*/
#ifndef GUIELEMENT_HH_
#define GUIELEMENT_HH_

#include <SFML/Graphics.hpp>
#include "Resolver.hh"

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
		~GUIElement() {};

		virtual void toggle();
		const std::string &getId();

		virtual void setPosition(const sf::Vector2f &pos) = 0;
		
		virtual bool updateRT(); //Real time update, called more than one time between frames
		virtual bool update(const sf::Event &e) = 0;
		virtual void draw(sf::RenderWindow *win) = 0;
	protected:
		std::string _id;
		bool _active;
	};

	/*!
	* @class GUIButton
	* @brief Abstract button superclass
	*
	*        This class should not be instanciated. It is used as an abstract layer to control behaviour of all button types
	*/
	typedef void(*onClickCallback)(void);

	class GUIButton : public GUIElement
	{
	public:
		GUIButton(const std::string &id, const sf::Event::EventType &triggerType);
		~GUIButton();

		bool isHovered() const;
		void setClickCallback(const onClickCallback &fptr);

		virtual bool onHover(const bool &triggered);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);
	private:
		bool _hover;
		sf::Event::EventType _triggerType;
		onClickCallback _clickCallback;
	};

	/*!
	* @class GUITextButton
	* @brief Clickable and hovereable simple text button
	*
	*        This represents a clickable text button entity on screen.
	*/
	class GUITextButton : public GUIButton
	{
	public:
		GUITextButton(const std::string &id, const std::string &label, const sf::Vector2f &pos, const sf::Event::EventType &triggerType = sf::Event::MouseButtonPressed);
		~GUITextButton();

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);
	private:
		sf::Text _label;
	};

	/*!
	* @class GUISpriteButton
	* @brief Clickable and hovereable textured button
	*
	*        This represents a clickable image button entity on screen.
	*/
	class GUISpriteButton : public GUIButton
	{
	public:
		GUISpriteButton(const std::string &id, const std::string &resource, const sf::Vector2f &pos, const sf::Event::EventType &triggerType = sf::Event::MouseButtonPressed);
		~GUISpriteButton();

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);
	private:
		sf::Sprite _sprite;
	};

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
	* @class GUIPanel
	* @brief Panel for GUI
	*
	*        This class is a panel to group indicators, or set custom actions bars, ...
	*/

	#define PN_CLOSE		      1  //Adds close button to header
	#define PN_LOCK		          2  //Adds poslock to header

	enum PanelButton {
		Close,
		Lock,
	};

	class GUIPanel : public GUIElement
	{
	public:
		GUIPanel();
		GUIPanel(const std::string &id, const sf::Vector2i &size, const sf::Color &color);
		GUIPanel(const std::string &id, const sf::Vector2i &size, const std::string &name);
		~GUIPanel();

		virtual void setPosition(const sf::Vector2f &pos);
		void setStyle(const char &style);

		void addElement(GUIElement *element);
		void updateElementsPosition();

		bool onButtonHover(const PanelButton &id, const bool &triggered);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);

	protected:
		char _style;
		bool _bhover[2];
		sf::Sprite _buttonBar[2];
		std::string _id;
		sf::Sprite _frame;
		std::vector<GUIElement *> _elements;
	};

	/*!
	* @class GUIDraggablePanel
	* @brief Draggable implementation of panel
	*
	*        This class is a Panel, that can be moved around in interface.
	*/

	class GUIDraggablePanel : public GUIPanel
	{
	public:
		GUIDraggablePanel(const std::string &id, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor);
		GUIDraggablePanel(const std::string &id, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource);
		~GUIDraggablePanel();
		void initialUpdate();

		void toggleLock();
		virtual void toggle();

		void setPosition(const sf::Vector2f &pos);
		void movePanel(const sf::Vector2f &newpos);

		bool onButtonHover(const PanelButton &id, const bool &triggered);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);

	private:
		bool _dragging, _lock;
		sf::Vector2f _dragOffset;
		sf::Sprite _header;
	};

}

#endif /* GUIELEMENT_HH_ */