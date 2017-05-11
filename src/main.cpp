#include "Engine.hh"



int main(int argc, char **argv)
{
  Engine engine(1280, 1024);

  if (argc > 0)
    engine.handleArgs(argc, argv);
  engine.mainLoop();  
  return (0);
}
