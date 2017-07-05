#include "Resolver.hh"
#include "cengine.hh"

int main(int argc, char **argv)
{
  sEngine engine;
  sf::Font f;

  Resolver::resolve(f, std::string("arial"));
  if (argc > 0)
    engine.handleArgs(argc, argv);
  engine.mainLoop();  
  return (0);
}
