#include "GUIXML.hh"
#include "GUIScreen.hh"

using namespace stb;

std::map<std::string, XMLParserFptr> stb::GUIXMLElementParser = {
	{ "pair", &GUIXML::getGUIElementPairFromXML },
	{ "grid", &GUIXML::getGUIElementGridFromXML },
	{ "button", &GUIXML::getGUIButtonFromXML },
	{ "toggleButton", &GUIXML::getGUIToggleButtonFromXML },
	{ "settingButton", &GUIXML::getGUISettingButtonFromXML },
	{ "buttonBar", &GUIXML::getGUIButtonBarFromXML },
	{ "checkbox", &GUIXML::getGUICheckboxFromXML },
	{ "edit", &GUIXML::getGUIEditFromXML },
	{ "slider", &GUIXML::getGUISliderFromXML },
	{ "panel", &GUIXML::getGUIPanelFromXML },
	{ "screen", &GUIXML::getGUIScreenFromXML },
	{ "indicator", &GUIXML::getGUIIndicatorFromXML },
	{ "text", &GUIXML::getGUITextFromXML },
	{ "textArea", &GUIXML::getGUITextAreaFromXML }
};

GUIElement *GUIXML::getGUIElementFromXML(const pugi::xml_node &node, GUIElement *receiver)
{
	if (!node.name() || !GUIXMLElementParser.count(node.name())) //Unknown Element
		return (NULL);
	receiver = GUIXMLElementParser[node.name()](node);
	GUIGenericFromXML(node, receiver);
	receiver->initialUpdate();
	return (receiver);
}

void GUIXML::GUIGenericFromXML(const pugi::xml_node &node, GUIElement *element)
{
	element->setId(node.attribute("id").as_string(DEFAULT_ID));
	if (node.attribute("x") && node.attribute("y"))
		element->setPosition(sf::Vector2f(node.attribute("x").as_float(), node.attribute("y").as_float()));
	else if (node.attribute("x"))
		element->setX(node.attribute("x").as_float());
	else if (node.attribute("y"))
		element->setY(node.attribute("y").as_float());
}

GUIElement *GUIXML::getGUIElementPairFromXML(const pugi::xml_node &node)
{
	GUIElementPair *element = new GUIElementPair();
	pugi::xml_node xmlElement = node.first_child();

	element->setSpacing(node.attribute("spacing").as_int(0));
	element->setFirst(getGUIElementFromXML(xmlElement));
	xmlElement = xmlElement.next_sibling();
	element->setSecond(getGUIElementFromXML(xmlElement));
	return (element);
}

GUIElement *GUIXML::getGUIElementGridFromXML(const pugi::xml_node &node)
{
	GUIElementGrid *element = new GUIElementGrid(sf::Vector2i(node.attribute("columns").as_int(0), node.attribute("rows").as_int(0)));
	pugi::xml_node xmlElement = node.first_child();

	element->setSpacing(node.attribute("spacing").as_int(0));
	for (pugi::xml_node it = node.first_child(); it; it = it.next_sibling())
	{
		if (GUIXMLElementParser.count(it.name()))
		{
			element->pushElement(getGUIElementFromXML(it));
		}
	}
	return (element);
}

GUIElement *GUIXML::getGUIButtonFromXML(const pugi::xml_node &node)
{
	GUIButton *button = NULL;

	if (node.attribute("texture")) //GUISpriteButton
	{
		button = new GUISpriteButton<GUIButton>(node.attribute("texture").as_string());
		pugi::xml_node it = node.first_child(); //Get and set skins, should be moved to a generic func and called in all instances of button.
		sf::IntRect normal, hover;
		if (it)
		{
			while (it)
			{
				if (strcmp(it.name(), "skin") == 0)
				{
					if (strcmp(it.attribute("type").as_string(), "hover") == 0)
						hover = sf::IntRect(node.attribute("left").as_int(0), node.attribute("top").as_int(0), node.attribute("width").as_int(0), node.attribute("height").as_int(0));
					else
						normal = sf::IntRect(node.attribute("left").as_int(0), node.attribute("top").as_int(0), node.attribute("width").as_int(0), node.attribute("height").as_int(0));
				}
				it = it.next_sibling();
			}
			button->setSkin(new SpriteSkin(normal, hover));
		}
	}
	else if (node.attribute("text")) //GUITextButton
	{
		button = new GUITextButton<GUIButton>(node.attribute("text").as_string(""), node.attribute("font").as_string(""));
	}
	if (node.attribute("target"))
		button->setCommand("gui_changescreen '" + std::string(node.attribute("target").as_string()) + "'");
	return (button);
}

GUIElement *GUIXML::getGUIToggleButtonFromXML(const pugi::xml_node &node)
{
	GUIButton *button = NULL;

	if (node.attribute("texture")) //GUISpriteButton
	{
		button = new GUISpriteButton<GUIToggleButton>(node.attribute("texture").as_string());
	}
	else if (node.attribute("text")) //GUITextButton
	{
		button = new GUITextButton<GUIToggleButton>(node.attribute("text").as_string(""), node.attribute("font").as_string(""));
		GUITextButton<GUIToggleButton> *btn = dynamic_cast<GUITextButton<GUIToggleButton> *>(button);
		btn->setAltSkin(new TextSkin(node.attribute("activetext").as_string(""), sf::Color::White, sf::Color::Cyan));
	}
	return (button);
}

GUIElement *GUIXML::getGUISettingButtonFromXML(const pugi::xml_node &node)
{
	GUIButton *button = NULL;

	if (node.attribute("texture")) //GUISpriteButton
	{
		button = new GUISpriteButton<GUISettingButton>(node.attribute("texture").as_string());
		GUISpriteButton<GUISettingButton> *btn = dynamic_cast<GUISpriteButton<GUISettingButton> *>(button);
		btn->pushValue(node.attribute("text").as_string(""));
		for (pugi::xml_node it = node.first_child(); it; it = it.next_sibling())
		{
			if (strcmp(it.name(), "setting") == 0)
			{
				btn->pushValue(it.attribute("text").as_string(""));
			}
		}
	}
	else if (node.attribute("text")) //GUITextButton
	{
		button = new GUITextButton<GUISettingButton>(node.attribute("text").as_string(""), node.attribute("font").as_string(""));
		GUITextButton<GUISettingButton> *btn = dynamic_cast<GUITextButton<GUISettingButton> *>(button);
		btn->pushValue(node.attribute("text").as_string(""));
		for (pugi::xml_node it = node.first_child(); it; it = it.next_sibling())
		{
			if (strcmp(it.name(), "setting") == 0)
			{
				btn->pushValue(it.attribute("text").as_string(""));
			}
		}
	}
	return (button);
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
	element->setSpacing(node.attribute("spacing").as_int(0));
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
	element->setFont(node.attribute("font").as_string(""));
	element->setWidth(node.attribute("width").as_float(150.0f));
	element->setColor(Console::convertColorCode(node.attribute("color").as_string("#000000000"), "#"));
	element->setTextColor(Console::convertColorCode(node.attribute("textcolor").as_string("#255255255"), "#"));
	return (element);
}

GUIElement *GUIXML::getGUISliderFromXML(const pugi::xml_node &node)
{
	GUISlider *element = new GUISlider();
	return (element);
}

GUIElement *GUIXML::getGUIPanelFromXML(const pugi::xml_node &node)
{
	GUIPanel *element = new GUIPanel();
	element->setSpacing(node.attribute("spacing").as_int(0));
	for (pugi::xml_node it = node.first_child(); it; it = it.next_sibling())
	{
		if (GUIXMLElementParser.count(it.name()))
		{
			element->addElement(getGUIElementFromXML(it));
		}
	}
	return (element);
}

GUIElement *GUIXML::getGUIScreenFromXML(const pugi::xml_node &node)
{
	GUIScreen *screen = new GUIScreen();
	if (node.attribute("background"))
		screen->setBackground(node.attribute("background").as_string());
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