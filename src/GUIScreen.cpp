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

void GUIScreen::copy(GUIScreen *screen, bool destroy)
{
	_active = screen->_active;
	_id = screen->_id;
	_elements = screen->_elements;
	_frame = screen->_frame;
	if (destroy)
		delete (screen);
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
	copy(static_cast<GUIScreen *>(GUIXML::getGUIElementFromXML(screen))); //Copy loaded screen to this
	STBResolver<GUIScreen>::insert(_id, this);
	return (true);
}