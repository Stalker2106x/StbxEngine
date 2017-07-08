#include "HUD.hh"

//
// HUDPanel
//

HUDPanel::HUDPanel(const int &x, const int &y, const int &width, const int &height)
{
	_frame.setPosition(x, y);
	_frame.setSize(sf::Vector2f(width, height));
}

HUDPanel::HUDPanel(const sf::Vector2f &pos, const sf::Vector2f &size)
{
	_frame.setPosition(pos);
	_frame.setSize(size);
}

HUDPanel::~HUDPanel()
{

}

//
// HUD
//

HUD::HUD()
{

}

HUD::~HUD()
{

}

void HUD::toggle()
{
	_active = (_active ? false : true);
}

void HUD::addPanel()
{

}

void HUD::addIndicator()
{

}