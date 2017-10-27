/*!
* @file      GUIButton.hh
* @brief     Buttons placeable on GUI
*
*            This classes set provide GUI buttons to draw info over the renderer frame.
*            They should be managed through GUI module and its containers
*/
#ifndef GUIBUTTON_HH_
#define GUIBUTTON_HH_

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include "GUIElement.hpp"
#include "GUISpecializedButton.hpp"

namespace stb {
	
	//Skins definition (A skin is a normal+Hover Version of a TextColor / SpriteTexture)
	enum SkinType {
		SkinText,
		SkinSprite
	};

	struct Skin {
		SkinType type;
	};

	struct TextSkin : public Skin
	{
		sf::Color normal;
		sf::Color hover;

		TextSkin() { type = SkinText; }
		TextSkin(sf::Color n, sf::Color h)
		{
			type = SkinText;
			normal = n;
			hover = h;
		}
	};

	struct SpriteSkin : public Skin
	{
		sf::IntRect normal;
		sf::IntRect hover;

		SpriteSkin() { type = SkinSprite; }
		SpriteSkin(sf::IntRect n, sf::IntRect h)
		{
			type = SkinSprite;
			normal = n;
			hover = h;
		}
	};

	/*!
	* @class GUIButton
	* @brief Abstract button superclass
	*
	*        This class should not be instanciated. It is used as an abstract layer to control behaviour of all button types
	*/
	class GUIButton : public GUIElement
	{
	public:
		GUIButton(const sf::Event::EventType &triggerType = sf::Event::EventType::MouseButtonPressed);
		virtual ~GUIButton();

		virtual void initialUpdate();

		bool isHovered() const;
		void setClickCallback(const std::function<void(void)> &fptr);
		void setRClickCallback(const std::function<void(void)> &fptr);
		virtual void setPosition(const sf::Vector2f &pos) = 0;
		void setSkin(Skin *skin);

		virtual void setActiveSkin(const sf::Color color) {}; //Overloadable for inheritance
		virtual void setActiveSkin(const sf::IntRect geometry) {}; //Overloadable for inheritance

		virtual bool onHover(bool triggered);
		virtual void onClick();
		virtual void onRClick();
		
		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win) = 0;
	protected:
		bool _hover;
		sf::Event::EventType _triggerType;
		Skin *_skin;
		std::function<void(void)> *_onClickCallback;
		std::function<void(void)> *_onRClickCallback;
	};

	/*!
	* @class GUIToggleButton
	* @brief Clickable, hovereable and toggleable button
	*
	*        This represents a "On/Off" clickable button entity on screen. Appearance changes wether its on or off
	*/
	class GUIToggleButton : public GUIButton
	{
	public:
		GUIToggleButton(const sf::Event::EventType &triggerType = sf::Event::MouseButtonPressed);
		virtual ~GUIToggleButton();

		void setAltSkin(Skin *skin);

		bool onHover(bool triggered) override;
		virtual void onClick() override;

		virtual bool update(const sf::Event &e);
	private:
		bool _state;
		Skin *_altSkin;
	};

	/*!
	* @class GUIButtonBar
	* @brief Button Bar implementation
	*
	*        This class provides a stackable container for gui buttons
	*/
	enum BarType {
		Horizontal,
		Vertical
	};
	class GUIButtonBar : public GUIElement
	{
	public:
		GUIButtonBar(BarType type);
		virtual ~GUIButtonBar();

		virtual void initialUpdate();

		void invert();
		GUIButton *getButton(const std::string &id);
		void setSpacing(int spacing);
		const sf::Vector2f calcButtonPosition(const size_t &index, const sf::Vector2f &pos);
		virtual void setPosition(const sf::Vector2f &pos);

		virtual const sf::Vector2f &getPosition();
		virtual const sf::Vector2f getSize();

		GUIButton *addButton(GUIButton *button);
		GUITextButton<GUIButton> *addTextButton(const std::string &label, const std::string &fontResource);
		GUISpriteButton<GUIButton> *addSpriteButton(const std::string &resource);
		GUISpriteButton<GUIToggleButton> *addToggleSpriteButton(const std::string &resource);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);

	private:
		std::vector<GUIButton *> _buttons;
		int _spacing;
		bool _inverted;
		BarType _type;
	};

}

#endif /* !GUIBUTTON_HH_ */