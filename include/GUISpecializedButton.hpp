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
		GUITextButton<T>::GUITextButton(GUIElement *parent, const std::string &label, const std::string &fontResource, const sf::Event::EventType &triggerType = sf::Event::MouseButtonPressed) : T(parent, triggerType)
		{
			_skin = new TextSkin(label, sf::Color::White, sf::Color::Cyan);
			_label.setFont(*SFResolver<sf::Font>::resolve(fontResource));
		}

		GUITextButton<T>::~GUITextButton()
		{
		}

		void GUITextButton<T>::initialUpdate()
		{
			GUIButton::initialUpdate();
			setActiveSkin(static_cast<TextSkin *>(_skin)->text, static_cast<TextSkin *>(_skin)->normal);
			if (_label.getGlobalBounds().contains(Engine::instance->getMousePosition()))
				onHover(true);
			else
				onHover(false);
		}

		virtual void GUITextButton<T>::setLabel(const std::string &label)
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

		void GUITextButton<T>::setActiveSkin(const std::string text, sf::Color color)
		{
			_label.setString(text);
			_label.setFillColor(color);
		}

		virtual const sf::Vector2f GUITextButton<T>::getPosition()
		{
			return (_label.getPosition());
		}

		const sf::Vector2f GUITextButton<T>::getSize()
		{
			return (sf::Vector2f(_label.getLocalBounds().width, _label.getLocalBounds().height));
		}

		virtual bool GUITextButton<T>::onHover(bool triggered)
		{
			T::onHover(triggered);
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
			if (!T::update(e))
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
		GUISpriteButton<T>::GUISpriteButton(GUIElement *parent, const std::string &resource, const sf::Event::EventType &triggerType = sf::Event::MouseButtonPressed) : T(parent, triggerType)
		{
			_sprite.setTexture(*SFResolver<sf::Texture>::resolve(resource));
			_skin = NULL;
		}

		GUISpriteButton<T>::~GUISpriteButton()
		{
		}

		void GUISpriteButton<T>::initialUpdate()
		{
			GUIButton::initialUpdate();
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

		virtual const sf::Vector2f GUISpriteButton<T>::getPosition()
		{
			return (_sprite.getPosition());
		}

		const sf::Vector2f GUISpriteButton<T>::getSize()
		{
			return (sf::Vector2f(_sprite.getLocalBounds().width, _sprite.getLocalBounds().height));
		}

		virtual bool GUISpriteButton<T>::onHover(bool triggered)
		{
			T::onHover(triggered);
			if (_skin == NULL)
				return (false);
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
			if (!T::update(e))
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