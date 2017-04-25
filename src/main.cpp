#include "Engine.hh"

int main(int argc, char **argv)
{
  Engine engine(1280, 1024);

  (void)argc;
  (void)argv;
  engine.mainLoop();  
  return (0);
}
