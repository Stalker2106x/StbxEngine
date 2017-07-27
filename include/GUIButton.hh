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

		virtual void initialUpdate() = 0;

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);
	private:
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
	class GUITextButton : public GUIButton
	{
	public:
		GUITextButton();
		GUITextButton(const std::string &id, const std::string &label, const std::string &fontResource, sf::Color skins[2], const sf::Event::EventType &triggerType = sf::Event::MouseButtonPressed);
		~GUITextButton();

		void setLabel(const std::string &label);
		void setFont(const sf::Font &font);
		virtual void setPosition(const sf::Vector2f &pos);
		void setFontsize(const int &size);
		void setColor(const sf::Color &color);
		virtual const sf::Vector2f &getPosition();
		virtual const sf::FloatRect &getLocalBounds();
		virtual const sf::FloatRect &getGlobalBounds();

		void initialUpdate();

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);
	private:
		sf::Text _label;
		sf::Color _skins[];
	};

	/*!
	* @class GUISpriteButton
	* @brief Clickable and hovereable textured button
	*
	*        This represents a clickable image button entity on screen.
	*/
	class GUISpriteButton : public GUIButton
	{
	public:
		GUISpriteButton();
		GUISpriteButton(const std::string &id, const std::string &resource, sf::IntRect skins[], const sf::Event::EventType &triggerType = sf::Event::MouseButtonPressed);
		~GUISpriteButton();

		void setTexture(const std::string &resource);
		void setPosition(const sf::Vector2f &pos);
		virtual const sf::Vector2f &getPosition();
		virtual const sf::FloatRect &getLocalBounds();
		virtual const sf::FloatRect &getGlobalBounds();

		void initialUpdate();

		bool onHover(const bool &triggered);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);
	private:
		sf::Sprite _sprite;
		char _activeSkin;
		sf::IntRect _skins[];
	};

	/*!
	* @class GUIButtonBar
	* @brief Button Bar implementation
	*
	*        This class provides a stackable container for gui buttons
	*/
	class GUIButtonBar : public GUIElement
	{
	public:
		GUIButtonBar();
		~GUIButtonBar();

		GUIButton *getButton(const std::string &id);
		void setPosition(const sf::Vector2f &pos);

		GUITextButton *GUIButtonBar::addTextButton(const std::string &id, const std::string &label, const std::string &fontResource, const sf::Color &normalSkin, const sf::Color &hoverSkin);
		GUISpriteButton *GUIButtonBar::addSpriteButton(const std::string &id, const std::string &resource, const sf::IntRect &normalSkin, const sf::IntRect &hoverSkin);

		virtual bool update(const sf::Event &e);
		virtual void draw(sf::RenderWindow *win);

	private:
		std::vector<GUIButton *> _buttons;
	};

}

#endif /* !GUIBUTTON_HH_ */