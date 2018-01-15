#include <pugixml.hpp>
#include <fstream>
#include "Engine.hpp"
#include "utils.h"
#include "defs.h"

namespace stb {

	GUIResourceDefaults GUIDefaults;

	const sf::Color convertColorCode(std::string code, std::string esc)
	{
		sf::Color color;

		if (code.length() < (9 + esc.length()))
			return (sf::Color::White);
		if (code.find(esc) == 0)
			code = code.substr(esc.length(), 9);
		color.r = atoi(code.substr(0, 3).c_str());
		color.g = atoi(code.substr(3, 3).c_str());
		color.b = atoi(code.substr(6, 3).c_str());
		if (code.length() >= (12 + esc.length()))
			color.a = atoi(code.substr(9, 3).c_str());
		else
			color.a = 255;
		return (color);
	}

#ifdef PUGIXML_WCHAR_MODE
	const std::wstring getIconCode(const std::string &id)
	{
		pugi::xml_document doc;
		std::ifstream ifs("../extlib/ionicons/fonts/ionicons.svg");
		pugi::xml_parse_result xml;
		pugi::xml_node node;

		if (!ifs)
		{
			Engine::instance->console->output(COLOR_ERROR, "Error: FontIcons: SVG resource not found");
			return (NULL);
		}
		if (!(xml = doc.load(ifs)))
		{
			Engine::instance->console->output(COLOR_ERROR, "Error: FontIcons: resource SVG parsing failed");
			return (NULL);
		}
		node = doc.child(L"svg").child(L"defs").child(L"font").first_child();
		while (wcscmp(node.name(), L"glyph") != 0)
			node = node.next_sibling();
		while (node != doc.child(L"font").last_child())
		{
			if (node.attribute(L"glyph-name").as_string() == pugi::as_wide(id))
				return (node.attribute(L"unicode").as_string());
			node = node.next_sibling();
		}
		return (L""); //Unknown Glyph
	}
#endif

}