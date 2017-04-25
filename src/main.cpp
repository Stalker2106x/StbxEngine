#include "Engine.hh"

int main(int argc, char **argv)
{
  Engine engine;

  (void)argc;
  (void)argv;
  engine.openWindow();
  engine.mainLoop();  
  return (0);
}
