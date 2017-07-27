#include "GUIObject.hh"
#include "Engine.hpp"

using namespace stb;

//
// GUISIndicator
//

GUISIndicator::GUISIndicator(const std::string &label) : GUIElement(label)
{
	_value.setFont(*Resolver<sf::Font>::resolve("glitch"));
}

GUISIndicator::~GUISIndicator()
{
	if (_label != NULL)
		delete (_label);
}

void GUISIndicator::setFontsize(const int &fontSize)
{
	if (_label != NULL)
		_label->setCharacterSize(fontSize);
	_value.setCharacterSize(fontSize);
}

void GUISIndicator::setPosition(const sf::Vector2f &pos)
{
	if (_label != NULL)
		_label->setPosition(pos);
	_value.setPosition(_label->getPosition() + sf::Vector2f(_label->getLocalBounds().width + 5, 0));
}

bool GUISIndicator::update(const sf::Event &e)
{
	if (!GUIElement::update(e))
		return (false);
	return (true);
}

void GUISIndicator::draw(sf::RenderWindow *win)
{
	if (!_active)
		return;
	if (_label != NULL)
		win->draw(*_label);
	win->draw(_value);
}

//
// GUIPanel
//

GUIPanel::GUIPanel(const std::string &id, const sf::Vector2i &size, const sf::Color &color) : GUIElement(id)
{
	sf::Texture ctexture;

	ctexture.create(size.x, size.y);
	_frame.setTexture(ctexture);
	_frame.setColor(color);
}


GUIPanel::GUIPanel(const std::string &id, const sf::Vector2i &size, const std::string &name) : GUIElement(id)
{
	_frame.setTexture(*Resolver<sf::Texture>::resolve(name));
}

GUIPanel::~GUIPanel()
{

}

void GUIPanel::setPosition(const sf::Vector2f &pos)
{
	_frame.setPosition(pos);
}

void GUIPanel::setStyle(const char &style)
{
	_style = style;
}

void GUIPanel::addElement(GUIElement *element)
{
	_elements.push_back(element);
	_elements.back()->setPosition(_frame.getPosition() + sf::Vector2f(5, 5 + ((_elements.size() - 1) * 35)));
}

void GUIPanel::updateElementsPosition()
{
	for (size_t i = 0; i < _elements.size(); i++)
	{
		_elements[i]->setPosition(_frame.getPosition() + sf::Vector2f(5, 5 + (i * 35)));
	}
}

bool GUIPanel::update(const sf::Event &e)
{
	if (!GUIElement::update(e))
		return (false);
	for (size_t i = 0; i < _elements.size(); i++)
		_elements[i]->update(e);
	return (true);
}

void GUIPanel::draw(sf::RenderWindow *win)
{
	if (!_active)
		return;
	win->draw(_frame);
	for (size_t i = 0; i < _elements.size(); i++)
		_elements[i]->draw(win);
}

//
// GUIDynamicPanel
//

GUIDraggablePanel::GUIDraggablePanel(const std::string &id, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor)
	: GUIPanel(id, size, frameColor)
{
	sf::Texture ctexture;

	ctexture.create(size.x, 15);
	_header.setTexture(ctexture);
	_header.setColor(headerColor);
	initialUpdate();
}

GUIDraggablePanel::GUIDraggablePanel(const std::string &id, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource)
	: GUIPanel(id, size, frameResource)
{
	_header.setTexture(*Resolver<sf::Texture>::resolve(headerResource));
	initialUpdate();
}


GUIDraggablePanel::~GUIDraggablePanel()
{

}

void GUIDraggablePanel::initialUpdate()
{
	GUIElement *btn;

	_lock = false;
	_dragging = false;
	_style |= PN_CLOSE | PN_LOCK;
	btn = _buttonBar.addSpriteButton("__close", "buttons", sf::IntRect(0, 0, 16, 16), sf::IntRect( 0, 16, 16, 16 ));
	if ((_style & PN_CLOSE) != PN_CLOSE)
		btn->toggle();
	btn = _buttonBar.addSpriteButton("__lock", "buttons", sf::IntRect(16, 0, 16, 16), sf::IntRect(16, 16, 16, 16));
	if ((_style & PN_LOCK) != PN_LOCK)
		btn->toggle();
	movePanel(sf::Vector2f(0, 0));
}

void GUIDraggablePanel::toggle()
{
	GUIElement::toggle();
	_dragging = false;
	_lock = false;
}

void GUIDraggablePanel::toggleLock()
{
	_lock = (_lock ? false : true);
	//toggleactiveskin
}

void GUIDraggablePanel::setPosition(const sf::Vector2f &pos)
{
	GUIPanel::setPosition(pos + sf::Vector2f(0, 15));
	_header.setPosition(pos);
	_buttonBar.getButton("__close")->setPosition(sf::Vector2f(pos + sf::Vector2f(_header.getLocalBounds().width - _buttonBar.getButton("__close")->getLocalBounds().width, 0)));
	_buttonBar.getButton("__lock")->setPosition(pos + sf::Vector2f(_header.getLocalBounds().width -
		(_buttonBar.getButton("__lock")->getLocalBounds().width + _buttonBar.getButton("__lock")->getLocalBounds().width), 0));
	movePanel(pos);
}

void GUIDraggablePanel::movePanel(const sf::Vector2f &newpos)
{
	_header.setPosition(newpos);
	_buttonBar.getButton("__close")->setPosition(newpos + sf::Vector2f(_header.getGlobalBounds().width - _buttonBar.getButton("__close")->getGlobalBounds().width, 0));
	_buttonBar.getButton("__lock")->setPosition(newpos + sf::Vector2f(_header.getGlobalBounds().width -
		(_buttonBar.getButton("__close")->getGlobalBounds().width + _buttonBar.getButton("__lock")->getGlobalBounds().width), 0));
	_frame.setPosition(newpos + sf::Vector2f(0, _header.getGlobalBounds().height));
	updateElementsPosition();
}

bool GUIDraggablePanel::update(const sf::Event &e)
{
	if (!GUIPanel::update(e))
		return (false);
	_buttonBar.update(e);
	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (!_lock && !_dragging && e.key.code == sf::Mouse::Left && _header.getGlobalBounds().contains(Engine::getMousePosition()))
		{
			_dragging = true;
			_dragOffset = sf::Vector2f(Engine::getMousePosition().x - _header.getGlobalBounds().left,
				Engine::getMousePosition().y - _header.getGlobalBounds().top);
		}
	}
	else if (e.type == sf::Event::MouseButtonReleased)
	{
		if (!_lock && _dragging && e.key.code == sf::Mouse::Left)
			_dragging = false;
	}
	return (true);
}

void GUIDraggablePanel::draw(sf::RenderWindow *win)
{
	if (!_active)
		return;
	win->draw(_header);
	_buttonBar.draw(win);
	GUIPanel::draw(win);
}
