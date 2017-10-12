/*!
* @file      GUIXML.hh
* @class     stb::GUIXML
* @brief     GUI XML Parser
*
*            This classes set provide GUI elements loaders from XML Screens resources.
*            It is used merely for building screens, but also to map GUIElements inside menus.
*/
#ifndef GUIXML_HH_
#define GUIXML_HH_

#ifdef STBXENGINE_CORE
#include <pugixml.hpp>
#endif
#include "GUIElement.hpp"
#include "GUIEntity.hh"
#include "GUIPanel.hh"

#define DEFAULT_ID	""

namespace stb
{
#ifdef STBXENGINE_CORE
	class GUIScreen; //Forward
	
	class GUIXML
	{
	public:
		static GUIElement *getGUIElementFromXML(GUIScreen *container, const pugi::xml_node &node);
		static void GUIGenericFromXML(GUIScreen *container, const pugi::xml_node &node, GUIElement *element);

		static GUIElement *getGUIButtonFromXML(const pugi::xml_node &node);
		static GUIElement *getGUIButtonBarFromXML(const pugi::xml_node &node);
		static GUIElement *getGUICheckboxFromXML(const pugi::xml_node &node);
		static GUIElement *getGUIEditFromXML(const pugi::xml_node &node);
		static GUIElement *getGUIPanelFromXML(const pugi::xml_node &node);
		static GUIElement *getGUIScreenFromXML(const pugi::xml_node &node);
		static GUIElement *getGUIIndicatorFromXML(const pugi::xml_node &node);
		static GUIElement *getGUITextFromXML(const pugi::xml_node &node);
		static GUIElement *getGUITextAreaFromXML(const pugi::xml_node &node);

	private:

	};

	//Pointer to GUIXML parsing function
	typedef GUIElement *(*XMLParserFptr)(const pugi::xml_node &);

	// This map binds XML Nodes names to corresponding C++ Parser
	extern std::map<std::string, XMLParserFptr> GUIXMLElementParser;
#endif
}

#endif /* !GUIXML_HH_ */