#include "HUD.hh"

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