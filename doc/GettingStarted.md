## Getting Started ##

### Start developing YOUR environment

The StbxEngine provides the Engine class, which is the starting point of the whole library.\n 
To create your own Engine, you must inherit from this base class and add all your game routine to your own code.\n 

Here is a small example of a basic engine implementation\n 

     class MyEngine : public Engine
     {
          bool update(const sf::Event &e);
     	  void draw(sf::RenderWindow *win);
	  //These two methods are mandatory to compile your project
     };
     
     bool MyEngine::update(const sf::Event &e)
     {
          //Your game logic goes here
     }
     
     void MyEngine::draw(sf::RenderWindow *win)
     {
	  //Your game graphics goes here
     }

With this architecture, every aspect of the game has its container:\n 
Please note: EVERY Drawable class you write should implement this update/draw logic\n
The draw function should only draw, and therefore should be const passive to its owner.\n 
Both draw and update function are triggered every tick, and draw happens only after the update calls.\n

