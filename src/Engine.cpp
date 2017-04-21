#include "Engine.hh"

Engine::Engine()
{
  _winsize = sf::Vector2i(1024, 768);
  _win = new sf::RenderWindow();
  _win->setVerticalSyncEnabled(false);
  _win->setFramerateLimit(120);
  _win->setKeyRepeatEnabled(false);
  _console = new Console(_winsize);
}

Engine::~Engine()
{

}

bool Engine::openWindow()
{
  _win->create(sf::VideoMode(_winsize.x, _winsize.y), "Stbx Engine ALPHA");
  return (true);
}

void Engine::graphicsLoop()
{
  if (_console->isActive())
    _console->draw(_win);
}

bool Engine::updateLoop()
{
  sf::Event event;

  while (_win->pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	{
	  _win->close();
	  return (false);
	}
      if (_console->isActive())
	_console->update(event);
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
    _console->toggle();  
  return (true);
}

int Engine::mainLoop()
{
  while (_win->isOpen() && updateLoop())
    {
      _win->clear(sf::Color::Black);
      graphicsLoop();
      _win->display();
    }
  return (0);
}

char Engine::getChar(sf::Event event, CharType type)
{
  if (type == alphanumeric || type == numeric)
    {
      if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9)
	return (static_cast<char>(event.key.code + 48));
    }
  if (type == alphanumeric || type == alphabetic)
    {
      if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z)
	return (static_cast<char>(event.key.code + 97));
    }
  if (event.key.code == sf::Keyboard::BackSpace)
    return ('\b');
  return ('\0');
}
