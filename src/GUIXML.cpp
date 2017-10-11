#include "GUIXML.hh"

using namespace stb;

std::map<std::string, XMLParserFptr> GUIXMLElementParser = {
	{ "Button", &GUIXML::getGUIButtonFromXML },
	{ "ButtonBar", &GUIXML::getGUIButtonBarFromXML },
	{ "Checkbox", &GUIXML::getGUICheckboxFromXML },
	{ "Edit", &GUIXML::getGUIEditFromXML },
	{ "Panel", &GUIXML::getGUIPanelFromXML },
	{ "Screen", &GUIXML::getGUIScreenFromXML },
	{ "Indicator", &GUIXML::getGUIIndicatorFromXML },
	{ "Text", &GUIXML::getGUITextFromXML },
	{ "TextArea", &GUIXML::getGUITextAreaFromXML }
};

GUIElement *GUIXML::getGUIElementFromXML(const pugi::xml_node &node)
{
	if (!node.name())
		return (NULL);
	return (GUIXMLElementParser[node.name()](node));
}

GUIElement *GUIXML::getGUIButtonFromXML(const pugi::xml_node &node)
{
	return (NULL);
}

GUIElement *GUIXML::getGUIButtonBarFromXML(const pugi::xml_node &node)
{
	return (NULL);
}

GUIElement *GUIXML::getGUICheckboxFromXML(const pugi::xml_node &node)
{
	return (NULL);
}

GUIElement *GUIXML::getGUIEditFromXML(const pugi::xml_node &node)
{
	return (NULL);
}

GUIElement *GUIXML::getGUIPanelFromXML(const pugi::xml_node &node)
{
	return (NULL);
}

GUIElement *GUIXML::getGUIScreenFromXML(const pugi::xml_node &node)
{
	return (NULL);
}

GUIElement *GUIXML::getGUIIndicatorFromXML(const pugi::xml_node &node)
{
	return (NULL);
}

GUIElement *GUIXML::getGUITextFromXML(const pugi::xml_node &node)
{
	return (NULL);
}

GUIElement *GUIXML::getGUITextAreaFromXML(const pugi::xml_node &node)
{
	return (NULL);
}