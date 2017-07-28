#include "GUIButton.hh"
#include "Engine.hpp"
#include "Resolver.hh"

using namespace stb;

//
// GUIButton
//

GUIButton::GUIButton() : GUIElement()
{
	_hover = false;
	_triggerType = sf::Event::MouseButtonPressed;
}

GUIButton::GUIButton(const std::string &id, const sf::Event::EventType &triggerType) : GUIElement(id)
{
	_triggerType = triggerType;
}

GUIButton::~GUIButton()
{
}

bool GUIButton::isHovered() const
{
	return (_hover);
}

void GUIButton::setClickCallback(const std::function<void(void)> &fptr)
{
	_onClickCallback = fptr;
}

void GUIButton::setRClickCallback(const std::function<void(void)> &fptr)
{
	_onRClickCallback = fptr;
}

bool GUIButton::onHover(const bool &triggered)
{
	if ((triggered && _hover)
		|| (!triggered && !_hover))
		return (false);
	if (triggered)
		_hover = true;
	else
		_hover = false;
	return (true);
}

void GUIButton::onClick()
{
	_onClickCallback();
}

void GUIButton::onRClick()
{
	_onRClickCallback();
}

bool GUIButton::update(const sf::Event &e)
{
	if (!GUIElement::update(e))
		return (false);
	if (e.type == _triggerType && _hover)
	{
		if (e.key.code == sf::Mouse::Left && !_onClickCallback._Empty())
			onClick();
		else if (e.key.code == sf::Mouse::Right && !_onRClickCallback._Empty())
			onRClick();
	}
	return (true);
}

void GUIButton::draw(sf::RenderWindow *win)
{

}

//
// GUITextButton
//

GUITextButton::GUITextButton() : GUIButton()
{
}

GUITextButton::GUITextButton(const std::string &id, const std::string &label, const std::string &fontResource, const TextSkin &skin, const sf::Event::EventType &triggerType) : GUIButton(id, triggerType)
{
	_label.setString(label);
	_label.setFont(*Resolver<sf::Font>::resolve(fontResource));
	_skin = skin;
}

GUITextButton::~GUITextButton()
{
}

void GUITextButton::setLabel(const std::string &label)
{
	_label.setString(label);
}

void GUITextButton::setFont(const sf::Font &font)
{
	_label.setFont(font);
}

void GUITextButton::setPosition(const sf::Vector2f &pos)
{
	_label.setPosition(pos);
}

void GUITextButton::setFontsize(const int &size)
{
	_label.setCharacterSize(size);
}

void GUITextButton::setColor(const sf::Color &color)
{
	_label.setFillColor(color);
}

const sf::Vector2f &GUITextButton::getPosition()
{
	return (_label.getPosition());
}

const sf::FloatRect &GUITextButton::getLocalBounds()
{
	return (_label.getLocalBounds());
}

const sf::FloatRect &GUITextButton::getGlobalBounds()
{
	return (_label.getGlobalBounds());
}

void GUITextButton::initialUpdate()
{
	if (_label.getGlobalBounds().contains(Engine::instance->getMousePosition()))
		onHover(true);
}

bool GUITextButton::update(const sf::Event &e)
{
	if (!GUIButton::update(e))
		return (false);
	if (e.type == sf::Event::MouseMoved)
	{
		if (_label.getGlobalBounds().contains(sf::Vector2f(e.mouseMove.x, e.mouseMove.y)))
			onHover(true);
		else
			onHover(false);
	}
	return (true);
}

void GUITextButton::draw(sf::RenderWindow *win)
{
	if (!_active)
		return;
	win->draw(_label);
}

//
// GUISpriteButton
//

GUISpriteButton::GUISpriteButton() : GUIButton()
{
}

GUISpriteButton::GUISpriteButton(const std::string &id, const std::string &resource, const SpriteSkin &skin, const sf::Event::EventType &triggerType) : GUIButton(id, triggerType)
{
	_sprite.setTexture(*Resolver<sf::Texture>::resolve(resource));
	_skin = skin;
}

GUISpriteButton::~GUISpriteButton()
{
}

void GUISpriteButton::setTexture(const std::string &resource)
{
	_sprite.setTexture(*Resolver<sf::Texture>::resolve(resource));
}

void GUISpriteButton::setPosition(const sf::Vector2f &pos)
{
	_sprite.setPosition(pos);
}

const sf::Vector2f &GUISpriteButton::getPosition()
{
	return (_sprite.getPosition());
}

const sf::FloatRect &GUISpriteButton::getLocalBounds()
{
	return (_sprite.getLocalBounds());
}

const sf::FloatRect &GUISpriteButton::getGlobalBounds()
{
	return (_sprite.getGlobalBounds());
}

void GUISpriteButton::initialUpdate()
{
	if (_sprite.getGlobalBounds().contains(Engine::instance->getMousePosition()))
		onHover(true);
}

bool GUISpriteButton::onHover(const bool &triggered)
{
	GUIButton::onHover(triggered);
	if (triggered)
	{
		_sprite.setTextureRect(_skin.hover);
	}
	else
	{
		_sprite.setTextureRect(_skin.normal);
	}
	return (true);
}

bool GUISpriteButton::update(const sf::Event &e)
{
	if (!GUIButton::update(e))
		return (false);
	if (e.type == sf::Event::MouseMoved)
	{
		if (_sprite.getGlobalBounds().contains(sf::Vector2f(e.mouseMove.x, e.mouseMove.y)))
			onHover(true);
		else
			onHover(false);
	}
	return (true);
}

void GUISpriteButton::draw(sf::RenderWindow *win)
{
	if (!_active)
		return;
	win->draw(_sprite);
}

//
// GUIToggleSpriteButton
//

GUIToggleSpriteButton::GUIToggleSpriteButton() : GUISpriteButton()
{
	_state = false;
}

GUIToggleSpriteButton::GUIToggleSpriteButton(const std::string &id, const std::string &resource, const SpriteSkin &skin, const SpriteSkin &altSkin, const sf::Event::EventType &triggerType) : GUISpriteButton(id, resource, skin, triggerType)
{
	_state = false;
	_altSkin = altSkin;
}

GUIToggleSpriteButton::~GUIToggleSpriteButton()
{
}

bool GUIToggleSpriteButton::onHover(const bool &triggered)
{
	GUIButton::onHover(triggered);
	if (triggered)
	{
		if (_state)
			_sprite.setTextureRect(_altSkin.hover);
		else
			_sprite.setTextureRect(_skin.hover);
	}
	else
	{
		if (_state)
			_sprite.setTextureRect(_altSkin.normal);
		else
			_sprite.setTextureRect(_skin.normal);
	}
	return (true);
}

void GUIToggleSpriteButton::onClick()
{
	_state = (_state ? false : true);
	_onClickCallback();
}

bool GUIToggleSpriteButton::update(const sf::Event &e)
{
	if (!GUISpriteButton::update(e))
		return (false);
	return (true);
}

//
// GUIButtonBar
//

GUIButtonBar::GUIButtonBar(BarType type)
{
	_spacing = 0;
	_type = type;
	_inverted = false;
}

GUIButtonBar::~GUIButtonBar()
{

}

void GUIButtonBar::invert()
{
	_inverted = (_inverted ? false : true);
}

GUIButton *GUIButtonBar::getButton(const std::string &id)
{
	std::vector<GUIButton *>::iterator it = _buttons.begin();

	while (it != _buttons.end())
	{
		if ((*it)->getId() == id)
			return (*it);
		it++;
	}
	return (NULL);
}

void GUIButtonBar::setSpacing(const int &spacing)
{
	_spacing = spacing;
}

const sf::Vector2f &GUIButtonBar::calcButtonPosition(const std::vector<GUIButton *>::iterator &it, const sf::Vector2f &pos)
{
	std::vector<GUIButton *>::iterator rIt = it;
	int size = 0;

	if (_type == Horizontal)
	{
		while (rIt != _buttons.begin())
		{
			size += (*rIt)->getLocalBounds().width;
			rIt--;
		} 
	}
	else if (_type == Vertical)
	{
		while (rIt != _buttons.begin())
		{
			size += (*rIt)->getLocalBounds().height;
				rIt--;
		}
	}
	return (pos + sf::Vector2f(0, size + _spacing));
}

const sf::Vector2f &GUIButtonBar::calcButtonPosition(const std::vector<GUIButton *>::reverse_iterator &it, const sf::Vector2f &pos)
{
	std::vector<GUIButton *>::reverse_iterator rIt = it;
	int size = 0;

	if (_type == Horizontal)
	{
		while (rIt != _buttons.rbegin())
		{
			size += (*rIt)->getLocalBounds().width;
			rIt--;
		}
	}
	else if (_type == Vertical)
	{
		while (rIt != _buttons.rbegin())
		{
			size += (*rIt)->getLocalBounds().height;
			rIt--;
		} 
	}
	return (pos + sf::Vector2f(0, size + _spacing));
}

void GUIButtonBar::setPosition(const sf::Vector2f &pos)
{
	if (!_inverted)
	{
		std::vector<GUIButton *>::iterator it = _buttons.begin();

		while (it != _buttons.end())
		{
			(*it)->setPosition(calcButtonPosition(it, pos));
			it++;
		}
	}
	else
	{
		std::vector<GUIButton *>::reverse_iterator it = _buttons.rbegin();

		while (it != _buttons.rend())
		{
			(*it)->setPosition(calcButtonPosition(it, pos));
			it++;
		}
	}
}

GUITextButton *GUIButtonBar::addTextButton(const std::string &id, const std::string &label, const std::string &fontResource, const TextSkin &skin)
{
	GUITextButton *button = new GUITextButton(id, label, fontResource, skin);

	_buttons.push_back(button);
	return (button);
}

GUISpriteButton *GUIButtonBar::addSpriteButton(const std::string &id, const std::string &resource, const SpriteSkin &skin)
{
	GUISpriteButton *button = new GUISpriteButton(id, resource, skin);

	_buttons.push_back(button);
	return (button);
}

GUIToggleSpriteButton *GUIButtonBar::addToggleSpriteButton(const std::string &id, const std::string &resource, const SpriteSkin &skin, const SpriteSkin &altSkin)
{
	GUIToggleSpriteButton *button = new GUIToggleSpriteButton(id, resource, skin, altSkin);

	_buttons.push_back(button);
	return (button);
}

bool GUIButtonBar::update(const sf::Event &e)
{
	std::vector<GUIButton *>::iterator it = _buttons.begin();

	while (it != _buttons.end())
	{
		(*it)->update(e);
		it++;
	}
	return (true);
}

void GUIButtonBar::draw(sf::RenderWindow *win)
{
	std::vector<GUIButton *>::iterator it = _buttons.begin();

	while (it != _buttons.end())
	{
		(*it)->draw(win);
		it++;
	}
}