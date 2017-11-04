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
#include "GUIElementGrid.hh"
#include "GUIElementPair.hh"
#include "GUIEntity.hh"
#include "GUIPanel.hh"

#define DEFAULT_ID	""

namespace stb
{
#ifdef STBXENGINE_CORE
	
	class GUIXML
	{
	public:
		static GUIElement *getGUIElementFromXML(const pugi::xml_node &node, GUIElement *parent = NULL, GUIElement *receiver = NULL);

		static void GUIGenericFromXML(const pugi::xml_node &node, GUIElement *element);

		static GUIElement *getGUIElementPairFromXML(const pugi::xml_node &node, GUIElement *parent = NULL);
		static GUIElement *getGUIElementGridFromXML(const pugi::xml_node &node, GUIElement *parent = NULL);
		static GUIElement *getGUIButtonFromXML(const pugi::xml_node &node, GUIElement *parent = NULL);
		static GUIElement *getGUIToggleButtonFromXML(const pugi::xml_node &node, GUIElement *parent = NULL);
		static GUIElement *getGUISettingButtonFromXML(const pugi::xml_node &node, GUIElement *parent = NULL);
		static GUIElement *getGUIButtonBarFromXML(const pugi::xml_node &node, GUIElement *parent = NULL);
		static GUIElement *getGUICheckboxFromXML(const pugi::xml_node &node, GUIElement *parent = NULL);
		static GUIElement *getGUIEditFromXML(const pugi::xml_node &node, GUIElement *parent = NULL);
		static GUIElement *getGUISliderFromXML(const pugi::xml_node &node, GUIElement *parent = NULL);
		static GUIElement *getGUIPanelFromXML(const pugi::xml_node &node, GUIElement *parent = NULL);
		static GUIElement *getGUIScreenFromXML(const pugi::xml_node &node, GUIElement *parent = NULL);
		static GUIElement *getGUIIndicatorFromXML(const pugi::xml_node &node, GUIElement *parent = NULL);
		static GUIElement *getGUITextFromXML(const pugi::xml_node &node, GUIElement *parent = NULL);
		static GUIElement *getGUITextAreaFromXML(const pugi::xml_node &node, GUIElement *parent = NULL);

	private:

	};

	//Pointer to GUIXML parsing function
	typedef GUIElement *(*XMLParserFptr)(const pugi::xml_node &, GUIElement *);

	// This map binds XML Nodes names to corresponding C++ Parser
	extern std::map<std::string, XMLParserFptr> GUIXMLElementParser;
#endif
}

#endif /* !GUIXML_HH_ */