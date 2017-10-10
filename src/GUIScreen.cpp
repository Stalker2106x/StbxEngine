#include "GUIScreen.hh"

using namespace stb;

GUIScreen::GUIScreen()
 : _container("NULL", Engine::instance->getWindowSize(), sf::Color::Transparent)
{
}

GUIScreen::~GUIScreen()
{

}

void GUIScreen::reset()
{
	_container.clear();
}

bool GUIScreen::loadFromFile(const std::string &file)
{
	pugi::xml_document doc;
	std::ifstream ifs(file);
	pugi::xml_parse_result xml;

	if (!ifs)
	{
		Engine::instance->console->output(COLOR_ERROR, "Error: Menu: XML resource not found");
		return (false);
	}
	if (!(xml = doc.load(ifs)))
	{
		Engine::instance->console->output(COLOR_ERROR, "Error: Menu: Invalid XML resource");
		return (false);
	}
	for (pugi::xml_node element = doc.child("se").first_child(); element; element = element.next_sibling())
	{
		if (strcmp(element.name(),"menu") == 0)
			_container.addElement(GUIMenu::parseXML(this, element));
	} 
	return (true);
}

void GUIScreen::changeScreen(const std::string &location)
{
	_changeLocation = location;
}

bool GUIScreen::update(const sf::Event &e)
{
	if (!_changeLocation.empty())
	{
		reset();
		loadFromFile(_changeLocation);
		_changeLocation.clear();
	}
	_container.update(e);
	return (true);
}

void GUIScreen::draw(sf::RenderWindow *win)
{
	_container.draw(win);
}