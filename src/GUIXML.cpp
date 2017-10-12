#include "GUIXML.hh"
#include "GUIScreen.hh"

using namespace stb;

std::map<std::string, XMLParserFptr> stb::GUIXMLElementParser = {
	{ "button", &GUIXML::getGUIButtonFromXML },
	{ "buttonBar", &GUIXML::getGUIButtonBarFromXML },
	{ "checkbox", &GUIXML::getGUICheckboxFromXML },
	{ "edit", &GUIXML::getGUIEditFromXML },
	{ "panel", &GUIXML::getGUIPanelFromXML },
	{ "screen", &GUIXML::getGUIScreenFromXML },
	{ "indicator", &GUIXML::getGUIIndicatorFromXML },
	{ "text", &GUIXML::getGUITextFromXML },
	{ "textArea", &GUIXML::getGUITextAreaFromXML }
};

GUIElement *GUIXML::getGUIElementFromXML(GUIScreen *container, const pugi::xml_node &node)
{
	if (!node.name())
		return (NULL);
	GUIElement *element = GUIXMLElementParser[node.name()](node);
	GUIGenericFromXML(container, node, element);
	return (element);
}

void GUIXML::GUIGenericFromXML(GUIScreen *container, const pugi::xml_node &node, GUIElement *element)
{
	element->setId(node.attribute("id").as_string(DEFAULT_ID));
	for (pugi::xml_node it = node.first_child(); it; it = it.next_sibling())
	{
		if (GUIXMLElementParser.count(it.name()))
		{
			container->addElement(getGUIElementFromXML(container, it));
		}
	}
}


GUIElement *GUIXML::getGUIButtonFromXML(const pugi::xml_node &node)
{
	//Detected later based on background
	//	GUIButton *element = new GUIButton();
	return (NULL);
}

GUIElement *GUIXML::getGUIButtonBarFromXML(const pugi::xml_node &node)
{
	//Detected later based on Horizontal or vertical
	//GUIButtonBar *element = new GUIButtonBar();
	return (NULL);
}

GUIElement *GUIXML::getGUICheckboxFromXML(const pugi::xml_node &node)
{
	GUICheckbox *element = new GUICheckbox();
	return (element);
}

GUIElement *GUIXML::getGUIEditFromXML(const pugi::xml_node &node)
{
	GUIEdit *element = new GUIEdit();
	return (element);
}

GUIElement *GUIXML::getGUIPanelFromXML(const pugi::xml_node &node)
{
	GUIPanel *element = new GUIPanel();
	return (element);
}

GUIElement *GUIXML::getGUIScreenFromXML(const pugi::xml_node &node)
{
	GUIScreen *screen = new GUIScreen();
	if (node.child("background"))
		screen->setBackground(node.child_value("background"));
	return (screen);
}

GUIElement *GUIXML::getGUIIndicatorFromXML(const pugi::xml_node &node)
{
	GUISIndicator *element = new GUISIndicator();
	return (element);
}

GUIElement *GUIXML::getGUITextFromXML(const pugi::xml_node &node)
{
	GUIText *element = new GUIText();
	return (element);
}

GUIElement *GUIXML::getGUITextAreaFromXML(const pugi::xml_node &node)
{
	GUITextArea *element = new GUITextArea();
	return (element);
}