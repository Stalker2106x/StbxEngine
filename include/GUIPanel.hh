/*!
* @file      GUIPanel.hh
* @brief     GUI static or draggable panels
*
*            This class is designed to provide movables or static panels that acts as container for GUIElement items
*/
#ifndef GUIPANEL_HH_
#define GUIPANEL_HH_

#include <deque>
#include <stack>
#include "GUIElement.hpp"
#include "GUIButton.hh"
#include "utils.h"

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
		GUIPanel(std::shared_ptr<GUIElement> parent) : GUIElement("", parent, Panel), _buttonBar(getSPtr(), Horizontal) {};
		GUIPanel(std::shared_ptr<GUIElement> parent, const sf::Vector2i &size, const sf::Color &color = sf::Color::Transparent);
		GUIPanel(std::shared_ptr<GUIElement> parent, const sf::Vector2i &size, const std::string &name);
		virtual ~GUIPanel();

		virtual void initialUpdate();

		void clear();
		bool removeElement(int index);
		void drop();

		virtual void setPosition(const sf::Vector2f &pos);
		void setBackground(const std::string &resource, const sf::Color &color = sf::Color::White);
		void setSpacing(int spacing);
		void setStyle(char style);

		virtual const sf::Vector2f getPosition() const;
		virtual const sf::Vector2f getSize() const;

		void addElement(std::shared_ptr<GUIElement> element);

		virtual bool updateRT();
		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow &win);

	protected:
		char _style;
		int _spacing;
		std::string _id;
		sf::Sprite _frame;
		GUIButtonBar _buttonBar;
		std::deque<std::shared_ptr<GUIElement>> _elements;
		std::stack<size_t> _drop;
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
		GUIDraggablePanel(std::shared_ptr<GUIElement> parent, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor);
		GUIDraggablePanel(std::shared_ptr<GUIElement> parent, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource);
		virtual ~GUIDraggablePanel();
		void initialUpdate();

		void toggleLock();
		virtual void toggle();

		void setPosition(const sf::Vector2f &pos);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow &win);

	private:
		bool _dragging, _lock;
		sf::Vector2f _dragOffset;
		sf::Sprite _header;
	};

}

#endif /* !GUIPANEL_HH_ */