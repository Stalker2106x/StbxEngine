#include "GUIXML.hh"
#include "GUIScreen.hh"
#include "Engine.hpp"

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
	{ "sprite", &GUIXML::getGUISpriteFromXML },
	{ "text", &GUIXML::getGUITextFromXML },
	{ "separator", &GUIXML::getGUISeparatorFromXML }
};

std::shared_ptr<GUIElement> GUIXML::getGUIElementFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent, std::shared_ptr<GUIElement> receiver)
{
	if (!node.name() || !GUIXMLElementParser.count(node.name())) //Unknown Element
		return (NULL);
	receiver = GUIXMLElementParser[node.name()](node, parent);
	GUIGenericFromXML(node, receiver);
	receiver->initialUpdate();
	return (receiver);
}

void GUIXML::GUIGenericFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> element)
{
	element->setId(node.attribute("id").as_string(DEFAULT_ID));
	if (node.attribute("x") && node.attribute("y"))
		element->setPosition(sf::Vector2f(convertSize<float>(node.attribute("x").as_string(), Horizontal, element->getParent()),
										  convertSize<float>(node.attribute("y").as_string(), Vertical, element->getParent())));
	else if (node.attribute("x"))
		element->setX(convertSize<float>(node.attribute("x").as_string(), Horizontal, element->getParent()));
	else if (node.attribute("y"))
		element->setY(convertSize<float>(node.attribute("y").as_string(), Vertical, element->getParent()));
	if (node.attribute("dock"))
	{

	}
}

std::shared_ptr<GUIElement> GUIXML::getGUIElementPairFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUIElementPair> element = std::make_shared<GUIElementPair>(parent);
	pugi::xml_node xmlElement = node.first_child();

	if (node.attribute("spacing"))
		element->setSpacing(convertSize<float>(node.attribute("spacing").as_string(), Horizontal, parent));
	else
		element->setSpacing(Engine::instance->gui->defaults.pairSpacing);
	element->setFirst(getGUIElementFromXML(xmlElement, element->getSPtr()));
	xmlElement = xmlElement.next_sibling();
	element->setSecond(getGUIElementFromXML(xmlElement, element->getSPtr()));
	return (element);
}

std::shared_ptr<GUIElement> GUIXML::getGUIElementGridFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUIElementGrid> element = std::make_shared<GUIElementGrid>(parent, sf::Vector2i(node.attribute("columns").as_int(0), node.attribute("rows").as_int(0)));
	pugi::xml_node xmlElement = node.first_child();

	if (node.attribute("spacing"))
		element->setSpacing(convertSize<float>(node.attribute("spacing").as_string(), Horizontal, parent));
	else
		element->setSpacing(Engine::instance->gui->defaults.gridSpacing);
	for (pugi::xml_node it = node.first_child(); it; it = it.next_sibling())
	{
		if (GUIXMLElementParser.count(it.name()))
		{
			element->pushElement(getGUIElementFromXML(it, element->getSPtr()));
		}
	}
	return (element);
}

std::shared_ptr<GUIElement> GUIXML::getGUIButtonFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUIButton> button;

	if (node.attribute("texture")) //GUISpriteButton
	{
		button = std::make_shared<GUISpriteButton<GUIButton>>(parent, node.attribute("texture").as_string());
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
		button = std::make_shared<GUITextButton<GUIButton>>(parent, node.attribute("text").as_string(""), node.attribute("font").as_string(Engine::instance->gui->defaults.font.c_str()));
		std::shared_ptr<GUITextButton<GUIButton>> btn = std::static_pointer_cast<GUITextButton<GUIButton>>(button);
		btn->setFontSize(node.attribute("fontSize").as_int(Engine::instance->gui->defaults.fontSize));
	}
	if (node.attribute("target"))
		button->setCommand("gui_changescreen '" + std::string(node.attribute("target").as_string()) + "'");
	if (node.attribute("command"))
		button->setCommand(std::string(node.attribute("command").as_string()));
	return (button);
}

std::shared_ptr<GUIElement> GUIXML::getGUIToggleButtonFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr <GUIButton> button;

	if (node.attribute("texture")) //GUISpriteButton
	{
		button = std::make_shared<GUISpriteButton<GUIToggleButton>>(parent, node.attribute("texture").as_string());
	}
	else if (node.attribute("text")) //GUITextButton
	{
		button = std::make_shared<GUITextButton<GUIToggleButton>>(parent, node.attribute("text").as_string(""), node.attribute("font").as_string(Engine::instance->gui->defaults.font.c_str()));
		std::shared_ptr<GUITextButton<GUIToggleButton>> btn = std::static_pointer_cast<GUITextButton<GUIToggleButton>>(button);
		btn->setFontSize(node.attribute("fontSize").as_int(Engine::instance->gui->defaults.fontSize));
		btn->setAltSkin(new TextSkin(node.attribute("activetext").as_string(""), sf::Color::White, sf::Color::Cyan));
	}
	return (button);
}

std::shared_ptr<GUIElement> GUIXML::getGUISettingButtonFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr <GUIButton> button;

	if (node.attribute("texture")) //GUISpriteButton
	{
		button = std::make_shared<GUISpriteButton<GUISettingButton>>(parent, node.attribute("texture").as_string());
		std::shared_ptr<GUISpriteButton<GUISettingButton>> btn = std::static_pointer_cast<GUISpriteButton<GUISettingButton>>(button);
		btn->pushValue(node.attribute("text").as_string(""));
		for (pugi::xml_node it = node.first_child(); it; it = it.next_sibling())
		{
			if (strcmp(it.name(), "setting") == 0)
			{
				btn->pushValue(it.attribute("texture").as_string("")); //Should be skin
			}
		}
	}
	else if (node.attribute("text")) //GUITextButton
	{
		button = std::make_shared<GUITextButton<GUISettingButton>>(parent, node.attribute("text").as_string(""), node.attribute("font").as_string(Engine::instance->gui->defaults.font.c_str()));
		std::shared_ptr<GUITextButton<GUISettingButton>> btn = std::static_pointer_cast<GUITextButton<GUISettingButton>>(button);
		btn->setFontSize(node.attribute("fontSize").as_int(Engine::instance->gui->defaults.fontSize));
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

std::shared_ptr<GUIElement> GUIXML::getGUIButtonBarFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUIButtonBar> element;
	std::string orientation = node.attribute("orientation").as_string("horizontal");
	Orientation type;

	if (orientation == "vertical")
		type = Vertical;
	else if (orientation == "horizontal")
		type = Horizontal;
	else
		return (NULL);
	element = std::make_shared<GUIButtonBar>(parent, type);
	element->setSpacing(convertSize<float>(node.attribute("spacing").as_string("0"), type, parent));
	for (pugi::xml_node xmlButton = node.first_child(); xmlButton; xmlButton = xmlButton.next_sibling())
	{
		element->addButton(std::static_pointer_cast<GUIButton>(getGUIElementFromXML(xmlButton, element->getSPtr())));
	}
	return (element);
}

std::shared_ptr<GUIElement> GUIXML::getGUICheckboxFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUICheckbox> element = std::make_shared<GUICheckbox>(parent);
	return (element);
}

std::shared_ptr<GUIElement> GUIXML::getGUIEditFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUIEdit> element = std::make_shared<GUIEdit>(parent, node.attribute("cursor").as_string("_")[0], node.attribute("font").as_string(Engine::instance->gui->defaults.font.c_str()));
	element->setWidth(convertSize<float>(node.attribute("width").as_string("150"), Horizontal, parent));
	element->setColor(convertColorCode(node.attribute("color").as_string("#000000000"), "#"));
	element->setTextColor(convertColorCode(node.attribute("textcolor").as_string(Engine::instance->gui->defaults.fontColor.c_str()), "#"));
	return (element);
}

std::shared_ptr<GUIElement> GUIXML::getGUISliderFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUISlider> element = std::make_shared<GUISlider>(parent);
	return (element);
}

std::shared_ptr<GUIElement> GUIXML::getGUIPanelFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUIPanel> element = std::make_shared<GUIPanel>(parent);
	element->setSpacing(convertSize<float>(node.attribute("spacing").as_string("0"), Vertical, parent));
	for (pugi::xml_node it = node.first_child(); it; it = it.next_sibling())
	{
		if (GUIXMLElementParser.count(it.name()))
		{
			element->addElement(getGUIElementFromXML(it, element->getSPtr()));
		}
	}
	return (element);
}

std::shared_ptr<GUIElement> GUIXML::getGUIScreenFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUIScreen> screen = std::make_shared<GUIScreen>(parent);
	if (node.attribute("background"))
		screen->setBackground(node.attribute("background").as_string());
	for (pugi::xml_node it = node.first_child(); it; it = it.next_sibling())
	{
		if (GUIXMLElementParser.count(it.name()))
		{
			screen->addElement(getGUIElementFromXML(it, screen->getSPtr()));
		}
	}
	return (screen);
}

std::shared_ptr<GUIElement> GUIXML::getGUIIndicatorFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	//GUIIndicator *element = new GUIIndicator<>(node.attribute("text").as_string(), node.attribute("font").as_string(), *this);
	return (NULL);
}

std::shared_ptr<GUIElement> GUIXML::getGUISpriteFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUISprite> element = std::make_shared<GUISprite>(parent, node.attribute("texture").as_string(""));

	return (element);
}

std::shared_ptr<GUIElement> GUIXML::getGUITextFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUIText> element = std::make_shared<GUIText>(parent, node.attribute("text").as_string(""), node.attribute("font").as_string(Engine::instance->gui->defaults.font.c_str()));

	element->setFontSize(node.attribute("fontSize").as_int(Engine::instance->gui->defaults.fontSize));
	return (element);
}

std::shared_ptr<GUIElement> GUIXML::getGUISeparatorFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUISeparator> element = std::make_shared<GUISeparator>(parent, sf::Vector2f(node.attribute("width").as_float(0.0f), node.attribute("height").as_float(0.0f)));

	return (element);
}