#include "Resolver.hh"
#include "cengine.hh"

int main(int argc, char **argv)
{
  sEngine engine;

  if (argc > 0)
    engine.handleArgs(argc, argv);
  engine.mainLoop();  
  return (0);
}
