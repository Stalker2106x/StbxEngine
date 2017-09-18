/*!
 * @file      MenuItem.hh
 * @brief     Menu items (links, settings, sliders, text inputs, ...)
 *
 *            This classes set provide usables objects for all kinds of items in a menu.
 *            It defines Links, Settings, and Edit types,which are specialized in child objects
 *            like Sliders, Static and Dynamic enums for Settings, and Key or String for Edit.
 */

#ifndef MENUITEM_HH_
#define MENUITEM_HH_

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Engine.hpp"
#include "GUIButton.hh"

namespace stb {

	class Menu; //Forward declaration for Menu Handles

	enum MenuItemType {
		Link,
		Setting,
		DynamicSetting,
		Edit,
		Slider,
		Checkbox
	};

	enum ItemMode {
		Text,
		Sprite
	};

	/*!
	 * @class MenuItem
	 * @brief Abstract Menu item
	 *
	 *        This class is not instanciable. It is used as an abstract layer to store Items generically in Menu class.
	 */
	class MenuItem
	{
	public:
		MenuItem();
		~MenuItem();

		static MenuItem *factory(const MenuItemType &type);
		
		void setLabel(const std::string &label);
		void setPadding(int padding);
		virtual void setColor(const sf::Color &color);
		virtual void setFontsize(int size);
		virtual void setXOffset(const float &x);
		virtual void setYOffset(const float &y);
		virtual void setOffset(const float &x, const float &y);

		virtual void initialUpdate();
		virtual void onClick() = 0;

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *);

		static std::unordered_map<std::string, MenuItemType> typeMap; //move String to int ID

	protected:
		Engine *_e;
		ItemMode _mode;
		int _padding;
		GUIButton *_label;
		bool _active;
	};

	/*!
	 * @class MenuLink
	 * @brief Menu link to another menu or action
	 *
	 *        Link defines a MenuItem that is clickable and points towards another menu or do a specific action (quit, apply settings, ...)
	 */
	class MenuLink : public MenuItem
	{
	public:
		MenuLink();
		~MenuLink();

		void setMenuHandle(Menu *menu);
		void setTarget(const std::string &target);
		void setCustomAction(void(*fptr)(void *), void *cparam);
		void setCommand(const std::string &command);

		virtual void onClick() override;

		virtual bool update(const sf::Event &e);

	private:
		std::string _target;
		Menu *_menuHandle;
		void(*_customPtr)(void *);
		void *_customParam;
		std::string *_customCommand;
	};

	/*!
	 * @class MenuSetting
	 * @brief Static Setting item, showing a list of values defined in XML.
	 *
	 *        This class holds a static enum defined in XML, for dynamic values, use child MenuDynamicSetting
	 */
	class MenuSetting : public MenuItem
	{
	public:
		MenuSetting();
		~MenuSetting();

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
	 * @class MenuDynamicSetting
	 * @brief Dynamic Setting item, showing a list of values known only at runtime.
	 *
	 *        This class holds a dynamic enum filled at runtime, for static values, use parent MenuSetting
	 */
	class MenuDynamicSetting : public MenuSetting
	{
	public:
		MenuDynamicSetting();
		~MenuDynamicSetting();
	};

	/*!
	 * @class MenuEdit
	 * @brief Input box, either used for key binding, or text input from user
	 *
	 *        This item is an input box to get a string from the user inside a Menu.
	 */
	class MenuEdit : public MenuItem
	{
	public:
		MenuEdit();
		~MenuEdit();

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
	 * @class MenuSlider
	 * @brief Slider Setting item, accept any value within defined range
	 *
	 *        This item is a setting bar moving horizontally to get values from user.
	 */
	class MenuSlider : public MenuItem
	{
	public:
		MenuSlider();
		~MenuSlider();

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
	* @class MenuCheckbox
	* @brief Checkbox Setting item
	*
	*        This item is a box that allows to be checked (true) or unchecked (false)
	*/
	class MenuCheckbox : public MenuItem
	{
	public:
		MenuCheckbox();
		~MenuCheckbox();

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
