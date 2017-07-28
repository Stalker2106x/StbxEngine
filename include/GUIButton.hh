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
#include "GUIElement.hh"

namespace stb {
	
	/*!
	* @class GUIButton
	* @brief Abstract button superclass
	*
	*        This class should not be instanciated. It is used as an abstract layer to control behaviour of all button types
	*/
	class GUIButton : public GUIElement
	{
	public:
		GUIButton();
		GUIButton(const std::string &id, const sf::Event::EventType &triggerType);
		~GUIButton();

		bool isHovered() const;
		void setClickCallback(const std::function<void(void)> &fptr);
		void setRClickCallback(const std::function<void(void)> &fptr);
		virtual void setPosition(const sf::Vector2f &pos) = 0;
		virtual const sf::Vector2f &getPosition() = 0;
		virtual const sf::FloatRect &getLocalBounds() = 0;
		virtual const sf::FloatRect &getGlobalBounds() = 0;

		virtual bool onHover(const bool &triggered);
		virtual void onClick();
		virtual void onRClick();

		virtual void initialUpdate() = 0;

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);
	protected:
		bool _hover;
		sf::Event::EventType _triggerType;
		std::function<void(void)> _onClickCallback;
		std::function<void(void)> _onRClickCallback;
	};

	/*!
	* @class GUITextButton
	* @brief Clickable and hovereable simple text button
	*
	*        This represents a clickable text button entity on screen.
	*/
	struct TextSkin
	{
		sf::Color normal;
		sf::Color hover;

		TextSkin() {}
		TextSkin(sf::Color n, sf::Color h)
		{
			normal = n;
			hover = h;
		}
	};

	class GUITextButton : public GUIButton
	{
	public:
		GUITextButton();
		GUITextButton(const std::string &id, const std::string &label, const std::string &fontResource, const TextSkin &skin, const sf::Event::EventType &triggerType = sf::Event::MouseButtonPressed);
		~GUITextButton();

		void setLabel(const std::string &label);
		void setFont(const sf::Font &font);
		virtual void setPosition(const sf::Vector2f &pos);
		void setFontsize(const int &size);
		void setColor(const sf::Color &color);
		virtual const sf::Vector2f &getPosition();
		virtual const sf::FloatRect &getLocalBounds();
		virtual const sf::FloatRect &getGlobalBounds();

		virtual void initialUpdate();

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);
	private:
		sf::Text _label;
		TextSkin _skin;
	};

	/*!
	* @class GUISpriteButton
	* @brief Clickable and hovereable textured button
	*
	*        This represents a clickable image button entity on screen.
	*/
	struct SpriteSkin
	{
		sf::IntRect normal;
		sf::IntRect hover;

		SpriteSkin() {}
		SpriteSkin(sf::IntRect n, sf::IntRect h)
		{
			normal = n;
			hover = h;
		}
	};

	class GUISpriteButton : public GUIButton
	{
	public:
		GUISpriteButton();
		GUISpriteButton(const std::string &id, const std::string &resource, const SpriteSkin &skin, const sf::Event::EventType &triggerType = sf::Event::MouseButtonPressed);
		~GUISpriteButton();

		void setTexture(const std::string &resource);
		void setPosition(const sf::Vector2f &pos);
		virtual const sf::Vector2f &getPosition();
		virtual const sf::FloatRect &getLocalBounds();
		virtual const sf::FloatRect &getGlobalBounds();

		virtual void initialUpdate();

		bool onHover(const bool &triggered);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);
	protected:
		bool _state;
		sf::Sprite _sprite;
		SpriteSkin _skin;
	};

	/*!
	* @class GUIToggleSpriteButton
	* @brief Clickable and hovereable textured toggleable button
	*
	*        This represents a clickable image button entity on screen. Image changes wether its on or off
	*/
	class GUIToggleSpriteButton : public GUISpriteButton
	{
	public:
		GUIToggleSpriteButton();
		GUIToggleSpriteButton(const std::string &id, const std::string &resource, const SpriteSkin &skin, const SpriteSkin &altSkin, const sf::Event::EventType &triggerType = sf::Event::MouseButtonPressed);
		~GUIToggleSpriteButton();
		
		bool onHover(const bool &triggered) override;
		virtual void onClick() override;

		virtual bool update(const sf::Event &e);
	private:
		SpriteSkin _altSkin;
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
		~GUIButtonBar();

		void invert();
		GUIButton *getButton(const std::string &id);
		void setSpacing(const int &spacing);
		const sf::Vector2f &calcButtonPosition(const size_t &index, const sf::Vector2f &pos);
		void setPosition(const sf::Vector2f &pos);

		GUITextButton *addTextButton(const std::string &id, const std::string &label, const std::string &fontResource, const TextSkin &skin);
		GUISpriteButton *addSpriteButton(const std::string &id, const std::string &resource, const SpriteSkin &skin);
		GUIToggleSpriteButton *addToggleSpriteButton(const std::string &id, const std::string &resource, const SpriteSkin &skin, const SpriteSkin &altSkin);

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