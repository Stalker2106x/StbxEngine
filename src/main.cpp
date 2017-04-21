#include "Engine.hh"

int main(int argc, char **argv)
{
  Engine engine;

  engine.openWindow();
  engine.mainLoop();  
  return (0);
}
