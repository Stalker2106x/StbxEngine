#include "GUIElement.hh"

using namespace stb;

//
// GUIElement
//

GUIElement::GUIElement()
{
	_active = true;
}

GUIElement::GUIElement(const std::string &id) : GUIElement()
{
	_id = id;
}

void GUIElement::toggle()
{
	_active = (_active ? false : true);
}

const std::string &GUIElement::getId()
{
	return (_id);
}

bool GUIElement::updateRT()
{
	return (true);
}

bool GUIElement::update(const sf::Event &e)
{
	if (!_active)
		return (false);
	return (true);
}
