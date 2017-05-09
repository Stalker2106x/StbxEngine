#include "Engine.hh"

Keybinds *Engine::keybinds = new Keybinds();

Engine::Engine(int width, int height)
{
  _quit = false;
  _win = NULL;
  _console = new Console(*this);
  openWindow(width, height);
}

Engine::~Engine()
{

}

bool Engine::openWindow(int width, int height)
{
  _winsize = sf::Vector2i(width, height);
  if (_win != NULL)
    delete (_win);
  _win = new sf::RenderWindow();
  _win->setKeyRepeatEnabled(false);
  _win->create(sf::VideoMode(_winsize.x, _winsize.y), "Stbx Engine ALPHA");
  _console->initGraphics(_winsize);
  return (true);
}

sf::Vector2i Engine::getWindowSize() const
{
  return (_winsize);
}

void Engine::videoParamSet(const std::string &ent, const int &value)
{
  if (ent == "FPS")
    _win->setFramerateLimit(value);
  else if (ent == "VSYNC")
    _win->setVerticalSyncEnabled(static_cast<bool>(value));
}

sf::Image Engine::capture()
{
    return (_win->capture());
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
      _console->update(event);
    }
  return (true);
}

int Engine::mainLoop()
{
  while (!_quit && _win->isOpen() && updateLoop())
    {
      _win->clear(sf::Color::Black);
      graphicsLoop();
      _win->display();
    }
  return (0);
}

char Engine::getChar(sf::Event event, CharType type)
{

  if (event.key.code == sf::Keyboard::Return || event.type != sf::Event::TextEntered)
    return ('\0');
  if ((event.text.unicode >= '0' && event.text.unicode <= '9') && (type == numeric || type == alphanumeric))
      return (event.text.unicode);
  if ((event.text.unicode >= ' ' && event.text.unicode <= '~') && (type == alphanumeric || type == alphabetic))
      return (event.text.unicode);
  return ('\0');
}

struct tm *Engine::getTime()
{
  time_t t = time(0);
  struct tm *stamp = localtime(&t);
  
  return (stamp);
}

std::string Engine::getTimestamp()
{
  struct tm *time = Engine::getTime();
  std::string stamp;

  stamp = std::to_string(time->tm_hour)+":"+std::to_string(time->tm_min)+":"+std::to_string(time->tm_sec)+" ";
  stamp += std::to_string(time->tm_mday)+"-"+std::to_string(time->tm_mon)+"-"+std::to_string(time->tm_year);
  delete (time);
  return (stamp);
}

void Engine::quit()
{
  _quit = true;
}
