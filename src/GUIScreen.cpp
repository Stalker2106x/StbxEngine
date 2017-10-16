#include "GUIScreen.hh"

using namespace stb;

GUIScreen::GUIScreen() : GUIElement("", Screen),
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

void GUIScreen::addElement(GUIElement *element)
{
	_container.addElement(element);
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
		Engine::instance->console->output(COLOR_ERROR, "Error: Menu: \"" + file + "\" XML resource not found");
		return (false);
	}
	if (!(xml = doc.load(ifs)))
	{
		Engine::instance->console->output(COLOR_ERROR, "Error: Menu: \"" + file + "\" resource XML parsing failed");
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
		_container.addElement(GUIXML::getGUIElementFromXML(this, element));
		//if (strcmp(element.name(),"menu") == 0)
		//	_container.addElement(GUIMenu::parseXML(this, element));
	} 
	STBResolver<GUIScreen>::resources.emplace(_id, this);
	return (true);
}

void GUIScreen::parseScreen(const pugi::xml_node &screen)
{
}

bool GUIScreen::update(const sf::Event &e)
{
	return (_container.update(e));
}

void GUIScreen::draw(sf::RenderWindow *win)
{
	_container.draw(win);
}