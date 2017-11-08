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
#include "GUIContainer.hh"
#include "GUIEntity.hh"
#include "GUIPanel.hh"
#include "utils.h"

namespace stb
{
#ifdef STBXENGINE_CORE
	
	class GUIXML
	{
	public:
		static std::shared_ptr<GUIElement> getGUIElementFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent = NULL, std::shared_ptr<GUIElement> receiver = NULL);

		static void GUIGenericFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> element);

		static std::shared_ptr<GUIElement> getGUIElementPairFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent = NULL);
		static std::shared_ptr<GUIElement> getGUIElementGridFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent = NULL);
		static std::shared_ptr<GUIElement> getGUIButtonFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent = NULL);
		static std::shared_ptr<GUIElement> getGUIToggleButtonFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent = NULL);
		static std::shared_ptr<GUIElement> getGUISettingButtonFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent = NULL);
		static std::shared_ptr<GUIElement> getGUIButtonBarFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent = NULL);
		static std::shared_ptr<GUIElement> getGUICheckboxFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent = NULL);
		static std::shared_ptr<GUIElement> getGUIEditFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent = NULL);
		static std::shared_ptr<GUIElement> getGUISliderFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent = NULL);
		static std::shared_ptr<GUIElement> getGUIPanelFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent = NULL);
		static std::shared_ptr<GUIElement> getGUIScreenFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent = NULL);
		static std::shared_ptr<GUIElement> getGUIIndicatorFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent = NULL);
		static std::shared_ptr<GUIElement> getGUISpriteFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent = NULL);
		static std::shared_ptr<GUIElement> getGUITextFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent = NULL);
		static std::shared_ptr<GUIElement> getGUISeparatorFromXML(const pugi::xml_node &node, std::shared_ptr<GUIElement> parent = NULL);

	private:

	};

	//Pointer to GUIXML parsing function
	typedef std::shared_ptr<GUIElement> (*XMLParserFptr)(const pugi::xml_node &, std::shared_ptr<GUIElement>);

	// This map binds XML Nodes names to corresponding C++ Parser
	extern std::map<std::string, XMLParserFptr> GUIXMLElementParser;
#endif
}

#endif /* !GUIXML_HH_ */