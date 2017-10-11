#include "GUIScreen.hh"

using namespace stb;

GUIScreen::GUIScreen() : GUIElement(""),
	_container("NULL", Engine::instance->getWindowSize(), sf::Color::Transparent)
{
	_changeId = "";
}

GUIScreen::~GUIScreen()
{

}

void GUIScreen::setPosition(const sf::Vector2f &pos)
{
	_container.setPosition(pos);
}

void GUIScreen::setBackground(const std::string &resource)
{
	_container.setBackground(resource);
}

const sf::Vector2f &GUIScreen::getPosition()
{
	return (_container.getPosition());
}

void GUIScreen::reset()
{
	_container.clear();
}

bool GUIScreen::loadFromFile(const std::string &file, const std::string &screenId)
{
	pugi::xml_document doc;
	std::ifstream ifs(file);
	pugi::xml_parse_result xml;
	pugi::xml_node screen;

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
	_lastLocation = file;
	screen = doc.first_child();
	if (!screenId.empty()) //Getting desired screen of id screenId
	{
		while (screen.attribute("id").value() != screenId)
		{
			if (screen == doc.last_child())
				return (false);
			screen = screen.next_sibling();
		}
	}
	parseScreen(screen);
	for (pugi::xml_node element = screen.first_child(); element; element = element.next_sibling())
	{
		if (strcmp(element.name(),"menu") == 0)
			_container.addElement(GUIMenu::parseXML(this, element));
	} 
	return (true);
}

void GUIScreen::parseScreen(const pugi::xml_node &screen)
{
}

void GUIScreen::changeScreen(const std::string &id, const std::string &location)
{
	_changeLocation = location;
	_changeId = id;
}

bool GUIScreen::update(const sf::Event &e)
{
	if (!_changeId.empty())
	{
		reset();
		if (!_changeLocation.empty())
		{
			loadFromFile(_changeLocation, _changeId);
			_changeLocation.clear();
		}
		else
			loadFromFile(_lastLocation, _changeId);
		_changeId.clear();
	}
	_container.update(e);
	return (true);
}

void GUIScreen::draw(sf::RenderWindow *win)
{
	_container.draw(win);
}