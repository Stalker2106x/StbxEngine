#include "Engine.hpp"
#include "Console.hh"

using namespace stb;

stb::Engine *stb::Engine::instance = NULL;
Profile *stb::Engine::profile = NULL;
tgui::Gui *stb::Engine::gui = NULL;
Console *stb::Engine::console = NULL;

Engine::Engine()
{
	instance = this;
	_framerate = 0;
	_lastSecondTick = sf::Time::Zero;
	_quit = false;
	_win = NULL;
	_fullscreen = false;
	_vsync = false;
	stb::Profile::loadConfig();
}

Engine::~Engine()
{
	delete (_win);
}

void Engine::init(int width, int height, const std::string &windowTitle)
{
	keybinds = new Keybinds();
	console = new Console(*this);
	_windowTitle = windowTitle;
	openWindow(width, height);
	gui = new tgui::Gui(*_win);
	_winWidth = tgui::bindWidth(*gui);
	_winHeight = tgui::bindHeight(*gui);
	console->initGraphics(*gui);
	keybinds->bindEnv(this);
	_gametime.restart();
}

bool Engine::openWindow(int width, int height)
{
	if (_win != NULL)
		delete (_win);
	_win = new sf::RenderWindow();
	_win->setKeyRepeatEnabled(false);
	_win->create(sf::VideoMode(width, height), _windowTitle,
		(_fullscreen ? sf::Style::Fullscreen : sf::Style::Resize | sf::Style::Close));
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
		  Commands::parseCmd(cmd);
		}
    }
}

sf::RenderWindow &Engine::getWindowHandle()
{
	return (*_win);
}

tgui::Layout &Engine::getWindowWidth()
{
	return (instance->_winWidth);
}

tgui::Layout &Engine::getWindowHeight()
{
	return (instance->_winHeight);
}

int &Engine::getFramerate()
{
	return (_framerate);
}

sf::Vector2f &Engine::getMouse()
{
	return (_mouse);
}

sf::Time Engine::getGameTime()
{
	return (_gametime.getElapsedTime());
}

float Engine::getElapsedSeconds()
{
	return (_gametime.getElapsedTime().asSeconds());
}

void Engine::videoParamSet(const std::string &ent, int value)
{
  if (ent == "FPS")
    _win->setFramerateLimit(value);
  else if (ent == "TFULLSCREEN")
    {
      _fullscreen = (_fullscreen ? false : true);
      openWindow(_winWidth.getValue(), _winHeight.getValue());
    }
  else if (ent == "FULLSCREEN" && static_cast<bool>(value) != _fullscreen)
    {
      _fullscreen = static_cast<bool>(value);
      openWindow(_winWidth.getValue(), _winHeight.getValue());
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

void Engine::executeFromMain(std::function<void(void)> fptr)
{
	_executeStack.push(fptr);
}

void Engine::executeStack()
{
	while (!_executeStack.empty())
	{
		_executeStack.front()();
		_executeStack.pop();
	}
}

bool Engine::updateLoop()
{
  sf::Event event;

  _mouse = getMousePosition();
  executeStack();
  while (_win->pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
		{
		  _win->close();
		  return (false);
		}
		if (console->isActive())
			console->update(event);
		keybinds->update(event);
		if (update(event) == false)
		{
		  _win->close();
		  return (false);
		}
		// When the window is resized, the view is changed
		if (event.type == sf::Event::Resized)
		{
			_win->setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
			gui->setView(_win->getView());
		}
		// Pass the event to all the widgets
		gui->handleEvent(event);
    }
  return (true);
}

void Engine::updateFramerate()
{
	_frames++;
	if (_gametime.getElapsedTime().asSeconds() - _lastSecondTick.asSeconds() >= 1)
	{

		_lastSecondTick = _gametime.getElapsedTime();
		_framerate = _frames;
		_frames = 0;
	}
}

int Engine::mainLoop()
{
  while (!_quit && _win->isOpen() && updateLoop())
    {
      _win->clear(sf::Color::Black);
	  draw(*_win);
	  gui->draw();
	  if (console->isActive())
		  console->draw(*_win);
      _win->display();
	  updateFramerate();
    }
  return (0);
}

sf::Vector2f Engine::getMousePosition()
{
	return (static_cast<sf::Vector2f>(sf::Mouse::getPosition(instance->getWindowHandle())));
}

char Engine::getChar(sf::Event event, CharType type)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
		return ('\n');
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
		return ('\b');
	if (event.type != sf::Event::TextEntered)
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
  return (stamp);
}

void Engine::quit()
{
  _quit = true;
}
