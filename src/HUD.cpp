#include "HUD.hh"

//
// HUDPanel
//

HUDPanel::HUDPanel(const int &x, const int &y, const int &width, const int &height)
{

}

HUDPanel::HUDPanel(const sf::Vector2i &pos, const sf::Vector2i &size)
{

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