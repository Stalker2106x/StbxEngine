## Set up your environment

First of all, you must grab the latest sources and build them by yourself!\n
Don't worry, this step is usually easy if you already have all the Prerequisites setup.\n
To do so, open your command prompt and clone the repository:\n

    git clone https://bitbucket.org/stalker2106/StbxEngine.git

Then you want to download the latest source of all the dependencies\n

    git submodule update --init --recursive

You should already have all the mandatory code to start developing your game; though, before\n
using it, you must build the library and its dependencies.

### Build SFML

You need to build SFML to link StbxEngine with it. The git repository is linked and should\n
have grabbed the latest version of SFML inside "<REPO>/extlib/SFML/" directory.

If you want, you can replace the folder with pre-built binaries from SFML website.
Just follow the setup guide on their owner's repository, and go to next step.)\n

Start configuring SFML by navigating through the repository to "<REPO>/extlib/SFML/", and run\n
the CMake command with the correct option depending on which compiler will be used. (-G flag to specify)\n

    cd extlib/SFML/
    cmake .

You can right away compile the SFML library with the generated Makefile or VS/Xcode project.\n
NOTE: Check carefully the type of the built binary (you may want to select Release for most cases)\n

Once its done: Hoorah, you got SFML setted up. Now let's build the TGUI component.

### Build TGUI

You need to build Texu's GUI in order to compile StbxEngine. The git repository is linked and should\n
have grabbed the latest version of TGUI inside "<REPO>/extlib/TGUI/" directory.

Start configuring TGUI by navigating through the repository to "<REPO>/extlib/TGUI/", and run\n
the CMake command with the correct option depending on which compiler will be used. (-G flag to specify)\n

    cd extlib/TGUI/
    cmake .

You can right away compile the TGUI library with the generated Makefile or VS/Xcode project.\n
NOTE: Check carefully the type of the built binary (you may want to select Release for most cases)\n

When done, time to build StbxEngine in bones and flesh !\n

### Build StbxEngine

Get back to the root folder of the repository, and run CMake. Again, check carefully your options to match your environment.\n
NOTE: For Visual Studio, use the given Solutions in vs12 for Visual Studio 2013, and vs14 for 2015 respectively.\n

    cd ../../
    cmake .

Then just run the Makefile or the Visual Studio solution, and the project should build without errors.\n
Once done, you can use the engine to create your own game, following the next section guide.\n