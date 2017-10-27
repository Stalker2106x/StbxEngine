/*!
* @file      GUISpecializedButton.hh
* @brief     Buttons Specialization file
*
*            This classes set provide GUI buttons to draw info over the renderer frame.
*            They should inherit from Base Buttons Classes
*/
#ifndef GUISPECIALIZEDBUTTON_HH_
#define GUISPECIALIZEDBUTTON_HH_

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include "GUIElement.hpp"

namespace stb {

	/*!
	* @class GUITextButton
	* @brief Clickable and hovereable simple text button
	*
	*        This represents a clickable text button entity on screen.
	*/
	template <typename T>
	class GUITextButton : public T
	{
	public:
		GUITextButton<T>::GUITextButton(const std::string &label, const std::string &fontResource, const sf::Event::EventType &triggerType = sf::Event::MouseButtonPressed) : T(triggerType)
		{
			_label.setString(label);
			_label.setFont(*SFResolver<sf::Font>::resolve(fontResource));
		}

		GUITextButton<T>::~GUITextButton()
		{
		}

		void GUITextButton<T>::initialUpdate()
		{
			GUIButton::initialUpdate();
			_skin = new TextSkin(sf::Color::White, sf::Color::Cyan);
			if (_label.getGlobalBounds().contains(Engine::instance->getMousePosition()))
				onHover(true);
			else
				onHover(false);
		}

		void GUITextButton<T>::setLabel(const std::string &label)
		{
			_label.setString(label);
		}

		void GUITextButton<T>::setFont(const sf::Font &font)
		{
			_label.setFont(font);
		}

		void GUITextButton<T>::setPosition(const sf::Vector2f &pos)
		{
			_label.setPosition(pos);
		}

		void GUITextButton<T>::setFontsize(int size)
		{
			_label.setCharacterSize(size);
		}

		void GUITextButton<T>::setColor(const sf::Color &color)
		{
			_label.setFillColor(color);
		}

		void GUITextButton<T>::setActiveSkin(const sf::Color color)
		{
			_label.setFillColor(color);
		}

		const sf::Vector2f &GUITextButton<T>::getPosition()
		{
			return (_label.getPosition());
		}

		const sf::Vector2f GUITextButton<T>::getSize()
		{
			return (sf::Vector2f(_label.getLocalBounds().width, _label.getLocalBounds().height));
		}

		bool GUITextButton<T>::onHover(bool triggered)
		{
			GUIButton::onHover(triggered);
			if (triggered)
			{
				_label.setFillColor(static_cast<TextSkin *>(_skin)->hover);
			}
			else
			{
				_label.setFillColor(static_cast<TextSkin *>(_skin)->normal);
			}
			return (true);
		}

		bool GUITextButton<T>::update(const sf::Event &e)
		{
			if (!GUIButton::update(e))
				return (false);
			if (e.type == sf::Event::MouseMoved)
			{
				if (_label.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(e.mouseMove.x), static_cast<float>(e.mouseMove.y))))
					onHover(true);
				else
					onHover(false);
			}
			return (true);
		}

		void GUITextButton<T>::draw(sf::RenderWindow *win)
		{
			if (!_active)
				return;
			win->draw(_label);
		}

	private:
		sf::Text _label;
	};

	/*!
	* @class GUISpriteButton
	* @brief Clickable and hovereable textured button
	*
	*        This represents a clickable image button entity on screen.
	*/
	template <typename T>
	class GUISpriteButton : public T
	{
	public:
		GUISpriteButton<T>::GUISpriteButton(const std::string &resource, const sf::Event::EventType &triggerType = sf::Event::MouseButtonPressed) : T(triggerType)
		{
			_sprite.setTexture(*SFResolver<sf::Texture>::resolve(resource));
		}

		GUISpriteButton<T>::~GUISpriteButton()
		{
		}

		void GUISpriteButton<T>::initialUpdate()
		{
			GUIButton::initialUpdate();
			_sprite.setTextureRect(static_cast<SpriteSkin *>(_skin)->normal);
		}

		void GUISpriteButton<T>::setTexture(const std::string &resource)
		{
			_sprite.setTexture(*SFResolver<sf::Texture>::resolve(resource));
		}

		void GUISpriteButton<T>::setActiveSkin(const sf::IntRect geometry)
		{
			_sprite.setTextureRect(geometry);
		}

		void GUISpriteButton<T>::setPosition(const sf::Vector2f &pos)
		{
			_sprite.setPosition(pos);
		}

		const sf::Vector2f &GUISpriteButton<T>::getPosition()
		{
			return (_sprite.getPosition());
		}

		const sf::Vector2f GUISpriteButton<T>::getSize()
		{
			return (sf::Vector2f(_sprite.getLocalBounds().width, _sprite.getLocalBounds().height));
		}

		bool GUISpriteButton<T>::onHover(bool triggered)
		{
			GUIButton::onHover(triggered);
			if (triggered)
			{
				_sprite.setTextureRect(static_cast<SpriteSkin *>(_skin)->hover);
			}
			else
			{
				_sprite.setTextureRect(static_cast<SpriteSkin *>(_skin)->normal);
			}
			return (true);
		}

		bool GUISpriteButton<T>::update(const sf::Event &e)
		{
			if (!GUIButton::update(e))
				return (false);
			if (e.type == sf::Event::MouseMoved)
			{
				if (_sprite.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(e.mouseMove.x), static_cast<float>(e.mouseMove.y))))
					onHover(true);
				else
					onHover(false);
			}
			return (true);
		}

		void GUISpriteButton<T>::draw(sf::RenderWindow *win)
		{
			if (!_active)
				return;
			win->draw(_sprite);
		}

	protected:
		sf::Sprite _sprite;
	};

}

#endif /* !GUISPECIALIZEDBUTTON_HH_ */