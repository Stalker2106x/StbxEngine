#include "GUIXML.hh"
#include "GUIScreen.hh"

using namespace stb;

std::map<std::string, XMLParserFptr> stb::GUIXMLElementParser = {
	{ "pair", &GUIXML::getGUIElementPairFromXML },
	{ "button", &GUIXML::getGUIButtonFromXML },
	{ "buttonBar", &GUIXML::getGUIButtonBarFromXML },
	{ "checkbox", &GUIXML::getGUICheckboxFromXML },
	{ "edit", &GUIXML::getGUIEditFromXML },
	{ "panel", &GUIXML::getGUIPanelFromXML },
	{ "menu", &GUIXML::getGUIMenuFromXML },
	{ "screen", &GUIXML::getGUIScreenFromXML },
	{ "indicator", &GUIXML::getGUIIndicatorFromXML },
	{ "text", &GUIXML::getGUITextFromXML },
	{ "textArea", &GUIXML::getGUITextAreaFromXML }
};

GUIElement *GUIXML::getGUIElementFromXML(const pugi::xml_node &node)
{
	GUIElement *element;

	if (!node.name())
		return (NULL);
	if (strcmp(node.name(), "menu") == 0) //tmp
		element = GUIMenu::parseXML(node);
	else
		element = GUIXMLElementParser[node.name()](node);
	GUIGenericFromXML(node, element);
	element->initialUpdate();
	return (element);
}

void GUIXML::GUIGenericFromXML(const pugi::xml_node &node, GUIElement *element)
{
	element->setId(node.attribute("id").as_string(DEFAULT_ID));
	if (node.attribute("x"))
		element->setX(node.attribute("x").as_float());
	if (node.attribute("y"))
		element->setY(node.attribute("y").as_float());
}

GUIElement *GUIXML::getGUIElementPairFromXML(const pugi::xml_node &node)
{
	GUIElementPair *element = new GUIElementPair();
	pugi::xml_node xmlElement = node.first_child();

	element->setFirst(getGUIElementFromXML(xmlElement));
	xmlElement = xmlElement.next_sibling();
	element->setSecond(getGUIElementFromXML(xmlElement));
	return (element);
}

GUIElement *GUIXML::getGUIButtonFromXML(const pugi::xml_node &node)
{
	if (node.attribute("texture")) //GUISpriteButton
	{
		GUISpriteButton<GUIButton> *element = new GUISpriteButton<GUIButton>(node.attribute("texture").as_string());
		return (element);
	}
	else if (node.attribute("text")) //GUITextButton
	{
		GUITextButton<GUIButton> *element = new GUITextButton<GUIButton>(node.attribute("text").as_string(""), node.attribute("font").as_string(""));
		return (element);
	}
	else
	{
		return (NULL);
	}
}

GUIElement *GUIXML::getGUIButtonBarFromXML(const pugi::xml_node &node)
{
	GUIButtonBar *element = NULL;
	std::string type = node.attribute("orientation").as_string("horizontal");

	if (type == "vertical")
	{
		element = new GUIButtonBar(Vertical);
	}
	else if (type == "horizontal")
	{
		element = new GUIButtonBar(Horizontal);
	}
	if (element == NULL)
		return (NULL);
	for (pugi::xml_node xmlButton = node.first_child(); xmlButton; xmlButton = xmlButton.next_sibling())
	{
		element->addButton(dynamic_cast<GUIButton *>(getGUIElementFromXML(xmlButton)));
	}
	return (element);
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
	for (pugi::xml_node it = node.first_child(); it; it = it.next_sibling())
	{
		if (GUIXMLElementParser.count(it.name()))
		{
			element->addElement(getGUIElementFromXML(it));
		}
	}
	return (element);
}

GUIElement *GUIXML::getGUIMenuFromXML(const pugi::xml_node &node)
{
	GUIMenu *menu = new GUIMenu();
	menu->parseMenu(node);
	return (menu);
}

GUIElement *GUIXML::getGUIScreenFromXML(const pugi::xml_node &node)
{
	GUIScreen *screen = new GUIScreen();
	if (node.child("background"))
		screen->setBackground(node.child_value("background"));
	for (pugi::xml_node it = node.first_child(); it; it = it.next_sibling())
	{
		if (GUIXMLElementParser.count(it.name()))
		{
			screen->addElement(getGUIElementFromXML(it));
		}
	}
	return (screen);
}

GUIElement *GUIXML::getGUIIndicatorFromXML(const pugi::xml_node &node)
{
	GUISIndicator *element = new GUISIndicator();
	return (element);
}

GUIElement *GUIXML::getGUITextFromXML(const pugi::xml_node &node)
{
	GUIText *element = new GUIText(node.attribute("text").as_string(""));

	element->setFont(node.attribute("font").as_string(""));
	return (element);
}

GUIElement *GUIXML::getGUITextAreaFromXML(const pugi::xml_node &node)
{
	GUITextArea *element = new GUITextArea();
	return (element);
}