## Your first engine

The StbxEngine library resides on a simple yet powerful concept: the "Engine" ecosystem.\n
The base class of the project is the stb::Engine class, which you should inherit from, and\n
implement update/draw logic from your game. Basically, most of StbxEngine component act as\n
Extendable interfaces that you inherit from, or feed with functors.\n

For example, the simplest project hello world could be made with the following code:\n

    class MyGame : public stb::Engine //Inherit from StbxEngine class
    {
    public:
	    MyGame()
      {
        init(); //Call init to start Engine/window
      }

	    bool update(const sf::Event &e)
      {
        //Your game logic goes here
      }

	    void draw(sf::RenderWindow &win)
      {
        //Render your game here
      }
    };

    int main(int argc, char **argv)
    {
      MyGame game; //Instanciate your game

      if (argc > 0)
        engine.handleArgs(argc, argv); //If arguments present, handle them (Note: you can call handleArgs without testing.)
      engine.mainLoop(); //Start the game loop.
      return (0);
    }

With this architecture, every aspect of the game has its container:\n
Please note: EVERY Drawable class you write should implement this update/draw logic\n
The draw function should only draw, and therefore should be const passive to its owner.\n
The update method is called BEFORE each frame is drawn on screen; the draw method is called when everything has updated.\n
