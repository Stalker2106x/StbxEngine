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


/*!
* @class HUDElement
* @brief Abstract HUD Element superclass.
*
*        This class should not be instanciated. It is used as an abstract layer (Superclass) to store Panels or Indicators generically in HUD class.
*/
class HUDElement
{
public:
	HUDElement();
	~HUDElement() {};

	void toggle();

	virtual bool update(const sf::Event &e) = 0;
	virtual void draw(sf::RenderWindow *win) = 0;
protected:
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
	HUDSIndicator(std::string *label);
	~HUDSIndicator();

	void setFontsize(const int &fontSize);
	void setPosition(const sf::Vector2f &pos);
	bool update(const sf::Event &e);
	void draw(sf::RenderWindow *win);

protected:
	sf::Text *_label;
	sf::Text _value;
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
	HUDIndicator(const std::string *label, const T &var) : HUDSIndicator(label)
	{
		_hook = var;
	}

	~HUDIndicator()
	{
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
	HUDPanel(const sf::Vector2f &pos, const sf::Vector2i &size, const sf::Color &color);
	HUDPanel(const sf::Vector2f &pos, const sf::Vector2i &size, const std::string &name);
	~HUDPanel();
	
	void addElement(); //construct properly

	virtual bool update(const sf::Event &e);
	virtual void draw(sf::RenderWindow *win);

protected:
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
#define PN_RESIZE	          4  //Allows panel to be resized;

class HUDDraggablePanel : public HUDPanel
{
public:
	HUDDraggablePanel();
	HUDDraggablePanel(const sf::Vector2f &pos, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor);
	HUDDraggablePanel(const sf::Vector2f &pos, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource);
	~HUDDraggablePanel();

	void setStyle(const char &style);
	void movePanel(const sf::Vector2f &newpos);

	bool onButtonHover(const int &id, const bool &triggered);

	virtual bool update(const sf::Event &e);
	virtual void draw(sf::RenderWindow *win);

private:
	char _style;
	bool _dragging;
	sf::Vector2f _dragOffset;
	sf::Sprite _header;
	bool _bhover[2];
	sf::Sprite _buttonBar[2];
};

#endif /* HUDELEMENT_HH_ */