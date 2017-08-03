/*!
* @file      GUIPanel.hh
* @brief     GUI static or draggable panels
*
*            This class is designed to provide movables or static panels that acts as container for GUIElement items
*/
#ifndef GUIPANEL_HH_
#define GUIPANEL_HH_

#include "GUIElement.hh"
#include "GUIButton.hh"

namespace stb {

	/*!
	* @class GUIPanel
	* @brief Panel for GUI
	*
	*        This class is a panel to group indicators, or set custom actions bars, ...
	*/

	#define PN_CLOSE		      1  //Adds close button to header
	#define PN_LOCK		          2  //Adds poslock to header

	enum PanelButton {
		Close,
		Lock,
	};

	class GUIPanel : public GUIElement
	{
	public:
		GUIPanel();
		GUIPanel(const std::string &id, const sf::Vector2i &size, const sf::Color &color);
		GUIPanel(const std::string &id, const sf::Vector2i &size, const std::string &name);
		~GUIPanel();

		virtual void setPosition(const sf::Vector2f &pos);
		void setStyle(const char &style);

		void addElement(GUIElement *element);
		void updateElementsPosition();

		bool onButtonHover(const PanelButton &id, const bool &triggered);

		virtual bool updateRT();
		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);

	protected:
		char _style;
		std::string _id;
		sf::Sprite _frame;
		GUIButtonBar _buttonBar;
		std::vector<GUIElement *> _elements;
	};

	/*!
	* @class GUIDraggablePanel
	* @brief Draggable implementation of panel
	*
	*        This class is a Panel, that can be moved around in interface.
	*/

	class GUIDraggablePanel : public GUIPanel
	{
	public:
		GUIDraggablePanel(const std::string &id, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor);
		GUIDraggablePanel(const std::string &id, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource);
		~GUIDraggablePanel();
		void initialUpdate();

		void toggleLock();
		virtual void toggle();

		void setPosition(const sf::Vector2f &pos);

		bool onButtonHover(const PanelButton &id, const bool &triggered);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);

	private:
		bool _dragging, _lock;
		sf::Vector2f _dragOffset;
		sf::Sprite _header;
	};

}

#endif /* !GUIPANEL_HH_ */