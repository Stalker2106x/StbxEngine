#include "Engine.hpp"

Keybinds *Engine::keybinds = new Keybinds();
Console *Engine::console = NULL;

Engine::Engine(int width, int height)
{
  _quit = false;
  _win = NULL;
  _fullscreen = false;
  _vsync = false;
  Engine::console = new Console(*this);
  openWindow(width, height);
  keybinds->bindEnv(this);
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
  _win->create(sf::VideoMode(_winsize.x, _winsize.y), "Stbx Engine ALPHA",
	       (_fullscreen ? sf::Style::Fullscreen : sf::Style::Resize | sf::Style::Close));
  Engine::console->initGraphics(_winsize);
  return (true);
}

void Engine::handleArgs(int argc, char **argv)
{
  std::string cmd;

  if (argc <= 1)
    return;
  for (short i = 0; i < argc; i++)
    {
      if (argv[i][0] == '-')
	{
	  cmd = argv[i++] + 1;
	  while ((i + 1) < argc && argv[i + 1][0] != '-')
	    {
	      cmd += " "+std::string(argv[i]);
	      i++;
	    }
	  if ((i + 1) == argc)
	    cmd += " "+std::string(argv[i]);
	  Engine::console->output(cmd);
	  Commands::parseCmd(*this, cmd);
	}
    }
}

sf::Vector2i Engine::getWindowSize() const
{
  return (_winsize);
}

void Engine::videoParamSet(const std::string &ent, const int &value)
{
  if (ent == "FPS")
    _win->setFramerateLimit(value);
  else if (ent == "TFULLSCREEN")
    {
      _fullscreen = (_fullscreen ? false : true);
      openWindow(_winsize.x, _winsize.y);
    }
  else if (ent == "FULLSCREEN" && static_cast<bool>(value) != _fullscreen)
    {
      _fullscreen = static_cast<bool>(value);
      openWindow(_winsize.x, _winsize.y);
    }
  else if (ent == "TVSYNC")
    {
      _vsync = (_vsync ? false : true);
      _win->setVerticalSyncEnabled(_vsync);
    }
  else if (ent == "VSYNC")
    {
      _vsync = static_cast<bool>(value);
      _win->setVerticalSyncEnabled(_vsync);
    }
}

sf::Image Engine::capture()
{
  sf::Texture scpy;
  sf::Image screen;

  scpy.update(*_win);
  screen = scpy.copyToImage();
  return (screen);
}

void Engine::graphicsLoop()
{
  if (Engine::console->isActive())
    Engine::console->draw(_win);
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
      Engine::console->update(event);
      keybinds->update(event);
      if (update(event) == false)
	{
	  _win->close();
	  return (false);
	}
    }
  return (true);
}

int Engine::mainLoop()
{
  while (!_quit && _win->isOpen() && updateLoop())
    {
      _win->clear(sf::Color::Blue);
      graphicsLoop();
      draw();
      _win->display();
    }
  return (0);
}

char Engine::getChar(sf::Event event, CharType type, bool useBinds)
{
  if ((event.key.code == sf::Keyboard::Return || event.type != sf::Event::TextEntered)
    || (!useBinds && keybinds->isBound(Control("", event.key.code))))
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
