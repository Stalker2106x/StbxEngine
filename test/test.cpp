#include "../include/Engine.hpp"
#include "../include/Menu.hh"

class sEngine : public Engine
{
public:
  sEngine()
  {
    _mainMenu.loadFromFile("./Data/menu/main.xml");
  };
  
  ~sEngine()
  {

  };
  
  bool update(sf::Event &e);
  void draw();

private:
  Menu _mainMenu;
};

bool sEngine::update(sf::Event &e)
{
  _mainMenu.update(e);
  return (true);
}

void sEngine::draw()
{
  _mainMenu.draw(_win);
}

int main(int argc, char **argv)
{
  sEngine engine;

  if (argc > 0)
    engine.handleArgs(argc, argv);
  engine.mainLoop();  
  return (0);
}
