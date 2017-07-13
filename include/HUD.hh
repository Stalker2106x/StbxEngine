/*!
* @file      HUD.hh
* @brief     Heads up display module
*
*            This classes set provide usable GUI to draw info over the renderer frame.
*            It allows Panels, Dynamic Panels and Indicators to be added anywhere on screen.
*/
#ifndef HUD_HH_
#define HUD_HH_

#include <SFML/Graphics.hpp>
#include <vector>

/*!
* @class HUDSIndicator
* @brief Abstract HUD Indicator Superclass
*
*        This class should not be instanciated. It is used as an abstract layer (Superclass) to store HUDIndicators generically in HUD class.
*/
class HUDSIndicator
{
public:
	HUDSIndicator(std::string *label);
	~HUDSIndicator();

	void toggle();
	void setFontsize(const int &fontSize);
	void setPosition(const sf::Vector2f &pos);
	bool update(const sf::Event &e);
	void draw(sf::RenderWindow *win);

protected:
	bool _active;
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
class HUDPanel
{
public:
	HUDPanel(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &color);
	HUDPanel(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &name);
	~HUDPanel();

	void toggle();

	virtual bool update(const sf::Event &e);
	virtual void draw(sf::RenderWindow *win);

protected:
	bool _active;
	sf::Sprite _frame;
};

/*!
* @class HUDDraggablePanel
* @brief Draggable implementation of panel
*
*        This class is a Panel, that can be moved around in interface.
*/
class HUDDraggablePanel : public HUDPanel
{
public:
	HUDDraggablePanel(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &headerColor, const sf::Color &frameColor);
	HUDDraggablePanel(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &headerResource, const std::string &frameResource);
	~HUDDraggablePanel();

	virtual bool update(const sf::Event &e);
	virtual void draw(sf::RenderWindow *win);

private:
	bool _dragging;
	sf::Sprite _header;
};

/*!
* @class HUD
* @brief Main HUD Component
*
*        This class is the HUD component itself. It is a container for HUD Elements like Panels and Indicators
*/
class HUD
{
public:
	HUD();
	~HUD();

	bool isActive();

	void toggle();

	void addPanel(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &color);
	void addPanel(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &resource);
	void addDraggablePanel(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &headerColor, const sf::Color &frameColor);
	void addDraggablePanel(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &headerResource, const std::string &frameResource);
	template <typename T>
	void addIndicator(const sf::Vector2f &pos, const int &fontSize, std::string *label, T &var)
	{
		_indicators.push_back(new HUDIndicator<T>(label, var));
		_indicators.back()->setPosition(pos);
		_indicators.back()->setFontsize(fontSize);

	}

	void toggleHidePanel(const int &id);
	void toggleHideIndicator(const int &id);

	bool update(sf::Event &e);
	void draw(sf::RenderWindow *win);

private:
	bool _active;
	std::vector<HUDPanel *> _panels;
	std::vector<HUDSIndicator *> _indicators;
};

#endif /* !DRAWABLE_HH_ */