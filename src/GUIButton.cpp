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

bool GUIButton::update(const sf::Event &e)
{
	if (!GUIElement::update(e))
		return (false);
	if (e.type == _triggerType && _hover)
	{
		if (e.key.code == sf::Mouse::Left && !_onClickCallback._Empty())
			_onClickCallback();
		else if (e.key.code == sf::Mouse::Right && !_onRClickCallback._Empty())
			_onRClickCallback();
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

GUITextButton::GUITextButton(const std::string &id, const std::string &label, const std::string &fontResource, sf::Color skins[2], const sf::Event::EventType &triggerType) : GUIButton(id, triggerType)
{
	_label.setString(label);
	_label.setFont(*Resolver<sf::Font>::resolve(fontResource));
	_skins[0] = skins[0];
	_skins[1] = skins[1];
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
	_activeSkin = 0;
}

GUISpriteButton::GUISpriteButton(const std::string &id, const std::string &resource, sf::IntRect skins[2], const sf::Event::EventType &triggerType) : GUIButton(id, triggerType)
{
	_sprite.setTexture(*Resolver<sf::Texture>::resolve(resource));
	_skins[0] = skins[0];
	_skins[1] = skins[1];
	_activeSkin = 0;
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
	_activeSkin = (_activeSkin == 0 ? 1 : 0);
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
// GUIButtonBar
//

GUIButtonBar::GUIButtonBar()
{

}

GUIButtonBar::~GUIButtonBar()
{

}

GUIButton *GUIButtonBar::getButton(const std::string &id)
{
	std::vector<GUIButton *>::iterator it = _buttons.begin();

	while (it != _buttons.end())
	{
		if ((*it)->getId() == id)
			return (*it);
	}
	return (NULL);
}

void GUIButtonBar::setPosition(const sf::Vector2f &pos)
{
	//TODO
}

GUITextButton *GUIButtonBar::addTextButton(const std::string &id, const std::string &label, const std::string &fontResource, const sf::Color &normalSkin, const sf::Color &hoverSkin)
{
	sf::Color skins[] = { normalSkin, hoverSkin };
	GUITextButton *button = new GUITextButton(id, label, fontResource, skins);

	_buttons.push_back(button);
	return (button);
}

GUISpriteButton *GUIButtonBar::addSpriteButton(const std::string &id, const std::string &resource, const sf::IntRect &normalSkin, const sf::IntRect &hoverSkin)
{
	sf::IntRect skins[] = { normalSkin, hoverSkin };
	GUISpriteButton *button = new GUISpriteButton(id, resource, skins);

	_buttons.push_back(button);
	return (button);
}

bool GUIButtonBar::update(const sf::Event &e)
{
	std::vector<GUIButton *>::iterator it = _buttons.begin();

	while (it != _buttons.end())
	{
		(*it)->update(e);
	}
	return (true);
}

void GUIButtonBar::draw(sf::RenderWindow *win)
{
	std::vector<GUIButton *>::iterator it = _buttons.begin();

	while (it != _buttons.end())
	{
		(*it)->draw(win);
	}
}