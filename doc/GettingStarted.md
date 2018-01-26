## Getting Started ##

StbxEngine is cross-platform and supports variety of platforms, thanks to portability of SFML.\n
It supports Windows, Linux and MacOS out of the box, and hopefully Android & iOS; check [SFML website](https://www.sfml-dev.org/index.php) for further info.\n

### Set up your environment

There is two ways of using StbxEngine in your projects:\n

You can use precompiled StbxEngine binaires for your platform.\n
This method is the simplest, and should work out of the box for most platforms.\n
Follow the [Precompiled libs guide](./md_doc_SetUpEnvironmentPrecompiled.html) 

You can build the whole library AND dependencies to compile for any target platform (even a not pre-built one).\n
This is preferred for advanced users, if you use a standard platform and want a fast approach to the Engine, give the previous method a shot!\n
Follow the [Build youself guide](./md_doc_SetUpEnvironmentBuild.html)

### Start developing your game

Follow the [Your first engine guide](./md_doc_YourFirstEngine.html) for basic initiation to StbxEngine

### Components ###

#### Console ####

The engine has an integrated debugger console, which is useful for many purposes:
    -Give access to hidden / temporary commands to help devlopment\n
    -Modify GUI/Layout/Elements at runtime\n
    -Allow users to use advanced commands that are not listed within app\n
    -Check performance\n
    -Acts as a file descriptor for input/output, with logging capabilities\n

#### Network ####

NOTE: As of now, only TCP/IP protocol is supported.\n
The network layer embedded in the engine is powerful, reliable and multithreaded.\n
Based on SFML Network layer, with extended capabilities, it has a full Duplex conception where packets are handled generically.\n
Each packet is composed of a code, an emitter (clientId), and args. There can be any arguments of any type inside any packet.\n
Note that the emitter with id -1 is the Server itself.\n
This means for example that a basic packet exchange between server and client looks like this:

    code 151 = client wants to move in {direction} direction.
    code 251 = Server moved {clientId} client to {pos} position.

    C:151|0|{direction}
    S:251|-1|{ClientId}, {pos}

Basically, the handling of packets is as simple as associating a code to a function.\n
In this case, server bind the following function to packet code 151.\n

    void move(std::shared_ptr<Packet> packet)
    {
        auto player = _game.getPlayer(packet->clientId); //Get player from game
        Vector2i pos = packet->getData<Vector2i>(); //Get desired position from client

        player->move(pos); //move client to position grabbed from packet
        Packet::broadcast(_socket, -1, packet->clientId, pos); //Broadcast the move to others clients to synchronise everybody
    }

#### Profile ####

The engine implements a flexible Profile module which holds static configuration, and can be instanciated to represent a "User".\n
For account based games, it implements HTTP requests of any method to a remote api to validate login of users.\n
Any StbxEngine powered app that uses the config module has a "config.cfg" file in the root folder alongside the binary.\n
It uses standard KEY=VALUE syntax, and is used to store used parameters between different instances of the app.\n
C++-wise, you can access, create or destroy any parameter with the static map Profile::config.\n
The config is saved/restored automatically and you shouldnt care about that. Still, you can force reload, or save anytime with above-named functions.\n

#### Keybinds ####

Implements a device abstraction layer: Any interaction with Keyboard/Gamepad/Mouse is considered a "Control".\n
Therefore, unlike stock SFML, you can bind any action to basically any device without specific implementation depending on device nature.\n