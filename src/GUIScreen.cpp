#include "GUIScreen.hh"
#include "Engine.hpp"

using namespace stb;

GUIScreen::GUIScreen(std::shared_ptr<GUIElement> parent)
	: GUIPanel(parent, Engine::instance->getWindowSize())
{
	_type = Screen;
}

GUIScreen::~GUIScreen()
{

}

std::shared_ptr<GUIScreen> GUIScreen::loadFromFile(const std::string &file, const std::string &screenId)
{
	pugi::xml_document doc;
	std::ifstream ifs(file);
	pugi::xml_parse_result xml;
	pugi::xml_node screen;
	std::shared_ptr<GUIScreen> pScreen;

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
		while (screen.attribute(L"id").value() != pugi::as_wide(screenId))
		{
			if (screen == doc.last_child())
				return (false);
			screen = screen.next_sibling();
		}
	}
	pScreen = std::dynamic_pointer_cast<GUIScreen>(GUIXML::getGUIElementFromXML(screen));
	STBResolver<GUIScreen>::insert(pScreen->_id, pScreen);
	return (pScreen);
}