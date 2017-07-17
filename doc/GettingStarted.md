## Getting Started ##

#Start developing YOUR environment

The StbxEngine provides the Engine class, which is the starting point of the whole library. To create your own Engine, you must inherit from this base class and add all your game routine to your own code.

Here is a small example of a basic engine implementation
```
GNU/C++11

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
```
With this architecture, every aspect of the game has its container:
Please note: EVERY Drawable class your write should implement this update/draw logic
The draw function should only draw, and should be const passive to its owner.
The update function is triggered every tick to update the entity's members.
