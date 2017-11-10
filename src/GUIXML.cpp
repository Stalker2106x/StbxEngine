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
	if (!node.name() || !GUIXMLElementParser.count(pugi::as_utf8(node.name()))) //Unknown Element
		return (NULL);
	receiver = GUIXMLElementParser[pugi::as_utf8(node.name())](node, parent);
	GUIGenericFromXML(node, receiver);
	receiver->initialUpdate();
	return (receiver);
}

void GUIXML::GUIGenericFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> element)
{
	element->setId(pugi::as_utf8(node.attribute(L"id").as_string(DEFAULT_ID)));
	if (node.attribute(L"x") && node.attribute(L"y"))
		element->setPosition(sf::Vector2f(convertSize<float>(pugi::as_utf8(node.attribute(L"x").as_string()), Horizontal, element->getParent()),
										  convertSize<float>(pugi::as_utf8(node.attribute(L"y").as_string()), Vertical, element->getParent())));
	else if (node.attribute(L"x"))
		element->setX(convertSize<float>(pugi::as_utf8(node.attribute(L"x").as_string()), Horizontal, element->getParent()));
	else if (node.attribute(L"y"))
		element->setY(convertSize<float>(pugi::as_utf8(node.attribute(L"y").as_string()), Vertical, element->getParent()));
	if (node.attribute(L"dock"))
	{

	}
}

std::shared_ptr<GUIElement> GUIXML::getGUIElementPairFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUIElementPair> element = std::make_shared<GUIElementPair>(parent);
	pugi::xml_node xmlElement = node.first_child();

	if (node.attribute(L"spacing"))
		element->setSpacing(convertSize<float>(pugi::as_utf8(node.attribute(L"spacing").as_string()), Horizontal, parent));
	else
		element->setSpacing(GUIDefaults.pairSpacing);
	element->setFirst(getGUIElementFromXML(xmlElement, element->getSPtr()));
	xmlElement = xmlElement.next_sibling();
	element->setSecond(getGUIElementFromXML(xmlElement, element->getSPtr()));
	return (element);
}

std::shared_ptr<GUIElement> GUIXML::getGUIElementGridFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUIElementGrid> element = std::make_shared<GUIElementGrid>(parent, sf::Vector2i(node.attribute(L"columns").as_int(0), node.attribute(L"rows").as_int(0)));
	pugi::xml_node xmlElement = node.first_child();

	if (node.attribute(L"spacing"))
		element->setSpacing(convertSize<float>(pugi::as_utf8(node.attribute(L"spacing").as_string()), Horizontal, parent));
	else
		element->setSpacing(GUIDefaults.gridSpacing);
	for (pugi::xml_node it = node.first_child(); it; it = it.next_sibling())
	{
		if (GUIXMLElementParser.count(pugi::as_utf8(it.name())))
		{
			element->pushElement(getGUIElementFromXML(it, element->getSPtr()));
		}
	}
	return (element);
}

std::shared_ptr<GUIElement> GUIXML::getGUIButtonFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUIButton> button;

	if (node.attribute(L"texture")) //GUISpriteButton
	{
		button = std::make_shared<GUISpriteButton<GUIButton>>(parent, pugi::as_utf8(node.attribute(L"texture").as_string()));
		pugi::xml_node it = node.first_child(); //Get and set skins, should be moved to a generic func and called in all instances of button.
		sf::IntRect normal, hover;
		if (it)
		{
			while (it)
			{
				if (wcscmp(it.name(), L"skin") == 0)
				{
					if (it.attribute(L"type").as_string() == L"hover")
						hover = sf::IntRect(node.attribute(L"left").as_int(0), node.attribute(L"top").as_int(0), node.attribute(L"width").as_int(0), node.attribute(L"height").as_int(0));
					else
						normal = sf::IntRect(node.attribute(L"left").as_int(0), node.attribute(L"top").as_int(0), node.attribute(L"width").as_int(0), node.attribute(L"height").as_int(0));
				}
				it = it.next_sibling();
			}
			button->setSkin(new SpriteSkin(normal, hover));
		}
	}
	else if (node.attribute(L"text")) //GUITextButton
	{
		button = std::make_shared<GUITextButton<GUIButton>>(parent, pugi::as_utf8(node.attribute(L"text").as_string(L"")), (node.attribute(L"font") ? pugi::as_utf8(node.attribute(L"font").as_string()) : GUIDefaults.font.c_str()));
		std::shared_ptr<GUITextButton<GUIButton>> btn = std::static_pointer_cast<GUITextButton<GUIButton>>(button);
		btn->setFontSize(node.attribute(L"fontSize").as_int(GUIDefaults.fontSize));
	}
	if (node.attribute(L"target"))
		button->setCommand("gui_changescreen '" + std::string(pugi::as_utf8(node.attribute(L"target").as_string())) + "'");
	if (node.attribute(L"command"))
		button->setCommand(std::string(pugi::as_utf8(node.attribute(L"command").as_string(L""))));
	return (button);
}

std::shared_ptr<GUIElement> GUIXML::getGUIToggleButtonFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr <GUIButton> button;

	if (node.attribute(L"texture")) //GUISpriteButton
	{
		button = std::make_shared<GUISpriteButton<GUIToggleButton>>(parent, pugi::as_utf8(node.attribute(L"texture").as_string()));
	}
	else if (node.attribute(L"text")) //GUITextButton
	{
		button = std::make_shared<GUITextButton<GUIToggleButton>>(parent, pugi::as_utf8(node.attribute(L"text").as_string(L"")), (node.attribute(L"font") ? pugi::as_utf8(node.attribute(L"font").as_string()) : GUIDefaults.font.c_str()));
		std::shared_ptr<GUITextButton<GUIToggleButton>> btn = std::static_pointer_cast<GUITextButton<GUIToggleButton>>(button);
		btn->setFontSize(node.attribute(L"fontSize").as_int(GUIDefaults.fontSize));
		btn->setAltSkin(new TextSkin(node.attribute(L"activetext").as_string(L""), sf::Color::White, sf::Color::Cyan));
	}
	return (button);
}

std::shared_ptr<GUIElement> GUIXML::getGUISettingButtonFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr <GUIButton> button;

	if (node.attribute(L"texture")) //GUISpriteButton
	{
		button = std::make_shared<GUISpriteButton<GUISettingButton>>(parent, pugi::as_utf8(node.attribute(L"texture").as_string()));
		std::shared_ptr<GUISpriteButton<GUISettingButton>> btn = std::static_pointer_cast<GUISpriteButton<GUISettingButton>>(button);
		btn->pushValue(pugi::as_utf8(node.attribute(L"text").as_string(L"")));
		for (pugi::xml_node it = node.first_child(); it; it = it.next_sibling())
		{
			if (wcscmp(it.name(), L"setting") == 0)
			{
				btn->pushValue(pugi::as_utf8(it.attribute(L"texture").as_string(L""))); //Should be skin
			}
		}
	}
	else if (node.attribute(L"text")) //GUITextButton
	{
		button = std::make_shared<GUITextButton<GUISettingButton>>(parent, pugi::as_utf8(node.attribute(L"text").as_string(L"")), (node.attribute(L"font") ? pugi::as_utf8(node.attribute(L"font").as_string()) : GUIDefaults.font.c_str()));
		std::shared_ptr<GUITextButton<GUISettingButton>> btn = std::static_pointer_cast<GUITextButton<GUISettingButton>>(button);
		btn->setFontSize(node.attribute(L"fontSize").as_int(GUIDefaults.fontSize));
		btn->pushValue(pugi::as_utf8(node.attribute(L"text").as_string(L"")));
		for (pugi::xml_node it = node.first_child(); it; it = it.next_sibling())
		{
			if (wcscmp(it.name(), L"setting") == 0)
			{
				btn->pushValue(pugi::as_utf8(it.attribute(L"text").as_string(L"")));
			}
		}
	}
	return (button);
}

std::shared_ptr<GUIElement> GUIXML::getGUIButtonBarFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUIButtonBar> element;
	std::string orientation = pugi::as_utf8(node.attribute(L"orientation").as_string(L"horizontal"));
	Orientation type;

	if (orientation == "vertical")
		type = Vertical;
	else if (orientation == "horizontal")
		type = Horizontal;
	else
		return (NULL);
	element = std::make_shared<GUIButtonBar>(parent, type);
	element->setSpacing(convertSize<float>(pugi::as_utf8(node.attribute(L"spacing").as_string(L"0")), type, parent));
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
	std::shared_ptr<GUIEdit> element = std::make_shared<GUIEdit>(parent, pugi::as_utf8(node.attribute(L"cursor").as_string(L"_"))[0], (node.attribute(L"font") ? pugi::as_utf8(node.attribute(L"font").as_string()) : GUIDefaults.font.c_str()));
	element->setWidth(convertSize<float>(pugi::as_utf8(node.attribute(L"width").as_string(L"150")), Horizontal, parent));
	element->setColor(convertColorCode(pugi::as_utf8(node.attribute(L"color").as_string(L"#000000000")), "#"));
	element->setTextColor(convertColorCode((node.attribute(L"textcolor") ? pugi::as_utf8(node.attribute(L"textcolor").as_string()) : GUIDefaults.fontColor.c_str()), "#"));
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
	element->setSpacing(convertSize<float>(pugi::as_utf8(node.attribute(L"spacing").as_string(L"0")), Vertical, parent));
	for (pugi::xml_node it = node.first_child(); it; it = it.next_sibling())
	{
		if (GUIXMLElementParser.count(pugi::as_utf8(it.name())))
		{
			element->addElement(getGUIElementFromXML(it, element->getSPtr()));
		}
	}
	return (element);
}

std::shared_ptr<GUIElement> GUIXML::getGUIScreenFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUIScreen> screen = std::make_shared<GUIScreen>(parent);
	if (node.attribute(L"background"))
		screen->setBackground(pugi::as_utf8(node.attribute(L"background").as_string()));
	for (pugi::xml_node it = node.first_child(); it; it = it.next_sibling())
	{
		if (GUIXMLElementParser.count(pugi::as_utf8(it.name())))
		{
			screen->addElement(getGUIElementFromXML(it, screen->getSPtr()));
		}
	}
	return (screen);
}

std::shared_ptr<GUIElement> GUIXML::getGUIIndicatorFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	//GUIIndicator *element = new GUIIndicator<>(node.attribute(L"text").as_string(), node.attribute(L"font").as_string(), *this);
	return (NULL);
}

std::shared_ptr<GUIElement> GUIXML::getGUISpriteFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUISprite> element = std::make_shared<GUISprite>(parent, pugi::as_utf8(node.attribute(L"texture").as_string(L"")));

	return (element);
}

std::shared_ptr<GUIElement> GUIXML::getGUITextFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUIText> element = std::make_shared<GUIText>(parent, pugi::as_utf8(node.attribute(L"text").as_string(L"")), (node.attribute(L"font") ? pugi::as_utf8(node.attribute(L"font").as_string()) : GUIDefaults.font.c_str()));

	element->setFontSize(node.attribute(L"fontSize").as_int(GUIDefaults.fontSize));
	return (element);
}

std::shared_ptr<GUIElement> GUIXML::getGUISeparatorFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent)
{
	std::shared_ptr<GUISeparator> element = std::make_shared<GUISeparator>(parent, sf::Vector2f(node.attribute(L"width").as_float(0.0f), node.attribute(L"height").as_float(0.0f)));

	return (element);
}