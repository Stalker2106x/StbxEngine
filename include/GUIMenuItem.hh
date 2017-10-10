/*!
 * @file      GUIMenuItem.hh
 * @brief     GUI Menu items (links, settings, sliders, text inputs, ...)
 *
 *            This classes set provide usables objects for all kinds of items in a menu.
 *            It defines Links, Settings, and Edit types,which are specialized in child objects
 *            like Sliders, Static and Dynamic enums for Settings, and Key or String for Edit.
 */

#ifndef GUIMENUITEM_HH_
#define GUIMENUITEM_HH_

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Engine.hpp"
#include "GUIButton.hh"

namespace stb {

	class GUIMenu; //Forward declaration for Menu Handles

	enum GUIMenuItemType {
		Link,
		Setting,
		DynamicSetting,
		Edit,
		Slider,
		Checkbox
	};

	enum GUIMenuItemMode {
		Text,
		Sprite
	};

	/*!
	 * @class GUIMenuItem
	 * @brief Abstract Menu item
	 *
	 *        This class is not instanciable. It is used as an abstract layer to store Items generically in Menu class.
	 */
	class GUIMenuItem : public GUIElement
	{
	public:
		GUIMenuItem();
		~GUIMenuItem();

		static GUIMenuItem *factory(const GUIMenuItemType &type);
		
		void setLabel(const std::string &label);
		void setPadding(int padding);
		virtual void setColor(const sf::Color &color);
		virtual void setFontsize(int size);
		virtual void setPosition(const sf::Vector2f &pos);
		virtual void setXOffset(const float &x);
		virtual void setYOffset(const float &y);
		virtual void setOffset(const float &x, const float &y);
		int &getPadding();

		virtual void initialUpdate();
		virtual void onClick() = 0;

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *);

		static std::unordered_map<std::string, GUIMenuItemType> typeMap; //move String to int ID

	protected:
		Engine *_e;
		GUIMenuItemMode _mode;
		int _padding;
		GUIButton *_label;
		bool _active;
	};

	/*!
	 * @class GUIMenuLink
	 * @brief Menu link to another menu or action
	 *
	 *        Link defines a MenuItem that is clickable and points towards another menu or do a specific action (quit, apply settings, ...)
	 */
	class GUIMenuLink : public GUIMenuItem
	{
	public:
		GUIMenuLink();
		~GUIMenuLink();

		void setMenuHandle(GUIMenu *menu);
		void setTarget(const std::string &target);
		void setCustomAction(void(*fptr)(void *), void *cparam);
		void setCommand(const std::string &command);

		virtual void onClick() override;

		virtual bool update(const sf::Event &e);

	private:
		std::string _target;
		GUIMenu *_menuHandle;
		void(*_customPtr)(void *);
		void *_customParam;
		std::string *_customCommand;
	};

	/*!
	 * @class GUIMenuSetting
	 * @brief Static Setting item, showing a list of values defined in XML.
	 *
	 *        This class holds a static enum defined in XML, for dynamic values, use child MenuDynamicSetting
	 */
	class GUIMenuSetting : public GUIMenuItem
	{
	public:
		GUIMenuSetting();
		~GUIMenuSetting();

		virtual void onClick();
		virtual void onRClick();
		bool onValueHover(bool triggered);

		virtual void setFontsize(int size) override;
		virtual void setXOffset(const float &x) override;
		virtual void setYOffset(const float &y) override;
		void setValues(std::vector<std::string> &values, int defaultIndex = 0);
		int getCurrentIndex();

		void updateValue();
		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *);

	private:
		GUITextButton *_value;
		std::vector<std::string> _values;
		size_t _index;
	};

	/*!
	 * @class GUIMenuDynamicSetting
	 * @brief Dynamic Setting item, showing a list of values known only at runtime.
	 *
	 *        This class holds a dynamic enum filled at runtime, for static values, use parent MenuSetting
	 */
	class GUIMenuDynamicSetting : public GUIMenuSetting
	{
	public:
		GUIMenuDynamicSetting();
		~GUIMenuDynamicSetting();
	};

	/*!
	 * @class GUIMenuEdit
	 * @brief Input box, either used for key binding, or text input from user
	 *
	 *        This item is an input box to get a string from the user inside a Menu.
	 */
	class GUIMenuEdit : public GUIMenuItem
	{
	public:
		GUIMenuEdit();
		~GUIMenuEdit();

		virtual void setFontsize(int fontsize) override;
		virtual void setXOffset(const float &x) override;
		virtual void setYOffset(const float &y) override;
		void setInputColor(sf::Color *inputColor, sf::Color *valueColor);
		void setInputLength(const float &length);

		virtual void onClick() override;

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *);
	private:
		GUIEdit _edit;
	};

	/*!
	 * @class GUIMenuSlider
	 * @brief Slider Setting item, accept any value within defined range
	 *
	 *        This item is a setting bar moving horizontally to get values from user.
	 */
	class GUIMenuSlider : public GUIMenuItem
	{
	public:
		GUIMenuSlider();
		~GUIMenuSlider();

		void setRange(int min, int max);
		virtual void setXOffset(const float &x) override;
		virtual void setYOffset(const float &y) override;
		void setBarWidth(int width);
		void setBarColor(const sf::Color *barColor, const sf::Color *fillColor);
		virtual void setFontsize(int fontsize) override;

		int getValue();

		virtual void onClick() override {};

		void updateSlider(const sf::Event &e, bool forceupdate = false);
		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *);
	private:
		bool _sliding;
		int _value;
		int _range[2];
		sf::RectangleShape _bar, _fill;
	};

	/*!
	* @class GUIMenuCheckbox
	* @brief Checkbox Setting item
	*
	*        This item is a box that allows to be checked (true) or unchecked (false)
	*/
	class GUIMenuCheckbox : public GUIMenuItem
	{
	public:
		GUIMenuCheckbox();
		~GUIMenuCheckbox();

		virtual void setXOffset(const float &x) override;
		virtual void setYOffset(const float &y) override;
		void setCheckboxColor(const sf::Color *containerColor, const sf::Color *fillColor);

		virtual void onClick() override {};

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *);
	private:
		GUICheckbox _checkBox;
	};
}

#endif /* !MENUITEM_HH_ */
