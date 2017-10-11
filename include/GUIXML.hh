/*!
* @file      GUIXML.hh
* @brief     GUI XML Parser
*
*            This classes set provide GUI elements loaders from XML Screens resources.
*            It is used merely for building screens, but also to map GUIElements inside menus.
*/
#ifndef GUIXML_HH_
#define GUIXML_HH_

#include <pugixml.hpp>
#include "GUIScreen.hh"
#include "GUIElement.hh"
#include "GUIEntity.hh"
#include "GUIPanel.hh"

namespace stb
{
	class GUIXML
	{
	public:
		static GUIElement *getGUIElementFromXML(const pugi::xml_node &node);

		static GUIButton *getGUIButtonFromXML(const pugi::xml_node &node);
		static GUIButtonBar *getGUIButtonBarFromXML(const pugi::xml_node &node);
		static GUICheckbox *getGUICheckboxFromXML(const pugi::xml_node &node);
		static GUIEdit *getGUIEditFromXML(const pugi::xml_node &node);
		static GUIPanel *getGUIPanelFromXML(const pugi::xml_node &node);
		static GUIScreen *getGUIScreenFromXML(const pugi::xml_node &node);
		static GUISIndicator *getGUIIndicatorFromXML(const pugi::xml_node &node);
		static GUIText *getGUITextFromXML(const pugi::xml_node &node);
		static GUITextArea *getGUITextAreaFromXML(const pugi::xml_node &node);

	private:

	};

	//Pointer to GUIXML parsing function
	typedef GUIElement *(*XMLParserFptr)(const pugi::xml_node &);

	// This map binds XML Nodes names to corresponding C++ Parser
	extern std::map<std::string, XMLParserFptr> GUIXMLElementType;
}

#endif /* !GUIXML_HH_ */