## Getting Started ##

### Prerequisites

StbxEngine is cross-platform and supports variety of platforms, thanks to SFML.\n
It supports Windows, Linux and MacOS out of the box, and hopefully Android & iOS; check SFML website for further info!\n
To setup your environment will need a few tools, such as :\n
  -Git to download the repository and all the submodule dependencies\n
  -C++ Compiler with C++11 support\n
  -Cmake for configuring projects for Gcc or Clang\n

### Set up environment

First of all, you must grab the latest sources and build them by yourself!\n
Don't worry, this step is usually easy if you already have all the Prerequisites setup.\n
To do so, open your command prompt and clone the repository:\n

    git clone https://bitbucket.org/stalker2106/StbxEngine.git

Then you want to download the latest source of all the dependencies\n
(if you want to use pre-built ones, just follow the setup guide on their owner's repository)\n

    git submodule update --init --recursive

You should already have all the mandatory code to start developing your game; though, before\n
using it, you must build them (if you used pre-built binaries, you can skip this step).\n
Start configuring SFML by navigating through the repository to "<REPO>/extlib/SFML/", and run\n
the CMake command with the correct option depending on which compiler will be used. (-G flag to specify)\n

    cd extlib/SFML/
    cmake .

You can right away compile the SFML library with the generated Makefile or VS/Xcode project.\n
NOTE: Check carefully the platform of the built binary (you may want to select Release and x86 for most cases)\n

Once its done: Hoorah, you got your dependencies setup. Now let's compile the StbxEngine in bones and flesh !\n
Get back to the root folder of the repository, and run CMake again with the correct options\n
NOTE: For Visual Studio, use the given Solutions in vs12 for Visual Studio 2013, and vs14 for 2015 respectively.\n

    cd ../../
    cmake .

Then just run the Makefile or the Visual Studio solution compilation, and the project should build without errors.\n
Once done, you can use the engine to create your own game, following the next section guide.\n

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
