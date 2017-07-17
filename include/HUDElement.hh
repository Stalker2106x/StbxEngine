/*!
* @file      HUDElement.hh
* @brief     Heads up display module
*
*            This classes set provide GUI elements to draw info over the renderer frame.
*            They should be managed through HUD module and its containers
*/
#ifndef HUDELEMENT_HH_
#define HUDELEMENT_HH_

#include <SFML/Graphics.hpp>
#include "Resolver.hh"


/*!
* @class HUDElement
* @brief Abstract HUD Element superclass.
*
*        This class should not be instanciated. It is used as an abstract layer (Superclass) to store Panels or Indicators generically in HUD class.
*/
class HUDElement
{
public:
	HUDElement(const std::string &id);
	~HUDElement() {};

	virtual void toggle();
	const std::string &getId();

	virtual void setPosition(const sf::Vector2f &pos) = 0;

	virtual bool update(const sf::Event &e) = 0;
	virtual void draw(sf::RenderWindow *win) = 0;
protected:
	std::string _id;
	bool _active;
};

/*!
* @class HUDSIndicator
* @brief Abstract HUD Indicator Superclass
*
*        This class should not be instanciated. It is used as an abstract layer (Superclass) to store Panels and Indicators generically in Panels or HUD class.
*/
class HUDSIndicator : public HUDElement
{
public:
	HUDSIndicator(const std::string &label);
	~HUDSIndicator();

	void setFontsize(const int &fontSize);
	void setPosition(const sf::Vector2f &pos);
	bool update(const sf::Event &e);
	void draw(sf::RenderWindow *win);

protected:
	sf::Text *_label, _value;
};

/*!
* @class HUDIndicator
* @brief Templated class to track a variable value on screen
*
*        This class requires a reference to templated type at construction, and draw its always updated value on screen
*/
template <typename T>
class HUDIndicator : public HUDSIndicator
{

public:
	HUDIndicator(T &var) : HUDSIndicator(""), _hook(var)
	{
		_label = NULL;
	}

	HUDIndicator(const std::string &label, T &var) : HUDSIndicator(label), _hook(var)
	{
		_label = new sf::Text();
		_label->setString(label);
		_label->setFont(*Resolver<sf::Font>::resolve("glitch"));
	}

	~HUDIndicator()
	{
		delete (_label);
	}

private:
	T &_hook;
};

/*!
* @class HUDPanel
* @brief Panel for HUD
*
*        This class is a panel to group indicators, or set custom actions bars, ...
*/
class HUDPanel : public HUDElement
{
public:
	HUDPanel();
	HUDPanel(const std::string &id, const sf::Vector2i &size, const sf::Color &color);
	HUDPanel(const std::string &id, const sf::Vector2i &size, const std::string &name);
	~HUDPanel();
	
	virtual void setPosition(const sf::Vector2f &pos);

	void addElement(HUDElement *element);

	virtual bool update(const sf::Event &e);
	virtual void draw(sf::RenderWindow *win);

protected:
	std::string _id;
	sf::Sprite _frame;
	std::vector<HUDElement *> _elements;
};

/*!
* @class HUDDraggablePanel
* @brief Draggable implementation of panel
*
*        This class is a Panel, that can be moved around in interface.
*/

#define PN_CLOSE		      1  //Adds close button to header
#define PN_LOCK		          2  //Adds poslock to header

enum PanelButton {
	Close,
	Lock,
};

class HUDDraggablePanel : public HUDPanel
{
public:
	HUDDraggablePanel(const std::string &id, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor);
	HUDDraggablePanel(const std::string &id, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource);
	~HUDDraggablePanel();
	void initialUpdate();

	void toggleLock();
	virtual void toggle();

	void setPosition(const sf::Vector2f &pos);
	void setStyle(const char &style);
	void movePanel(const sf::Vector2f &newpos);

	bool onButtonHover(const PanelButton &id, const bool &triggered);

	virtual bool update(const sf::Event &e);
	virtual void draw(sf::RenderWindow *win);

private:
	char _style;
	bool _dragging, _lock;
	sf::Vector2f _dragOffset;
	sf::Sprite _header;
	bool _bhover[2];
	sf::Sprite _buttonBar[2];
};

#endif /* HUDELEMENT_HH_ */