#include "GUIXML.hh"

using namespace stb;

std::map<std::string, XMLParserFptr> GUIXMLElementType = {
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
	GUIXMLElementType[node.name()](node);
}

GUIButton *GUIXML::getGUIButtonFromXML(const pugi::xml_node &node) {}
GUIButtonBar *GUIXML::getGUIButtonBarFromXML(const pugi::xml_node &node) {}
GUICheckbox *GUIXML::getGUICheckboxFromXML(const pugi::xml_node &node) {}
GUIEdit *GUIXML::getGUIEditFromXML(const pugi::xml_node &node) {}
GUIPanel *GUIXML::getGUIPanelFromXML(const pugi::xml_node &node) {}
GUIScreen *GUIXML::getGUIScreenFromXML(const pugi::xml_node &node) {}
GUISIndicator *GUIXML::getGUIIndicatorFromXML(const pugi::xml_node &node) {}
GUIText *GUIXML::getGUITextFromXML(const pugi::xml_node &node) {}
GUITextArea *GUIXML::getGUITextAreaFromXML(const pugi::xml_node &node) {}