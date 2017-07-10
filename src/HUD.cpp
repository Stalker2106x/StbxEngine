#include "HUD.hh"

//
// HUDPanel
//

HUDPanel::HUDPanel(const sf::Vector2f &pos, const sf::Vector2f &size)
{
	_frame.setPosition(pos);
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

bool HUD::update(sf::Event &e)
{
	return (true);
}

void HUD::draw(sf::RenderWindow *win)
{

}