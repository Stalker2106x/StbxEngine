## Getting Started ##

### Prerequisites

StbxEngine is cross-platform and supports variety of platforms, thanks to portability of SFML.\n
It supports Windows, Linux and MacOS out of the box, and hopefully Android & iOS; check [SFML website]() for further info.\n
To setup your environment will need a few tools, such as :\n
  -Git to download the repository and all the submodule dependencies\n
  -C++ Compiler with C++11 support\n
  -CMake for configuring project for your environment\n

### Set up environment

Follow [Set up environment](SetUpEnvironment.md) Guide

### Start developing your game

The StbxEngine provides the Engine class, which is the starting point of the whole library.\n
To create your own Engine, you must inherit from this base class and add all your game routine to your own code.\n

Here is a small example of a basic engine implementation\n

    class MyEngine : public Engine
    {
      bool update(const sf::Event &e);
      void draw(sf::RenderWindow *win);
      //These two methods are mandatory to implement for the project to compile
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
The update method is called BEFORE each frame is drawn on screen; the draw method is called when everything has updated.\n
