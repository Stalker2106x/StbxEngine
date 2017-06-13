#include "../include/Engine.hpp"

class sEngine : public Engine
{
  bool update(sf::Event &e);
  void draw();
};

bool sEngine::update(sf::Event &e)
{
  return (true);
}

void sEngine::draw()
{

}

int main(int argc, char **argv)
{
  sEngine engine;

  if (argc > 0)
    engine.handleArgs(argc, argv);
  engine.mainLoop();  
  return (0);
}
