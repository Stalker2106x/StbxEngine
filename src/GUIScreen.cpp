#include "GUIScreen.hh"

using namespace stb;

GUIScreen::GUIScreen()
	: GUIPanel("NULL", Engine::instance->getWindowSize(), sf::Color::Transparent)
{
	_type = Screen;
}

GUIScreen::~GUIScreen()
{

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
		if (isScreenParam(element))
			continue;
		addElement(GUIXML::getGUIElementFromXML(element));
		//if (strcmp(element.name(),"menu") == 0)
		//	_container.addElement(GUIMenu::parseXML(this, element));
	} 
	STBResolver<GUIScreen>::insert(_id, this);
	return (true);
}

void GUIScreen::parseScreen(const pugi::xml_node &screen)
{
	_id = screen.attribute("id").as_string("");
}

bool GUIScreen::isScreenParam(const pugi::xml_node &param)
{
	if (strcmp(param.name(), "background") == 0)
	{
		setBackground(param.attribute("resource").as_string(""));
	}
	else
		return (false);
	return (true);
}