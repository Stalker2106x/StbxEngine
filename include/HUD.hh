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
	HUDSIndicator() {};
	virtual ~HUDSIndicator() {};
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
	HUDIndicator(const std::string *label, const T &var)
	{
		_label = label;
		_hook = var;
	}

	~HUDIndicator();

private:
	sf::Text *_label;
	sf::Text _value;
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
	HUDPanel(const int &x, const int &y, const int &width, const int &height);
	HUDPanel(const sf::Vector2i &pos, const sf::Vector2i &size);
	~HUDPanel();

private:
	sf::Sprite _background;
};

/*!
* @class HUDDynamicPanel
* @brief Draggable implementation of panel
*
*        This class is a Panel, that can be moved around in interface.
*/
class HUDDynamicPanel : public HUDPanel
{
public:
	HUDDynamicPanel();
	~HUDDynamicPanel();

private:
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

	void toggle();
	void addPanel();
	void addIndicator();

private:
	bool _active;
	std::vector<HUDPanel *> _panels;
	std::vector<HUDSIndicator *> _indicators;
};

#endif /* !DRAWABLE_HH_ */