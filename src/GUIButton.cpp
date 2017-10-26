#include "GUIButton.hh"
#include "Engine.hpp"
#include "Resolver.hh"

using namespace stb;

//
// GUIButton
//

GUIButton::GUIButton(const sf::Event::EventType &triggerType) : GUIElement("", Button)
{
	_onClickCallback = NULL;
	_onRClickCallback = NULL;
	_triggerType = triggerType;
}

GUIButton::~GUIButton()
{
}

void GUIButton::initialUpdate()
{
	_hover = false;
}

bool GUIButton::isHovered() const
{
	return (_hover);
}

void GUIButton::setClickCallback(const std::function<void(void)> &fptr)
{
	_onClickCallback = new std::function<void(void)>(fptr);
}

void GUIButton::setRClickCallback(const std::function<void(void)> &fptr)
{
	_onRClickCallback = new std::function<void(void)>(fptr);
}

void GUIButton::setSkin(Skin *skin)
{
	_skin = skin;
}

bool GUIButton::onHover(bool triggered)
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
	if (_onClickCallback != NULL)
		(*_onClickCallback)();
}

void GUIButton::onRClick()
{
	if (_onRClickCallback != NULL)
		(*_onRClickCallback)();
}

bool GUIButton::update(const sf::Event &e)
{
	if (!_active)
		return (false);
	if (e.type == _triggerType && _hover)
	{
		if (static_cast<int>(e.key.code) == static_cast<int>(sf::Mouse::Left))
			onClick();
		else if (static_cast<int>(e.key.code) == static_cast<int>(sf::Mouse::Right))
			onRClick();
	}
	return (true);
}

//
// GUIToggleSpriteButton
//

GUIToggleButton::GUIToggleButton(const sf::Event::EventType &triggerType) : GUIButton(triggerType)
{
	_state = false;
}

GUIToggleButton::~GUIToggleButton()
{
}

void GUIToggleButton::setAltSkin(Skin *altSkin)
{
	_altSkin = altSkin;
}

bool GUIToggleButton::onHover(bool triggered) //Set correct skin based on type of btn
{
	GUIButton::onHover(triggered);
	if (triggered)
	{
		if (_altSkin->type == SkinText)
		{
			if (_state)
				setActiveSkin(static_cast<TextSkin *>(_altSkin)->hover);
			else
				setActiveSkin(static_cast<TextSkin *>(_skin)->hover);
		}
		else if (_altSkin->type == SkinSprite)
		{
			if (_state)
				setActiveSkin(static_cast<SpriteSkin *>(_altSkin)->hover);
			else
				setActiveSkin(static_cast<SpriteSkin *>(_skin)->hover);
		}
	}
	else
	{
		if (_altSkin->type == SkinText)
		{
			if (_state)
				setActiveSkin(static_cast<TextSkin *>(_altSkin)->normal);
			else
				setActiveSkin(static_cast<TextSkin *>(_skin)->normal);
		}
		else if (_altSkin->type == SkinSprite)
		{
			if (_state)
				setActiveSkin(static_cast<SpriteSkin *>(_altSkin)->normal);
			else
				setActiveSkin(static_cast<SpriteSkin *>(_skin)->normal);
		}
	}
	return (true);
}

void GUIToggleButton::onClick()
{
	_state = (_state ? false : true);
	(*_onClickCallback)();
}

bool GUIToggleButton::update(const sf::Event &e)
{
	if (!GUIButton::update(e))
		return (false);
	return (true);
}
//
// GUITextButton
//

template <typename T>
GUITextButton<T>::GUITextButton(const std::string &label, const std::string &fontResource, const sf::Event::EventType &triggerType) : T(triggerType)
{
	_label.setString(label);
	_label.setFont(*SFResolver<sf::Font>::resolve(fontResource));
}

template <typename T>
GUITextButton<T>::~GUITextButton()
{
}

template <typename T>
void GUITextButton<T>::initialUpdate()
{
	GUIButton::initialUpdate();
	_skin = new TextSkin(sf::Color::White, sf::Color::Cyan);
	if (_label.getGlobalBounds().contains(Engine::instance->getMousePosition()))
		onHover(true);
	else
		onHover(false);
}

template <typename T>
void GUITextButton<T>::setLabel(const std::string &label)
{
	_label.setString(label);
}

template <typename T>
void GUITextButton<T>::setFont(const sf::Font &font)
{
	_label.setFont(font);
}

template <typename T>
void GUITextButton<T>::setPosition(const sf::Vector2f &pos)
{
	_label.setPosition(pos);
}

template <typename T>
void GUITextButton<T>::setFontsize(int size)
{
	_label.setCharacterSize(size);
}

template <typename T>
void GUITextButton<T>::setColor(const sf::Color &color)
{
	_label.setFillColor(color);
}

template <typename T>
void GUITextButton<T>::setActiveSkin(const sf::Color color)
{
	_label.setFillColor(color);
}

template <typename T>
const sf::Vector2f &GUITextButton<T>::getPosition()
{
	return (_label.getPosition());
}

template <typename T>
const sf::Vector2f GUITextButton<T>::getSize()
{
	return (sf::Vector2f(_label.getLocalBounds().width, _label.getLocalBounds().height));
}

template <typename T>
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

template <typename T>
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

template <typename T>
void GUITextButton<T>::draw(sf::RenderWindow *win)
{
	if (!_active)
		return;
	win->draw(_label);
}

//
// GUISpriteButton
//

template <typename T>
GUISpriteButton<T>::GUISpriteButton(const std::string &resource, const sf::Event::EventType &triggerType) : T(triggerType)
{
	_sprite.setTexture(*SFResolver<sf::Texture>::resolve(resource));
}

template <typename T>
GUISpriteButton<T>::~GUISpriteButton()
{
}

template <typename T>
void GUISpriteButton<T>::initialUpdate()
{
	GUIButton::initialUpdate();
	_sprite.setTextureRect(static_cast<SpriteSkin *>(_skin)->normal);
}

template <typename T>
void GUISpriteButton<T>::setTexture(const std::string &resource)
{
	_sprite.setTexture(*SFResolver<sf::Texture>::resolve(resource));
}

template <typename T>
void GUISpriteButton<T>::setActiveSkin(const sf::IntRect geometry)
{
	_sprite.setTextureRect(geometry);
}

template <typename T>
void GUISpriteButton<T>::setPosition(const sf::Vector2f &pos)
{
	_sprite.setPosition(pos);
}

template <typename T>
const sf::Vector2f &GUISpriteButton<T>::getPosition()
{
	return (_sprite.getPosition());
}

template <typename T>
const sf::Vector2f GUISpriteButton<T>::getSize()
{
	return (sf::Vector2f(_sprite.getLocalBounds().width, _sprite.getLocalBounds().height));
}

template <typename T>
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

template <typename T>
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

template <typename T>
void GUISpriteButton<T>::draw(sf::RenderWindow *win)
{
	if (!_active)
		return;
	win->draw(_sprite);
}


//
// GUIButtonBar
//

GUIButtonBar::GUIButtonBar(BarType type) : GUIElement("", ButtonBar)
{
	_spacing = 0;
	_type = type;
	_inverted = false;
}

GUIButtonBar::~GUIButtonBar()
{

}

void GUIButtonBar::initialUpdate()
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

const sf::Vector2f GUIButtonBar::getSize()
{
	std::vector<GUIButton *>::iterator it = _buttons.begin();
	sf::Vector2f size(0,0);

	while (it != _buttons.end())
	{
		if (_type == Horizontal)
		{
			size.x += (*it)->getSize().x;
			if (size.y < (*it)->getSize().y)
				size.y = (*it)->getSize().y;
		}
		else if (_type == Vertical)
		{
			size.y += (*it)->getSize().y;
			if (size.x < (*it)->getSize().x)
				size.x = (*it)->getSize().x;
		}
		it++;
	}
	return (size);
}

void GUIButtonBar::setSpacing(int spacing)
{
	_spacing = spacing;
}

const sf::Vector2f GUIButtonBar::calcButtonPosition(const size_t &index, const sf::Vector2f &pos)
{
	float size = 0;

	for (int i = index + (_inverted ? 1 : -1 ); (_inverted ? i < static_cast<int>(_buttons.size()) : i >= 0); (_inverted ? i++ : i--))
	{
		if (_type == Horizontal)
		{
			size += _buttons[i]->getSize().x;
		}
		else if (_type == Vertical)
		{
			size += _buttons[i]->getSize().y;
		}
	}
	if (_type == Vertical)
		return (pos + sf::Vector2f(0, size + _spacing));
	return (pos + sf::Vector2f(size + _spacing, 0)); //Horizontal
}

void GUIButtonBar::setPosition(const sf::Vector2f &pos)
{
	for (int i = (_inverted ? _buttons.size() - 1 : 0); (_inverted ? i >= 0 : i < static_cast<int>(_buttons.size())); (_inverted ? i-- : i++))
		_buttons[i]->setPosition(calcButtonPosition(i, pos));
}

const sf::Vector2f &GUIButtonBar::getPosition()
{
	return (_buttons.size() > 0 ? _buttons[0]->getPosition() : sf::Vector2f(0,0));
}

GUIButton *GUIButtonBar::addButton(GUIButton *button)
{
	_buttons.push_back(button);
	return (button);
}

GUITextButton<GUIButton> *GUIButtonBar::addTextButton(const std::string &label, const std::string &fontResource)
{
	GUITextButton<GUIButton> *button = new GUITextButton<GUIButton>(label, fontResource);

	addButton(button);
	return (button);
}

GUISpriteButton<GUIButton> *GUIButtonBar::addSpriteButton(const std::string &resource)
{
	GUISpriteButton<GUIButton> *button = new GUISpriteButton<GUIButton>(resource);

	addButton(button);
	return (button);
}

GUISpriteButton<GUIToggleButton> *GUIButtonBar::addToggleSpriteButton(const std::string &resource)
{
	GUISpriteButton<GUIToggleButton> *button = new GUISpriteButton<GUIToggleButton>(resource);

	addButton(button);
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