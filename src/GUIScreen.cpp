#include "GUIScreen.hh"
#include "Engine.hpp"

using namespace stb;

GUIScreen::GUIScreen(GUIElement *parent)
	: GUIPanel(parent, Engine::instance->getWindowSize())
{
	_type = Screen;
}

GUIScreen::~GUIScreen()
{

}

GUIScreen *GUIScreen::loadFromFile(const std::string &file, const std::string &screenId)
{
	pugi::xml_document doc;
	std::ifstream ifs(file);
	pugi::xml_parse_result xml;
	pugi::xml_node screen;
	GUIScreen *pScreen;

	if (!ifs)
	{
		Engine::instance->console->output(COLOR_ERROR, "Error: Menu: \"" + file + "\" XML resource not found");
		return (NULL);
	}
	if (!(xml = doc.load(ifs)))
	{
		Engine::instance->console->output(COLOR_ERROR, "Error: Menu: \"" + file + "\" resource XML parsing failed");
		return (NULL);
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
	pScreen = static_cast<GUIScreen *>(GUIXML::getGUIElementFromXML(screen));
	STBResolver<GUIScreen>::insert(pScreen->_id, pScreen);
	return (pScreen);
}